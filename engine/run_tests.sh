#!/bin/sh

/usr/bin/valgrind -q --leak-check=yes ./build/run_tests
