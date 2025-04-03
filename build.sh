#! /bin/bash

gcc src/main.c src/callbacks.c src/window.c src/renderer.c src/sound.c src/gl.c -Iinclude -Llib -lglfw3 -lm -pthread -lasound -o main -Wall -Wextra -Wpedantic -Wcast-align
