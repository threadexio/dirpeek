#!/bin/bash

if [ "$EUID" -ne 0 ]; then
	echo "This script requires root privileges"
	exit
fi

rm -drf ./build/ 2>/dev/null
mkdir -p ./build/ && cd ./build/

# Install boost program options library from apt
apt install -y 'libboost-program-options-dev'

# Ensure git, cmake, make and the openssl library are installed
apt install --no-install-recommends -y git make cmake libssl-dev openssl

# Clone the cpr c++ library and install it
git clone https://github.com/whoshuu/cpr
cd cpr
mkdir -p ./build/ && cd ./build/
cmake .. -DUSE_SYSTEM_CURL=OFF
make
make install

# Go to the root of the project
cd ../../../

# Reload ldconfig
ldconfig

# Compile it
rm ./binaries/dirpeek 2>/dev/null
echo Compiling...
./compile.sh
