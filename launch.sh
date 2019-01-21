#!/bin/sh

cd build && conan install .. --build=missing -s compiler.libcxx=libstdc++11 && cmake .. -G "Unix Makefiles" && cmake --build . && cp bin/rtype-client ../ && cp bin/rtype-server ../
