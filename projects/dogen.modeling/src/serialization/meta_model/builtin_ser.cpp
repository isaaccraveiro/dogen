/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen.modeling/serialization/meta_model/builtin_ser.hpp"
#include "dogen.modeling/serialization/meta_model/element_ser.hpp"

BOOST_CLASS_TRACKING(
    dogen::modeling::meta_model::builtin,
    boost::serialization::track_selectively)

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::modeling::meta_model::builtin& v,
    const unsigned int /*version*/) {
    ar << make_nvp("element", base_object<dogen::modeling::meta_model::element>(v));

    ar << make_nvp("is_default_enumeration_type", v.is_default_enumeration_type_);
    ar << make_nvp("is_floating_point", v.is_floating_point_);
    ar << make_nvp("can_be_enumeration_underlier", v.can_be_enumeration_underlier_);
    ar << make_nvp("can_be_primitive_underlier", v.can_be_primitive_underlier_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::modeling::meta_model::builtin& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("element", base_object<dogen::modeling::meta_model::element>(v));

    ar >> make_nvp("is_default_enumeration_type", v.is_default_enumeration_type_);
    ar >> make_nvp("is_floating_point", v.is_floating_point_);
    ar >> make_nvp("can_be_enumeration_underlier", v.can_be_enumeration_underlier_);
    ar >> make_nvp("can_be_primitive_underlier", v.can_be_primitive_underlier_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::modeling::meta_model::builtin& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::modeling::meta_model::builtin& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::modeling::meta_model::builtin& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::modeling::meta_model::builtin& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::modeling::meta_model::builtin& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::modeling::meta_model::builtin& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::modeling::meta_model::builtin& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::modeling::meta_model::builtin& v, unsigned int version);

} }