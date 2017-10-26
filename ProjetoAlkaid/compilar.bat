echo off

:COMPILAR
cls
gcc -I C:\allegro-5.0.10-mingw-4.7.0\include -c -W -Wall -pedantic -std=c11 main.c objetos.c movimentacao.c funcoes.c
gcc -o main.exe main.o objetos.o movimentacao.o funcoes.o C:\allegro-5.0.10-mingw-4.7.0\lib\liballegro-5.0.10-monolith-mt.a
echo "COMPILAR NOVAMENTE"
pause
goto COMPILAR:
