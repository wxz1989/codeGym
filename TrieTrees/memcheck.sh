#!/bin/bash
valgrind -v --tool=memcheck --leak-check=yes --track-origins=yes ./TrieTest __test_mode__ 0
