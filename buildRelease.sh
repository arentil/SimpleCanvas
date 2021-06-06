#!/bin/bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..     # or "Debug" for debug mode
make -j 4
