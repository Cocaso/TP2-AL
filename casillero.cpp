#include "casillero.h"


Casillero::Casillero() {
    this->casilla = AIRE;
    this->contenidos = new Contenido;
}
void Casillero::cambiarTerreno(int binario){
    if (binario == 0){
        this->casilla = AGUA;
    } else if(binario == 1){
        this->casilla = TIERRA;
    }
}

Casillero::~Casillero() {
    delete this->contenidos;
}
