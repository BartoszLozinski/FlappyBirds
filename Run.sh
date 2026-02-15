#!/bin/bash

if [-d build]; then
    cd build
else
    ./BuildScript.sh
    cd build
fi

./FlappyBirds

