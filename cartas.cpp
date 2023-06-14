#include "cartas.h"

Carta::Carta() {
    srand(time(NULL));
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

Carta::~Carta() {
}

Carta::tipos Carta::getCarta(){
    return this->tipoDeCarta;
}

void Carta::usarCarta(Tablero *tablero, Carta::tipos numDeCarta, Ubicacion posicion, Jugador * jugador){
    switch (numDeCarta) {
    case 0 : 
        this->cartaAtaqueQuimico(tablero, posicion);
        break;
    case 1 :
        this->cartaAvionRadar(tablero, posicion);
        break;
    case 2 : 
        this->cartaBarco(tablero, posicion);
        break;
    case 3 : 
        this->cartaPotOfGreed(jugador);
        break;
    case 4 : 
        this->tipo5();
        break;
    case 5 : 
        this->tipo6();
        break;
    }
}

void Carta::cartaAtaqueQuimico(Tablero * tablero, Ubicacion posicion){
    const int RANGOATAQUEQUIMICO = 5;       // RANGOATAQUEQUIMICO debe ser impar
    int efectoAtaqueQuimico = 10;
    int radioCubo = RANGOATAQUEQUIMICO / 2;
    int i, k, j;
    Ubicacion nuevo;

    for(i = (-radioCubo); i <= radioCubo; i++){
        for (j = (-radioCubo); j <= radioCubo; j++){
            for (k = (-radioCubo); k <= radioCubo; k++){
                nuevo.x = posicion.x + i;
                nuevo.y = posicion.y + j;
                nuevo.z = posicion.z + k;
                if((i == 0) && (j == 0) && (k == 0)){
                    tablero->getCasillero(posicion)->desactivarCasilla(efectoAtaqueQuimico);
                } else if(abs(i) == 2 || abs(j) == 2 || abs(k) == 2){
                    tablero->getCasillero(nuevo)->desactivarCasilla(efectoAtaqueQuimico - 4);
                } else if(abs(i) == 1 || abs(j) == 1 || abs(k) == 1){
                    tablero->getCasillero(nuevo)->desactivarCasilla(efectoAtaqueQuimico - 2);
                }
            }
        }
    }
    if(tablero->validarCoordenadas(posicion)){

    }
}

//void Carta::cartaAvionRadar(Tablero * tablero, Ubicacion posicion)

//void Carta::cartaBarco(Tablero *tablero, Ubicacion posicion)

//void Carta::cartaPotOfGreed(Jugador * jugador)



