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

Ubicacion Jugador::getPosicionSoldado(int nroSoldado){
    InfoTropa* tropa = getSoldado( nroSoldado);
    return tropa->posicion;
}


Lista<InfoTropa*>* Jugador::getListaTropas(){
    return this->tropas;
}

InfoTropa* Jugador::getSoldado(int nroSoldadoPedido){
    InfoTropa* soldadoBuscado = NULL;
    this->tropas->reiniciarCursor();
    while(this->tropas->avanzarCursor() && soldadoBuscado == NULL){
        if(this->tropas->getCursor()->nroTropa == nroSoldadoPedido  && this->tropas->getCursor()->tropa == SOLDADO){
            soldadoBuscado = this->tropas->getCursor();
        }
    }

    return soldadoBuscado;
}

InfoTropa* Jugador::getBarco(int nroBarcoPedido){
    InfoTropa* barcoBuscado = NULL;
    this->tropas->reiniciarCursor();
    while(this->tropas->avanzarCursor() && barcoBuscado == NULL){
        if(this->tropas->getCursor()->nroTropa == nroBarcoPedido && this->tropas->getCursor()->tropa == BARCO){
            barcoBuscado = this->tropas->getCursor();
        }
    }
    
    return barcoBuscado;

}

InfoTropa* Jugador::getAvion(int nroAvionPedido){
    InfoTropa* avionBuscado = NULL;
    this->tropas->reiniciarCursor();
    while(this->tropas->avanzarCursor() && avionBuscado == NULL){
        if(this->tropas->getCursor()->nroTropa == nroAvionPedido && this->tropas->getCursor()->tropa == AVION){
            avionBuscado = this->tropas->getCursor();
        }
    }
    
    return avionBuscado;
}

bool Jugador::soldadoVivo(int nroSoldado){
    InfoTropa* soldado = this->getSoldado( nroSoldado);
    return (soldado == null);
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