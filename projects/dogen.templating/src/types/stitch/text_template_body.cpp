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
#include "dogen.templating/types/stitch/text_template_body.hpp"

namespace dogen::templating::stitch {

text_template_body::text_template_body(
    const std::list<std::pair<std::string, std::string> >& tagged_values,
    const std::list<dogen::templating::stitch::line>& lines)
    : tagged_values_(tagged_values),
      lines_(lines) { }

void text_template_body::swap(text_template_body& other) noexcept {
    using std::swap;
    swap(tagged_values_, other.tagged_values_);
    swap(lines_, other.lines_);
}

bool text_template_body::operator==(const text_template_body& rhs) const {
    return tagged_values_ == rhs.tagged_values_ &&
        lines_ == rhs.lines_;
}

text_template_body& text_template_body::operator=(text_template_body other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::pair<std::string, std::string> >& text_template_body::tagged_values() const {
    return tagged_values_;
}

std::list<std::pair<std::string, std::string> >& text_template_body::tagged_values() {
    return tagged_values_;
}

void text_template_body::tagged_values(const std::list<std::pair<std::string, std::string> >& v) {
    tagged_values_ = v;
}

void text_template_body::tagged_values(const std::list<std::pair<std::string, std::string> >&& v) {
    tagged_values_ = std::move(v);
}

const std::list<dogen::templating::stitch::line>& text_template_body::lines() const {
    return lines_;
}

std::list<dogen::templating::stitch::line>& text_template_body::lines() {
    return lines_;
}

void text_template_body::lines(const std::list<dogen::templating::stitch::line>& v) {
    lines_ = v;
}

void text_template_body::lines(const std::list<dogen::templating::stitch::line>&& v) {
    lines_ = std::move(v);
}

}
