#!/bin/bash

g++ -std=gnu++1z -s -Wall -O3 -pthread $(find . -type f -iregex ".*\.cpp") -o shell.bin
