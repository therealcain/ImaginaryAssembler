#!/bin/bash

make DEBUG=1
valgrind --leak-check=full --track-origins=yes -s build/Assembler tests/test1.as
