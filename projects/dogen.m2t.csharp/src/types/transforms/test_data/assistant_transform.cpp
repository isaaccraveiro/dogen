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
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/test_data/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/test_data/assistant_transform.hpp"

namespace dogen::m2t::csharp::transforms::test_data {

std::string assistant_transform::static_id() {
    return traits::assistant_archetype_qn();
}

std::string assistant_transform::id() const {
    return static_id();
}

physical::entities::meta_name
assistant_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static const auto r(meta_name_factory::make(csharp::traits::backend_sn(),
        traits::facet_sn(), traits::assistant_archetype_sn()));
    return r;
}

const logical::entities::name& assistant_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_assistant_name());
    return r;
}

boost::filesystem::path assistant_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> assistant_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

void assistant_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), a);
    {
        const auto sn(e.name().simple());
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
ast.stream() << "using System;" << std::endl;
ast.stream() << "using System.Collections;" << std::endl;
ast.stream() << "using System.Collections.Specialized;" << std::endl;
ast.stream() << std::endl;
            const auto ns(ast.make_namespaces(e.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << "    /// <summary>" << std::endl;
ast.stream() << "    /// Provides helper methods for the sequence generators." << std::endl;
ast.stream() << "    /// </summary>" << std::endl;
ast.stream() << "    static class " << sn << "SequenceGenerator" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        private const int SequenceSize = 10;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static object CreateObject(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return \"this is an object: \" + Convert.ToString(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static string CreateString(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return \"this is a string: \" + Convert.ToString(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static byte CreateByte(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToByte(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static sbyte CreateShortByte(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToSByte(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static int CreateInt(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToInt32(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static uint CreateUInt(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return position;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static short CreateShort(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToInt16(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static ushort CreateUShort(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToUInt16(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static long CreateLong(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToInt64(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static ulong CreateULong(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToUInt64(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static float CreateFloat(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToSingle(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static double CreateDouble(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToDouble(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static char CreateChar(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToChar(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static bool CreateBool(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return position % 2 == 0;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static decimal CreateDecimal(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return Convert.ToDecimal(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static IEnumerable CreateIEnumerable(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return CreateArrayList(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static ICollection CreateICollection(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return CreateArrayList(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static IList CreateIList(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return CreateArrayList(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static ArrayList CreateArrayList(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var result = new ArrayList();" << std::endl;
ast.stream() << "            for (uint i = 0; i < SequenceSize; i++)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                switch((position + i) % 5)" << std::endl;
ast.stream() << "                {" << std::endl;
ast.stream() << "                case 0: result.Add(CreateString(position + i)); break;" << std::endl;
ast.stream() << "                case 1: result.Add(CreateByte(position + i)); break;" << std::endl;
ast.stream() << "                case 2: result.Add(CreateInt(position + i)); break;" << std::endl;
ast.stream() << "                case 3: result.Add(CreateLong(position + i)); break;" << std::endl;
ast.stream() << "                case 4: result.Add(CreateFloat(position + i)); break;" << std::endl;
ast.stream() << "                case 5: result.Add(CreateDecimal(position + i)); break;" << std::endl;
ast.stream() << "                default: result.Add(CreateBool(position + i)); break;" << std::endl;
ast.stream() << "                }" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            return result;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static IDictionary CreateIDictionary(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return CreateHashtable(position);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static Hashtable CreateHashtable(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var result = new Hashtable();" << std::endl;
ast.stream() << "            for (uint i = 0; i < SequenceSize; i++)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                result.Add(\"key_\" + position + i, \"value_\" + position + i);" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            return result;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static HybridDictionary CreateHybridDictionary(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var result = new HybridDictionary();" << std::endl;
ast.stream() << "            for (uint i = 0; i < SequenceSize; i++)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                result.Add(\"key_\" + position + i, \"value_\" + position + i);" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            return result;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static NameValueCollection CreateNameValueCollection(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var result = new NameValueCollection();" << std::endl;
ast.stream() << "            for (uint i = 0; i < SequenceSize; i++)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                result.Add(\"key_\" + position + i, \"value_\" + position + i);" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            return result;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static BitArray CreateBitArray(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var result = new BitArray(SequenceSize);" << std::endl;
ast.stream() << "            for (int i = 0; i < SequenceSize; i++)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                result[i] = position % 2 == 0;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            return result;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static Queue CreateQueue(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var result = new Queue();" << std::endl;
ast.stream() << "            for (int i = 0; i < SequenceSize; i++)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                result.Enqueue(\"value_\" + position + i);" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            return result;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static Stack CreateStack(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var result = new Stack();" << std::endl;
ast.stream() << "            for (int i = 0; i < SequenceSize; i++)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                result.Push(\"value_\" + position + i);" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            return result;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static SortedList CreateSortedList(uint position)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var result = new SortedList();" << std::endl;
ast.stream() << "            for (int i = 0; i < SequenceSize; i++)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                result.Add(\"key_\" + position + i, \"value_\" + position + i);" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "            return result;" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "    }" << std::endl;
        }
    } // sbf
    ast.update_artefact();
}
}
