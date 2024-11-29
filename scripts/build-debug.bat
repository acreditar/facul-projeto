@echo off

if not exist bin (
    mkdir bin
)

gcc -I .\include .\src\auth.c .\src\database.c .\src\main.c .\src\menu.c .\src\splash.c -DDEBUG -g -Wall -o bin\program.exe

if %ERRORLEVEL% neq 0 (
    exit /b %ERRORLEVEL%
)

exit /b
