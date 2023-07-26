@echo off

cmake -S . -B build

cmake --build build

build\Debug\test.exe

python test.py