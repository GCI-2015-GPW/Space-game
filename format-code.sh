#!/bin/bash


cd src

clang-format -style=file -i $(find . -name "*.cpp") $(find . -name "*.h") $(find . -name "*.cc")
