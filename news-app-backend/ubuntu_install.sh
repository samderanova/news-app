#!/bin/sh

# Set up install directory
mkdir install
cd install

# PostgreSQL
sudo apt install libpq-dev postgresql

# spdlog
sudo apt install libspdlog-dev

# feedpp
sudo apt install git autoconf libtool libxml2-dev libxml-doc make cmake
git clone https://github.com/kamarya/feedpp.git
cd feedpp
./autogen.sh
mkdir release
cd release
../configure
make -j8
make check
sudo make install
cd ../..

# crow
sudo apt install libasio-dev
git clone https://github.com/CrowCpp/Crow.git
cd Crow
mkdir build
cd build
cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF
sudo make install

# mlpack
sudo apt install libmlpack-dev

# cleanup
rm -rf install
