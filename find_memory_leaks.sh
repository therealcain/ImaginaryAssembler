#!/bin/bash

make DEBUG=1
valgrind --leak-check=full build/Assembler tests/*.as
