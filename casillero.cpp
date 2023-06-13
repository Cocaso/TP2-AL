#include "casillero.h"


Casillero::Casillero() {
    this->terreno = AIRE;
    this->contenido = new (Contenido);
}

Casillero::~Casillero() {
    delete this->contenido;
}

void Casillero::cambiarTerreno(int binario){
    if (binario == 0){
        this->terreno = AGUA;
    } else if(binario == 1){
        this->terreno = TIERRA;
    }
}

void Casillero::desactivarCasilla(int cantidadTurnosCasillaInactiva){
    this->contenido->turnosInactivo = cantidadTurnosCasillaInactiva;

    //Modularizar todo esto lmao
    this->contenido->artilleria = VACIO;
    this->contenido->jugador = 0;
    this->contenido->numSoldado = 0;
    this->contenido->municionDelBarco = 0;
}

void Casillero::disminuirTurnosInactivo(){
    if (this->contenido->turnosInactivo == 0){
        throw("ASI NO FUNCA PA");
    } else {
        this->contenido->turnosInactivo -= 1;
    }
    
}

void Casillero::ponerArtilleria(Artilleria artilleria){
    this->contenido->artilleria = artilleria;
}

void Casillero::ponerArtilleria(Artilleria artilleria, int numJugador){
    this->contenido->artilleria = artilleria;
    this->contenido->jugador = numJugador;
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
        default:
            // :)
            break;
    }
    return false;
}

Artilleria Casillero::devolverArtilleria(){
    return this->contenido->artilleria;
}

int Casillero::devolverNroJugador(){
    return this->contenido->jugador;
}

int Casillero::devolverNroSoldado(){
    return this->contenido->numSoldado;
}


