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
#include "masd.dogen.tracing/types/tracer.hpp"
#include "masd.dogen.extraction/types/transforms/context.hpp"

namespace masd::dogen::extraction::transforms {

context::context(
    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer,
    const boost::optional<masd::dogen::diffing_configuration>& diffing_configuration)
    : tracer_(tracer),
      diffing_configuration_(diffing_configuration) { }

const boost::shared_ptr<masd::dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

boost::shared_ptr<masd::dogen::tracing::tracer>& context::tracer() {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v) {
    tracer_ = v;
}

void context::tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>&& v) {
    tracer_ = std::move(v);
}

const boost::optional<masd::dogen::diffing_configuration>& context::diffing_configuration() const {
    return diffing_configuration_;
}

boost::optional<masd::dogen::diffing_configuration>& context::diffing_configuration() {
    return diffing_configuration_;
}

void context::diffing_configuration(const boost::optional<masd::dogen::diffing_configuration>& v) {
    diffing_configuration_ = v;
}

void context::diffing_configuration(const boost::optional<masd::dogen::diffing_configuration>&& v) {
    diffing_configuration_ = std::move(v);
}

}