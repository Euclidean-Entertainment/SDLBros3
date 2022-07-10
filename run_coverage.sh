#!/bin/bash

mkdir coverage
cd coverage
cmake -DCMAKE_BUILD_TYPE="Coverage" ../
make -j4 $(cmake --build . --target help | grep coverage | awk '{printf $NF " "}')
rm -rf $(ls | grep -v '\_coverage$')
