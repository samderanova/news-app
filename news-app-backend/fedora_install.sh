#!/bin/sh

# Set up install directory
mkdir install
cd install

# PostgreSQL
sudo dnf install libpq-devel postgresql

# spdlog
sudo dnf install spdlog-devel

# feedpp
sudo dnf install git autoconf libtool libxml2-devel make cmake libcurl-devel
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
sudo dnf install asio-devel
git clone https://github.com/CrowCpp/Crow.git
cd Crow
mkdir build
cd build
cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF
sudo make install

# mlpack
sudo dnf install mlpack-devel

# cleanup
rm -rf install
