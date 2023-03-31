#! /bin/bash
rm Main.o
rm sfml-app
g++ -c Main.cpp
g++ Main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app