g++ src/*.cpp -I./include/ -I./dependencies/SDL2/include/ -L./dependencies/SDL2/lib/ -std=c++11 -lmingw32 -lSDL2main -lSDL2 -o bin/conway.exe && cd bin && conway.exe
