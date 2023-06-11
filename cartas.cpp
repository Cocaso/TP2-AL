#include "cartas.h"

Carta::Carta() {
    switch (rand() % 6) {        //random mal 
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

void Carta::usarCarta(Tablero *tablero, Carta::tipos numDeCarta, unsigned int x, unsigned int y, unsigned int z){
    switch (numDeCarta) {
    case 0 : 
        this->cartaAtaqueQuimico(tablero, x, y, z);
        break;
    case 1 :
        this->cartaAvionRadar(tablero, x, y, z);
        break;
    case 2 : 
        this->cartaBarco(tablero, x, y, z);
        break;
    case 3 : 
        this->tipo4();
        break;
    case 4 : 
        this->tipo5();
        break;
    case 5 : 
        this->tipo6();
        break;
    }
}

void Carta::cartaAtaqueQuimico(Tablero *tablero, unsigned int x, unsigned int y, unsigned int z){
    int efectoAtaqueQuimico = 10;
    if(tablero->validarCoordenadas(x, y, z)){

    }
    for(int i=0; i < 2; i ++){
        if(i == 0){
            tablero->getCasillero(x, y, z)->desactivarCasilla(efectoAtaqueQuimico);
        } else {
            tablero->getCasillero(x + i, y + i, z + i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x + i, y + i, z - i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x + i, y - i, z - i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x + i, y - i, z + i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x - i, y + i, z + i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x - i, y + i, z - i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x - i, y - i, z + i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x - i, y - i, z - i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x, y + i, z + i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x, y + i, z - i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x, y - i, z + i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x, y - i, z - i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x + i, y, z + i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x + i, y, z - i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x - i, y, z + i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x - i, y, z - i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x + i, y + i, z)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x + i, y - i, z)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x - i, y + i, z)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x - i, y - i, z)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x + i, y, z)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x - i, y, z)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x, y + i, z)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x, y - i, z)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x, y, z + i)->desactivarCasilla(efectoAtaqueQuimico);
            tablero->getCasillero(x, y, z - i)->desactivarCasilla(efectoAtaqueQuimico);
        }
        efectoAtaqueQuimico = efectoAtaqueQuimico - 2;
    }
    
}

void Carta::cartaAvionRadar(Tablero *tablero, unsigned int x, unsigned int y, unsigned int z){
}

void Carta::cartaBarco(Tablero *tablero, unsigned int x, unsigned int y, unsigned int z){
    
}



Carta::tipos Carta::getCarta(){
    return this->tipoDeCarta;
}

Carta::~Carta() {
}