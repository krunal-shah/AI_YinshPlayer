#!/bin/bash

## This is to run the first program main.cpp

if [ -e "dumbot-v0-kshah" ]; then
	./dumbot-v0-kshah
else
    echo "First run compile.sh to compile the code"
fi
