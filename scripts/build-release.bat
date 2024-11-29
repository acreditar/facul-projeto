@echo off

if not exist bin (
    mkdir bin
)

gcc -I .\include .\src\auth.c .\src\database.c .\src\main.c .\src\menu.c .\src\splash.c -O2 -g -Wall -o bin\horti.exe

if %ERRORLEVEL% neq 0 (
    exit /b %ERRORLEVEL%
)

exit /b
