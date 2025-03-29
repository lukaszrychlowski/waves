#! /bin/bash

gcc src/main.c src/callbacks.c src/window.c src/renderer.c  src/gl.c -Iinclude -Llib -lglfw3 -lm -o main
