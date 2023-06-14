#include "jugador.h"

Jugador::Jugador(){
    this->vidas = 0;
    this->numDeJugador = 0;
    this->tropas = NULL;
    this->cartas = NULL;
}

Jugador::Jugador(int nroJugador, int vidas){
    this->vidas = vidas;
    this->numDeJugador = nroJugador;
    this->tropas = new(Lista<InfoTropa*>);
    this->cartas = new(Lista<Carta*>);

    /*int i;
    InfoSoldado* soldadito = new(InfoSoldado);
    soldadito->posicion.x = 0;
    soldadito->posicion.y = 0;
    soldadito->posicion.z = 0;
    for (i = 1; i <= vidas; i++){
        soldadito->nroSoldado = i;
        tropas->add(soldadito);
    }
    delete soldadito;*/
}

Jugador::~Jugador(){
    delete tropas;
    delete cartas;
}

void Jugador::agregarSoldado(Ubicacion posicionSoldado, int nroSoldado){
    InfoTropa* nuevoSoldado = new(InfoTropa);
    nuevoSoldado->posicion = posicionSoldado;
    nuevoSoldado->nroTropa = nroSoldado;
    this->tropas->add(nuevoSoldado);
}

int Jugador::removerSoldado(int nroSoldado){
    this->vidas --;
    //sacamos de la lista el numero de soldado
    this->tropas->remover(getPosicionSoldadoEnLista(nroSoldado));
    return this->vidas;
}

int Jugador::getNumeroJugador(){
    return this->numDeJugador;
}

int Jugador::getPosicionSoldadoEnLista(int nroSoldado){
    int posicionSoldado = 1;
    this->tropas->reiniciarCursor();
    while(this->tropas->avanzarCursor()){
        if(this->tropas->getCursor()->nroTropa == nroSoldado  && this->tropas->getCursor()->tropa == SOLDADO){
            return posicionSoldado;
        }
        posicionSoldado ++;
    }
}

Ubicacion Jugador::getPosicionTropa(int nroTropa, Artilleria tipoArtilleria){
    InfoTropa* tropa = getTropa(nroTropa, tipoArtilleria);
    return tropa->posicion;
}

InfoTropa* Jugador::getTropa(int nroTropaPedida, Artilleria tipoArtilleria){
    InfoTropa* tropaBuscada = NULL;
    this->tropas->reiniciarCursor();
    while(this->tropas->avanzarCursor() && tropaBuscada == NULL){
        if(this->tropas->getCursor()->nroTropa == nroTropaPedida  && this->tropas->getCursor()->tropa == tipoArtilleria){
            tropaBuscada = this->tropas->getCursor();
        }
    }
    return tropaBuscada;
}

Lista<InfoTropa*>* Jugador::getListaTropas(){
    return this->tropas;
}

bool Jugador::tropaViva(int nroTropa, Artilleria tipoArtilleria){
    InfoTropa* tropa = this->getTropa(nroTropa, tipoArtilleria);
    return (tropa == null);
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
        jugador->tropas = new(Lista<Ubicacion>);

        for (int i = 0 ; i < cantidadSoldados; i++){
            ubicacionSoldado = this->pedirUbicacion(AIRE);
            nroSoldado = i;
            jugador->tropas->add(ubicacionSoldado); //le saco el soldado
            jugador->vidas -- ; //le resto una vida
            this->colocarSoldado(ubicacionSoldado,nroJugador,nroSoldado);
        }
        this->jugadores->add(jugador);
    }
}*/ //vaya a saber uno que hace... la guardamos por las dudas.