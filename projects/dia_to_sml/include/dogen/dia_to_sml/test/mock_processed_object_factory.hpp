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
#ifndef DOGEN_DIA_TEST_MOCK_PROCESSED_OBJECT_FACTORY_HPP
#define DOGEN_DIA_TEST_MOCK_PROCESSED_OBJECT_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <array>
#include "dogen/dia_to_sml/types/object_types.hpp"
#include "dogen/dia_to_sml/types/stereotypes.hpp"
#include "dogen/dia_to_sml/types/processed_object.hpp"

namespace dogen {
namespace dia_to_sml {
namespace test {

/**
 * @brief Generates mock dia objects that are more realistic than the
 * test data objects.
 */
class mock_processed_object_factory {
public:
    /**
     * @brief Given a number, returns a dia object ID.
     */
    static std::string to_oject_id(const unsigned int n);

    /**
     * @brief Generates a UML note without a dogen marker.
     *
     * @param n identifier used for object ID generation.
     */
    static processed_object build_uml_note(const unsigned int n = 0);

    /**
     * @brief Generates a UML note with a dogen comment marker.
     *
     * @param n identifier used for object ID generation.
     */
    static processed_object
    build_uml_note_with_marker(const unsigned int n = 0);

    /**
     * @brief Generates an empty UML note.
     *
     * @param n identifier used for object ID generation.
     */
    static processed_object build_empty_uml_note(const unsigned int n = 0);

    /**
     * @brief Generates a UML note inside a large package.
     *
     * @param n identifier used for object ID generation.
     */
    static std::array<processed_object, 2>
    build_uml_note_inside_large_package(unsigned int n = 0);

    /**
     * @brief Generates an empty UML note inside a large package.
     *
     * @param n identifier used for object ID generation.
     */
    static std::array<processed_object, 2>
    build_empty_uml_note_inside_large_package(unsigned int n = 0);

    /**
     * @brief Generates an empty UML note inside a large package.
     *
     * @param n identifier used for object ID generation.
     */
    static std::array<processed_object, 2>
    build_uml_note_with_marker_inside_large_package(unsigned int n = 0);

    /**
     * @brief Generates a new UML class.
     *
     * @param n identifier used for object ID generation.
     */
    static processed_object build_class(const unsigned int n = 0);

    /**
     * @brief Generates a new UML class with an empty name.
     *
     * @param n identifier used for object ID generation.
     */
    static processed_object build_empty_named_class(const unsigned int n = 0);

    /**
     * @brief Generates a new UML class with the given stereotype.
     *
     * @param n identifier used for object ID generation.
     */
    static processed_object build_stereotyped_class(
        const stereotypes st, const unsigned int n = 0);

    /**
     * @brief Generates a new UML large package.
     *
     * @param n identifier used for object ID generation.
     */
    static processed_object build_large_package(const unsigned int n = 0);

    /**
     * @brief Generates a UML class inside a large package, plus the
     * large package itself.
     *
     * @param n identifier used for object ID generation.
     */
    static std::array<processed_object, 3>
    build_class_inside_two_large_packages(unsigned int n = 0);

    /**
     * @brief Generates a UML class inside a large package, itself
     * inside a large package.
     *
     * @param n identifier used for object ID generation.
     */
    static std::array<processed_object, 2>
    build_class_inside_large_package(unsigned int n = 0);

    /**
     * @brief Generates two UML classes and a generalisation between
     * the two.
     *
     * @param n identifier used for object ID generation.
     */
    static std::array<processed_object, 3>
    build_generalization(unsigned int n = 0);

    /**
     * @brief Generates two UML classes and a generalisation between
     * the two, and places all objects inside a package.
     *
     * @param n identifier used for object ID generation.
     */
    static std::array<processed_object, 4>
    build_generalization_inside_large_package(unsigned int n = 0);

    /**
     * @brief Generates two UML classes and an association between
     * the two.
     *
     * @param n identifier used for object ID generation.
     */
    static std::array<processed_object, 3>
    build_association(unsigned int n = 0);

    /**
     * @brief Generates objects directly connected in a cycle.
     *
     * @param n identifier used for object ID generation.
     */
    static std::array<processed_object, 4>
    build_first_degree_cycle(unsigned int n = 0);
};

} } }

#endif
