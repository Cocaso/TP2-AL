#include "casillero.h"


Casillero::Casillero() {
    this->casilla = AIRE;
    this->contenido = new (Contenido);
}


void Casillero::cambiarTerreno(int binario){
    if (binario == 0){
        this->casilla = AGUA;
    } else if(binario == 1){
        this->casilla = TIERRA;
    }
}


void Casillero::desactivarCasilla(int cantidadTurnosCasillaInactiva){
    this->contenido->turnosInactivo = cantidadTurnosCasillaInactiva;
    this->contenido->artillerias = VACIO;
}


void Casillero::disminuirTurnosInactivo(){
    if (!(getTurnosInactivo() > 0)){
        throw("ASI NO FUNCA PA");
    };
    this->contenido->turnosInactivo -= 1;
}


int Casillero::getTurnosInactivo(){
    return this->contenido->turnosInactivo;
}

void Casillero::ponerArtilleriaVacia(){
    this->artilleria = VACIO;
}

void Casillero::ponerArtilleria(Artilleria artilleria, int numJugador){
    this->artilleria = artilleria;
    this->contenido->jugador = numJugador;
}

bool Casillero::comprobarTerreno(Artilleria unidad){
    switch (unidad) {
        case SOLDADO:
            if (this->terreno == AGUA || this->terreno == TIERRA){
                return true
            }
            break;
        case MINA:
            if (this->terreno == AGUA || this->terreno == TIERRA){
                return true
            }
            break;
        case BARCO:
            if (this->terreno == AGUA){
                return true
            }
            break;
        case AVION:
            if (this->terreno == AIRE){
                return true
            }
            break;
        default:
            // :)
            break;
    }
    return false;
}

Artilleria Casillero::devolverArtilleria(){
    return this->contenido->artillerias;
}

int Casillero::devolverNroJugador(){
    return this->contenido->jugador;
}

int Casillero::devolverNroSoldado(){
    return this->contenido->numSoldado;
}

Casillero::~Casillero() {
    delete this->contenido;
}
