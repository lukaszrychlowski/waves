#! /bin/bash

gcc src/main.c src/callbacks.c src/shaders.c src/gl.c -Iinclude -Llib -lglfw3 -lm -o main
