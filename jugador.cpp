#include "jugador.h"

Jugador::Jugador(){
    this->vidas = 0;
    this->numDeJugador = 0;
    this->soldados = NULL;
    this->cartas = NULL;
}

Jugador::Jugador(int nroJugador, int vidas){
    this->vidas = vidas;
    this->numDeJugador = nroJugador;
    this->soldados = new(Lista<InfoSoldado*>);
    this->cartas = new(Lista<Carta*>);

    /*int i;
    InfoSoldado* soldadito = new(InfoSoldado);
    soldadito->posicion.x = 0;
    soldadito->posicion.y = 0;
    soldadito->posicion.z = 0;
    for (i = 1; i <= vidas; i++){
        soldadito->nroSoldado = i;
        soldados->add(soldadito);
    }
    delete soldadito;*/
}

Jugador::~Jugador(){
    delete soldados;
    delete cartas;
}

int Jugador::getNumeroJugador(){
    return this->numDeJugador;
}

void Jugador::agregarSoldado(Ubicacion posicionSoldado, int nroSoldado){
    InfoSoldado* nuevoSoldado = new(InfoSoldado);
    nuevoSoldado->posicion = posicionSoldado;
    nuevoSoldado->nroSoldado = nroSoldado;
    this->soldados->add(nuevoSoldado);
} 

int Jugador::reducirVidaJugador(){
    this->vidas --;
    return this->vidas;
}



/*
void Jugador::colocarSoldados(int cantidadSoldados, int cantidadJugadores){
    Ubicacion ubicacionSoldado;
    int nroSoldado;
    int nroJugador;
    
    for (int j = 0 ; j < cantidadJugadores; j++){
        nroJugador = j ;
        Jugador* jugador = new(Jugador);
        jugador->vidas = cantidadSoldados;
        jugador->numDeJugador = nroJugador;
        jugador->soldados = new(Lista<Ubicacion>);

        for (int i = 0 ; i < cantidadSoldados; i++){
            ubicacionSoldado = this->pedirUbicacion(AIRE);
            nroSoldado = i;
            jugador->soldados->add(ubicacionSoldado); //le saco el soldado
            jugador->vidas -- ; //le resto una vida
            this->colocarSoldado(ubicacionSoldado,nroJugador,nroSoldado);
        }
        this->jugadores->add(jugador);
    }
}*/ //vaya a saber uno que hace... la guardamos por las dudas.