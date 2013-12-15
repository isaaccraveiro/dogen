/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <memory>
#include <functional>
#include <boost/make_shared.hpp>
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/injection_error.hpp"
#include "dogen/sml/types/injector.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.injector"));

const std::string empty;
const std::string merged("merged_");
const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string dia_model("dia");
const std::string sml_model("sml");
const std::string key_extractor_name("key_extractor");
const std::string visitor_name("visitor");
const std::string versioned_name("versioned_key");
const std::string unversioned_name("unversioned_key");
const std::string extract_name("extract");
const std::string uint_name("unsigned int");
const std::string id_name("id");
const std::string version_name("version");
const std::string visitor_argument_name("v");
const std::string extractor_argument_name("e");
const std::string visitor_doc("Visitor for ");
const std::string key_extractor_doc("Extracts keys for type ");
const std::string visit_operation_doc("Accept visits for type ");
const std::string unversioned_key_doc("Unversioned key for ");
const std::string versioned_key_doc("Versioned key for ");
const std::string versioned_property_doc("Object instance's version.");
const std::string empty_identity(
    "Identity must have at least one attribute: ");
const std::string duplicate_qname(
    "Attempt to add object with a name that already exists in model: ");
const std::string zero_leaves("Type marked as visitable but has no leaves: ");
const std::string unversioned_key_not_found(
    "Object is an entity but has no unversioned key: ");

const std::string accept_operation_name("accept");
const std::string accept_argument_name("v");
const std::string accept_operation_doc("Acceptor for ");

}

