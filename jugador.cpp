#include "jugador.h"
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