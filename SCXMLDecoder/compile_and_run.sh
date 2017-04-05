#!/bin/sh


g++ -o run main.cpp CodeGenerator.cpp CodeSwitch.cpp MachineState.cpp Argument.cpp -std=c++0x
./run

chmod 777 Result/compile_basic.sh
chmod 777 Result/compile_advanced.sh

cd Result/
