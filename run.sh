#!/bin/bash

g++ $(find src -type f -iregex ".*\.cpp") -o ./bin/gb
chmod +x ./bin/gb
./bin/gb
