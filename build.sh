#!/bin/bash

appRunning=1

while [ $appRunning == 1 ]; do
    echo Compile and run [1], Compile [2], Run [3], Exit [4]
    read userChoice

    if [[ $userChoice == 1 ]]; then
        echo Compiling and running...
        g++ -c src/*.cpp -std=c++14 -Werror
        g++ *.o -o bin/Bomberman -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
        ./bin/Bomberman
    elif [[ $userChoice == 2 ]]; then
        echo Compiling...
        g++ -c src/*.cpp -std=c++14 -Werror
        g++ *.o -o bin/Bomberman -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    elif [[ $userChoice == 3 ]]; then
        ./bin/Bomberman
    elif [[ $userChoice == 4 ]]; then
        exit
    fi
done