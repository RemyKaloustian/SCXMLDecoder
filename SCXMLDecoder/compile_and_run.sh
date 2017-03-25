#!/bin/sh


g++ -o run main.cpp CodeGenerator.cpp CodeSwitch.cpp MachineState.cpp Argument.cpp -std=c++0x
./run