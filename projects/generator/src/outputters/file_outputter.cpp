/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/outputters/file_outputter.hpp"

namespace {

static dogen::utility::log::logger
lg(dogen::utility::log::logger_factory("file_outputter"));

const std::string outputter_name("file output");
const std::string writing_file_message("Writing file: ");
const std::string wrote_file_message("Wrote file: ");
const std::string using_target_dir_message("Using Target directory: ");
const std::string created_target_dir_message("Created target directory: ");

const std::string error_generating_files("error generating file: ");
const std::string path_size_warning("Full path exceeds 255 bytes.");

}

namespace dogen {
namespace generator {
namespace outputters {

file_outputter::file_outputter(bool verbose, bool force_write)
    : verbose_(verbose), force_write_(force_write) {}

void file_outputter::
log_writing_file(boost::filesystem::path path) const {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << writing_file_message << path.string();
    if (path.string().size() > 255)
        BOOST_LOG_SEV(lg, warn) << path_size_warning << path.string();
}

void file_outputter::
log_wrote_file(boost::filesystem::path path) const {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << wrote_file_message << path.string();
}

void file_outputter::
log_created_directories(bool created, boost::filesystem::path directory) const {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << (created ? created_target_dir_message :
        using_target_dir_message) << directory.string();
}

void file_outputter::log_no_content_changes() const {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << "File contents have not changed, "
                             << "and force write is false so not writing";
}

void file_outputter::log_content_changes() const {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << "File contents have changed, need to write";
}

bool file_outputter::writing_needed(outputter::value_entry_type value) const {
    if (force_write_)
        return true;

    const boost::filesystem::path path(value.first);
    const std::string contents(value.second);

    if (!boost::filesystem::exists(path))
        return true;

    using dogen::utility::filesystem::read_file_content;
    std::string existing_contents(read_file_content(path));

    if (existing_contents == contents) {
        log_no_content_changes();
        return false;
    }
    log_content_changes();
    return true;
}

void file_outputter::to_file(outputter::value_entry_type value) const {
    try {
        const boost::filesystem::path path(value.first);
        const std::string contents(value.second);
        log_writing_file(path.string());

        boost::filesystem::path dir(path);
        dir.remove_filename();

        using boost::filesystem::create_directories;
        const bool dir_exists(!create_directories(dir));
        log_created_directories(!dir_exists, dir);

        if (!dir_exists || writing_needed(value)) {
            using dogen::utility::filesystem::write_file_content;
            write_file_content(path, contents);
            log_wrote_file(path.string());
        }
    } catch(const std::exception& e) {
        const std::string message(error_generating_files);
        throw dogen::utility::exception::exception(message + e.what());
    }
}

std::string file_outputter::outputter_name() {
    return ::outputter_name;
}

void file_outputter::
output(outputter::value_type value) const {
    for (const auto pair : value)
        to_file(pair);
}

} } }
