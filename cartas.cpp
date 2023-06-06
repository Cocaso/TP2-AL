#include <cartas.h>

Carta::Carta() {
    switch ((1+ (rand() % 6)))
    {
    case 0 : 
        this->tipoDeCarta = ATAQUEQUIMICO;
        break;
    case 1 :
        this->tipoDeCarta = AVIONRADAR;
        break;
    case 2 : 
        this->tipoDeCarta = BARCO;
        break;
    case 3 : 
        this->tipoDeCarta = FUTURO;
        break;
    case 4 : 
        this->tipoDeCarta = FUTURO;
        break;
    case 5 : 
        this->tipoDeCarta = FUTURO;
        break;
    }
}

Carta::~Carta() {
}