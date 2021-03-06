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
#ifndef DOGEN_INJECTION_TYPES_INJECTION_HPP
#define DOGEN_INJECTION_TYPES_INJECTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief Provides support for encoding and decoding of external models.
 *
 * An external model is defined as:
 *
 * @li a third-party format that is not owned or controlled by
 *     Dogen, such as Dia;
 * @li a Dogen format designed for interoperability (JSON).
 *
 * External models are converted into an intermediate format called
 * the @e injection model, because it is the original entry point into
 * the dogen processing pipeline. It also reflects the notion that we
 * are injecting external technical spaces into the MASD technical
 * technical space.
 *
 * A @e codec must be created for each external model that is to be
 * injected, providing a transformation between the native formats
 * and the injection model. The codecs are created in their own models,
 * following the naming convention injection.X for a given codec X.
 * They then register against the injection registrar. Note that for a
 * given file extension, there can only be one and only one codec to
 * manage it.
 */
namespace dogen::injection {
}

#endif
