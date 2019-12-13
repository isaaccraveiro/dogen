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
#ifndef DOGEN_TRACING_TYPES_TRACER_HPP
#define DOGEN_TRACING_TYPES_TRACER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <sstream>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen.tracing/types/backend.hpp"
#include "dogen/types/tracing_configuration.hpp"
#include "dogen/types/database_configuration.hpp"

namespace dogen::tracing {

/**
 * @brief Handles all of the tracing-related work.
 */
class tracer final {
private:
    static boost::shared_ptr<tracing::backend>
    make_backend(const boost::optional<tracing_configuration>& tcfg,
        const boost::optional<database_configuration>& dbcfg);

public:
    tracer(const tracer&) = default;

public:
    tracer(const boost::optional<tracing_configuration>& tcfg,
        const boost::optional<database_configuration>& dbcfg);

public:
    const boost::shared_ptr<tracing::backend> backend() const {
        return backend_;
    }

private:
    template<typename Ioable>
    std::string to_string(const Ioable& ioable) const {
        if (!tracing_enabled_)
            return "";

        std::ostringstream s;
        s << ioable;
        return s.str();
    }

    static std::string generate_guid();

public:
    /**
     * @brief Writes an initial input to the filesystem.
     */
    template<typename Ioable>
    void add_initial_input(const std::string& input_id,
        const Ioable& input) const {
        if (backend_)
            backend_->start_tracing(input_id, to_string(input));
    }

    void add_references_graph(const std::string& root_vertex,
        const std::unordered_map<std::string, std::list<std::string>>&
        edges_per_model) const;

    void start_chain(const std::string& transform_id) const;
    void start_chain(const std::string& transform_id,
        const std::string& model_id) const;

    template<typename Ioable>
    void start_chain(const std::string& transform_id,
        const std::string& model_id,
        const Ioable& input) const {
        if (backend_) {
            backend_->start_chain(transform_id, generate_guid(),
                model_id, to_string(input));
        }
    }

    void start_transform(const std::string& transform_id) const;

    void start_transform(const std::string& transform_id,
        const std::string& model_id) const;

    template<typename Ioable>
    void start_transform(const std::string& transform_id,
        const std::string& model_id,
        const Ioable& input) const {
        if (backend_) {
            backend_->start_transform(transform_id, generate_guid(),
                model_id, to_string(input));
        }
    }

    void end_chain() const;

    template<typename Ioable>
    void end_chain(const Ioable& output) const {
        if (backend_)
            backend_->end_chain(to_string(output));
    }

    void end_transform() const;

    template<typename Ioable>
    void end_transform(const Ioable& output) const {
        if (backend_)
            backend_->end_transform(to_string(output));
    }

    void end_tracing() const;

public:
    bool operator==(const tracer& rhs) const;

private:
    const bool tracing_enabled_;
    boost::shared_ptr<tracing::backend> backend_;
};

}

#endif
