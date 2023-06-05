#ifndef TABLERO_H
#define TABLERO_H

#include "listaBase.h"
#include "casillero.h"

class Tablero {
private:
    Lista <Lista<Casillero*>*>* tablero;
    int maxX;
    int maxY;
    int maxZ;
public:
    Tablero(/* args */);
    ~Tablero();
};
Tablero::Tablero(){
    this->tablero = NULL;   
    this->maxX = 0;
    this->maxY = 0;
    this->maxZ = 0;    
}

Tablero::~Tablero() {
}

void Tablero::setSize(int x, int y, int z) {
    this->maxX = x;
    this->maxY = y;
    this->maxZ = z;
}







#endif