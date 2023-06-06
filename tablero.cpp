#include <tablero.h>


Tablero::Tablero(){
    this->tablero = NULL;
    this->maxX = 0;
    this->maxY = 0;
    this->maxZ = 0;    
}

Tablero::Tablero(int x, int y, int z) {
    this->tablero = NULL;
    this->maxX = x;
    this->maxY = y;
    this->maxZ = z;
}

Tablero::~Tablero() {
}