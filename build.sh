#!/bin/bash

appRunning=1

while [ $appRunning == 1 ]; do
    echo -e "\e[96mCompile and run [1], Compile [2], Run [3], Exit [4]\e[39m"
    read userChoice

    if [[ $userChoice == 1 ]]; then
        echo -e "\e[93mCompiling and running...\e[39m"
        g++ -c $(find . -type f -iregex ".*\.cpp") -std=c++14 -Werror
        g++ *.o -o bin/Bomberman -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
        ./bin/Bomberman
    elif [[ $userChoice == 2 ]]; then
        echo -e "\e[93mCompiling...\e[39m"
        g++ -c $(find . -type f -iregex ".*\.cpp") -std=c++14 -Werror
        g++ *.o -o bin/Bomberman -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    elif [[ $userChoice == 3 ]]; then
        ./bin/Bomberman
    elif [[ $userChoice == 4 ]]; then
        exit
    fi
done
