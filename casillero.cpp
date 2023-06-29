#include "casillero.h"

Casillero::Casillero() {
    this->terreno = AIRE;
    this->toxico = false;
    this->jugador = 0;
    this->numTropa = 0;
    this->artilleria = VACIO;
    this->turnosInactivo = 0;
}

Casillero::~Casillero() {
}

int Casillero::devolverTurnosInactivos(){
    return this->turnosInactivo;
}

void Casillero::cambiarTerreno(int binario){
    if (binario == 0){
        this->terreno = AGUA;
    } else if(binario == 1){
        this->terreno = TIERRA;
    }
}

void Casillero::desactivarCasilla(int cantidadTurnosCasillaInactiva){
    this->turnosInactivo = cantidadTurnosCasillaInactiva;
    this->vaciarCasillero();
    //Modularizar todo esto lmao
}

bool Casillero::disminuirTurnosInactivo(){
    this->turnosInactivo --;
    return (this->turnosInactivo == 0);
}

//fijarse dónde se usó y cambiarle el nombre a "vaciarCasillero"
void Casillero::vaciarCasillero(){
    this->artilleria =  VACIO;
    this->jugador = 0;
    this->numTropa = 0;
}

//Unir con la de abajo e implementas los numTropa de todas las tropas
void Casillero::ponerArtilleria(Artilleria artilleria, int numJugador){
    this->artilleria = artilleria;
    this->jugador = numJugador;
}

void Casillero::ponerArtilleria(Artilleria artilleria, int numJugador, int numTropa){
    this->artilleria = artilleria;
    this->jugador = numJugador;
    this->numTropa = numTropa;
}

bool Casillero::comprobarTerreno(Artilleria unidad){
    switch (unidad) {
        case SOLDADO:
            if (this->terreno == AGUA || this->terreno == TIERRA){
                return true;
            }
            break;
        case MINA:
            if (this->terreno == AGUA || this->terreno == TIERRA){
                return true;
            }
            break;
        case BARCO:
            if (this->terreno == AGUA){
                return true;
            }
            break;
        case AVION:
            if (this->terreno == AIRE){
                return true;
            }
            break;
        case VACIO:
            return true; 
        default:
            // :)
            break;
    }
    return false;
}

bool Casillero::comprobarEstado(){
    return (this->turnosInactivo == 0);
}

Artilleria Casillero::devolverArtilleria(){
    return this->artilleria;
}

bool Casillero::esToxico(){
    return this->toxico;
}

void Casillero::setToxico(bool toxico){
    this->toxico = toxico;
}

int Casillero::devolverNroJugador(){
    return this->jugador;
}

int Casillero::devolverNroTropa(){
    return this->numTropa;
}

Terreno Casillero::devolverTerreno(){
    return this->terreno;
}

