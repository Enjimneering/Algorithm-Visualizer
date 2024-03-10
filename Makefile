all:
	gcc main.c -I "C:\SDL2-2.30.0\64_bit-w64-mingw32\include"  -L "C:\SDL2-2.30.0\64_bit-w64-mingw32\lib" -o main -lmingw32 -lSDL2main -lSDL2