namespace dogen {
namespace sml {

boost::shared_ptr<object> injector::create_key(const qname& qn,
    const generation_types gt, const std::list<property>& properties,
    const bool versioned) const {

    qname kqn;
    kqn.simple_name(qn.simple_name() + "_" +
        (versioned ? versioned_name : unversioned_name));
    kqn.model_name(qn.model_name());
    kqn.module_path(qn.module_path());
    kqn.external_module_path(qn.external_module_path());

    auto r(boost::make_shared<object>());
    r->name(kqn);
    r->generation_type(gt);
    r->origin_type(origin_types::system);

    const auto vk(object_types::versioned_key);
    const auto uvk(object_types::unversioned_key);
    r->object_type(versioned ? vk : uvk);

    const auto doc(versioned ? versioned_key_doc : unversioned_key_doc);
    r->documentation(doc + qn.simple_name());

    r->local_properties(properties);

    if (versioned)
        inject_version(*r);

    BOOST_LOG_SEV(lg, debug) << "Created key: " << kqn.simple_name();
    return r;
}

boost::shared_ptr<object> injector::
create_versioned_key(const qname& qn, const generation_types gt,
    const std::list<property>& properties) const {
    return create_key(qn, gt, properties, true);
}

boost::shared_ptr<object> injector::
create_unversioned_key(const qname& qn, const generation_types gt,
    const std::list<property>& properties) const {
    return create_key(qn, gt, properties, false);
}

boost::shared_ptr<object>
injector::create_key_extractor(const object& ke) const {
    auto r(boost::make_shared<object>());
    qname qn;
    qn.simple_name(ke.name().simple_name() + "_" + key_extractor_name);
    qn.model_name(ke.name().model_name());
    qn.module_path(ke.name().module_path());
    qn.external_module_path(ke.name().external_module_path());

    BOOST_LOG_SEV(lg, debug) << "Creating extractor: " << qn.simple_name();

    r->name(qn);
    r->generation_type(ke.generation_type());
    r->origin_type(origin_types::system);
    r->object_type(object_types::key_extractor);
    r->documentation(visitor_doc + ke.name().simple_name());

    // FIXME: create these methods with correct names
    parameter p;
    p.name(extractor_argument_name);

    nested_qname nqn;
    const auto i(ke.relationships().find(relationship_types::unversioned_keys));
    if (i == ke.relationships().end() || i->second.size() != 1) {
        BOOST_LOG_SEV(lg, error) << unversioned_key_not_found << ke.name();
        BOOST_THROW_EXCEPTION(
            injection_error(unversioned_key_not_found +
                boost::lexical_cast<std::string>(ke.name())));
    }
    nqn.type(i->second.front());
    p.type(nqn);

    operation opuv;
    opuv.name(unversioned_name);
    opuv.parameters().push_back(p);
    opuv.documentation(key_extractor_doc + ke.name().simple_name());
    r->operations().push_back(opuv);

    BOOST_LOG_SEV(lg, debug) << "Created extractor: " << qn.simple_name();
    return r;
}

void injector::inject_keys(model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting keys.";

    std::list<boost::shared_ptr<object> > objects;
    for (auto& pair : m.objects()) {
        const auto qn(pair.first);
        auto& o(*pair.second);

        BOOST_LOG_SEV(lg, debug) << "Visiting: " << qn;
        if (o.object_type() != object_types::keyed_entity)
            continue;

        if (o.identity().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_identity << qn;

            BOOST_THROW_EXCEPTION(injection_error(empty_identity +
                    boost::lexical_cast<std::string>(qn)));
        }
        BOOST_LOG_SEV(lg, debug) << "Attributes in identity operation: "
                                 << o.identity().size();

        const auto gt(o.generation_type());
        const auto uvk(create_unversioned_key(qn, gt, o.identity()));
        objects.push_back(uvk);
        o.relationships()[relationship_types::unversioned_keys].push_back(
            uvk->name());

        if (o.is_versioned()) {
            auto vk(create_versioned_key(qn, gt, o.identity()));
            o.relationships()[relationship_types::versioned_keys].push_back(
                vk->name());
            objects.push_back(vk);
        }

        // FIXME
        // objects.push_back(create_key_extractor(ke));
    }

    for (const auto& o : objects) {
        const auto i(m.objects().insert(std::make_pair(o->name(), o)));
        if (!i.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_qname << o->name();
            BOOST_THROW_EXCEPTION(injection_error(duplicate_qname +
                    boost::lexical_cast<std::string>(o->name())));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting keys. Total: "
                             << objects.size();
}

void injector::inject_version(object& p) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting version property to type: "
                             << p.name();

    qname qn;
    qn.simple_name(uint_name);

    nested_qname nqn;
    nqn.type(qn);

    property v;
    v.name(version_name);
    v.type(nqn);
    v.documentation(versioned_property_doc);

    p.local_properties().push_back(v);
}

void injector::inject_version(model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting version property on all types.";

    for (auto& pair : m.objects()) {
        auto& ao(*pair.second);

        if (ao.is_versioned())
            inject_version(ao);
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting version property on all types.";
}

boost::shared_ptr<object> injector::create_visitor(const object& ao) const {
    auto r(boost::make_shared<object>());
    qname qn;
    qn.simple_name(ao.name().simple_name() + "_" + visitor_name);
    qn.model_name(ao.name().model_name());
    qn.module_path(ao.name().module_path());
    qn.external_module_path(ao.name().external_module_path());

    BOOST_LOG_SEV(lg, debug) << "Creating visitor: " << qn.simple_name();

    r->name(qn);
    r->generation_type(ao.generation_type());
    r->origin_type(origin_types::system);
    r->object_type(object_types::visitor);
    r->documentation(visitor_doc + ao.name().simple_name());

    const auto i(ao.relationships().find(relationship_types::leaves));
    if (i != ao.relationships().end()) {
        for (const auto& l : i->second) {
            parameter p;
            p.name(visitor_argument_name);

            nested_qname nqn;
            nqn.type(l);
            p.type(nqn);

            operation op;
            op.name("visit");
            op.parameters().push_back(p);
            op.documentation(visit_operation_doc + l.simple_name());
            r->operations().push_back(op);
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Created visitor: " << qn.simple_name();
    return r;
}

void injector::inject_accept(object& ao, const object& v) const {
    parameter p;
    p.name(accept_argument_name);

    nested_qname nqn;
    nqn.type(v.name());
    p.type(nqn);

    operation op;
    op.name(accept_operation_name);
    op.parameters().push_back(p);
    op.documentation(accept_operation_doc + v.name().simple_name());
    ao.operations().push_back(op);
}

void injector::inject_visitors(model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting visitors.";

    std::list<boost::shared_ptr<object> > visitors;
    for (auto& pair : m.objects()) {
        auto& ao(*pair.second);

        if (!ao.is_visitable())
            continue;

        const auto i(ao.relationships().find(relationship_types::leaves));
        const bool has_leaves(i != ao.relationships().end() &&
            !i->second.empty());

        if (!has_leaves) {
            BOOST_LOG_SEV(lg, error) << zero_leaves << ao.name();
            BOOST_THROW_EXCEPTION(injection_error(zero_leaves +
                    boost::lexical_cast<std::string>(ao.name())));
        }

        const auto v(create_visitor(ao));
        visitors.push_back(v);
        inject_accept(ao, *v);
    }

    for (const auto v : visitors) {
        BOOST_LOG_SEV(lg, debug) << "Adding visitor: "
                                 << v->name().simple_name();

        const auto i(m.objects().insert(std::make_pair(v->name(), v)));

        if (!i.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_qname << v->name();
            BOOST_THROW_EXCEPTION(injection_error(duplicate_qname +
                    boost::lexical_cast<std::string>(v->name())));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting visitors.";
}

void injector::inject(model& m) const {
    inject_version(m);
    inject_keys(m);
    inject_visitors(m);
}

} }
