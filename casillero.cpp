#include "casillero.h"


Casillero::Casillero() {
    this->casilla = AIRE;
    this->contenidos = new Contenido;
}

Casillero::~Casillero() {
    delete this->contenidos;
}
