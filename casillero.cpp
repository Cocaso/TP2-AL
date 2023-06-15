#include "casillero.h"


Casillero::Casillero() {
    this->terreno = AIRE;
    this->contenido = new (Contenido);
}

Casillero::~Casillero() {
    delete this->contenido;
}

int Casillero::devolverTurnosInactivos(){
    return this->contenido->turnosInactivo;
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
    this->contenido->numTropa = 0;
    this->contenido->municionDelBarco = 0;
}

bool Casillero::disminuirTurnosInactivo(){
    this->contenido->turnosInactivo -- ;
    return (this->contenido->turnosInactivo == 0);
}

//fijarse dónde se usó y camiarle el nombre a "vaciarCasillero"
void Casillero::ponerArtilleria(Artilleria artilleria){
    this->contenido->artilleria = artilleria;
    this->contenido->jugador = 0;
    this->contenido->numTropa = 0;
    this->contenido->municionDelBarco = 0;
}

//Unir con la de abajo e implementas los numTropa de todas las tropas
void Casillero::ponerArtilleria(Artilleria artilleria, int numJugador){
    this->contenido->artilleria = artilleria;
    this->contenido->jugador = numJugador;
    if (artilleria == BARCO){
        this->contenido->municionDelBarco = 5;
    }
}

void Casillero::ponerArtilleria(Artilleria artilleria, int numJugador, int numTropa){
    this->contenido->artilleria = artilleria;
    this->contenido->jugador = numJugador;
    this->contenido->numTropa = numTropa;
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

bool Casillero::comprobarEstado(){
    return (this->contenido->turnosInactivo == 0);
}

Artilleria Casillero::devolverArtilleria(){
    return this->contenido->artilleria;
}

bool Casillero::esToxico(){
    return this->contenido->toxico;
}

void Casillero::setToxico(bool toxico){
    this->contenido->toxico = toxico;
}

int Casillero::devolverNroJugador(){
    return this->contenido->jugador;
}

int Casillero::devolverNroTropa(){ //Falta generalizar a devolverNroTropa
    return this->contenido->numTropa;
}

Terreno Casillero::devolverTerreno(){
    return this->terreno;
}

