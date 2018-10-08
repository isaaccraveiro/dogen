#!/bin/bash
#
# Copyright (C) 2012-2016 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be  useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#

#
# deps
#
package="vcpkg-export-20181008-182335.zip"
input_location="https://www.dropbox.com/s/6qobuvq66edi0ha/${package}?dl=0"
output_location="/tmp/${package}"
extract_dir="/tmp/dogen_deps"
wget --no-check-certificate ${input_location} -O ${output_location}
mkdir ${extract_dir}
unzip ${output_location} -d ${extract_dir}
ls ${extract_dir}/*

#
# common repos
#
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

#
# clang
#
if [ "$CXX" == "clang++" ]; then
    server="http://apt.llvm.org/trusty/"
    sources="/etc/apt/sources.list"
    trusty="llvm-toolchain-trusty"
    sudo sh -c "echo 'deb ${server} ${trusty}-6.0 main' >> ${sources}"
    sudo sh -c "echo 'deb ${server} ${trusty}-6.0 main' >> ${sources}"
    wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | sudo apt-key add -
    sudo apt-get update -qq

    sudo apt-get install --allow-unauthenticated -qq clang-6.0
    which clang-6.0
    export CXX="clang++-6.0" CC="clang-6.0"
fi

#
# g++
#
if [ "$CXX" = "g++" ]; then
    sudo apt-get install -qq g++-8
    export CXX="g++-8" CC="gcc-8" GCOV="gcov-8"
fi

#
# ninja
#
sudo apt-get install ninja-build

#
# cmake
#
cmake_name="cmake-3.4.1-Linux-x86_64"
cmake_tar="${cmake_name}.tar.gz"
cmake_input="https://cmake.org/files/v3.4/${cmake_tar}"
cmake_output="/tmp/${cmake_tar}"
wget --no-check-certificate ${cmake_input} -O ${cmake_output}
tar xf ${cmake_output} -C /tmp
sudo cp -r /tmp/${cmake_name}/* /usr
rm -rf ${cmake_output} /tmp/${cmake_name}

#
# coverage
#
sudo pip install cpp-coveralls==0.3.12

sudo apt-get clean
echo "Cleaned cache."
