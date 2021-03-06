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
#include <boost/make_shared.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.m2t.csharp/types/transforms/visual_studio/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/visual_studio/project_transform.hpp"

namespace dogen::m2t::csharp::transforms::visual_studio {

std::string project_transform::static_id() {
    return traits::project_archetype_qn();
}

std::string project_transform::id() const {
    static auto r(physical_meta_name().qualified());
    return r;
}

physical::entities::meta_name
project_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static const auto r(meta_name_factory::make(csharp::traits::backend_sn(),
        traits::facet_sn(), traits::project_archetype_sn()));
    return r;
}

const logical::entities::name&
project_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_visual_studio_project_name());
    return r;
}

boost::filesystem::path project_transform::
full_path(const formattables::locator& l, const logical::entities::name& n) const {
    auto temp(n);
    temp.simple(boost::algorithm::join(n.location().model_modules(), ".") + ".csproj");
    return l.make_full_path_for_project(temp, static_id());
}

std::list<std::string> project_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

void project_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), a);
    using logical::entities::visual_studio::project;
    const auto& proj(ast.as<project>(static_id(), e));

ast.stream() << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
ast.stream() << "<Project DefaultTargets=\"Build\" ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">" << std::endl;
ast.stream() << "  <PropertyGroup>" << std::endl;
ast.stream() << "    <Configuration Condition=\" '$(Configuration)' == '' \">Debug</Configuration>" << std::endl;
ast.stream() << "    <Platform Condition=\" '$(Platform)' == '' \">AnyCPU</Platform>" << std::endl;
ast.stream() << "    <ProjectGuid>{" << proj.guid() << "}</ProjectGuid>" << std::endl;
ast.stream() << "    <OutputType>Library</OutputType>" << std::endl;
ast.stream() << "    <RootNamespace>" << proj.project_name() << "</RootNamespace>" << std::endl;
ast.stream() << "    <AssemblyName>" << proj.project_name() << "</AssemblyName>" << std::endl;
ast.stream() << "  </PropertyGroup>" << std::endl;
ast.stream() << "  <PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Debug|AnyCPU' \">" << std::endl;
ast.stream() << "    <DebugSymbols>true</DebugSymbols>" << std::endl;
ast.stream() << "    <DebugType>full</DebugType>" << std::endl;
ast.stream() << "    <Optimize>false</Optimize>" << std::endl;
ast.stream() << "    <OutputPath>bin\\Debug</OutputPath>" << std::endl;
ast.stream() << "    <DefineConstants>DEBUG;</DefineConstants>" << std::endl;
ast.stream() << "    <ErrorReport>prompt</ErrorReport>" << std::endl;
ast.stream() << "    <WarningLevel>4</WarningLevel>" << std::endl;
ast.stream() << "    <ConsolePause>false</ConsolePause>" << std::endl;
ast.stream() << "  </PropertyGroup>" << std::endl;
ast.stream() << "  <PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Release|AnyCPU' \">" << std::endl;
ast.stream() << "    <DebugType>full</DebugType>" << std::endl;
ast.stream() << "    <Optimize>true</Optimize>" << std::endl;
ast.stream() << "    <OutputPath>bin\\Release</OutputPath>" << std::endl;
ast.stream() << "    <ErrorReport>prompt</ErrorReport>" << std::endl;
ast.stream() << "    <WarningLevel>4</WarningLevel>" << std::endl;
ast.stream() << "    <ConsolePause>false</ConsolePause>" << std::endl;
ast.stream() << "  </PropertyGroup>" << std::endl;
ast.stream() << "  <ItemGroup>" << std::endl;
ast.stream() << "    <Reference Include=\"System\" />" << std::endl;
ast.stream() << "  </ItemGroup>" << std::endl;
        for (const auto& ig : proj.item_groups()) {
ast.stream() << "  <ItemGroup>" << std::endl;
            for (const auto& i : ig.items())
ast.stream() << "    <" << i.name() << " Include=\"" << i.include() << "\" />" << std::endl;
ast.stream() << "  </ItemGroup>" << std::endl;
        }
ast.stream() << "  <Import Project=\"$(MSBuildBinPath)\\Microsoft.CSharp.targets\" />" << std::endl;
ast.stream() << "</Project>" << std::endl;
    ast.update_artefact();
}
}
