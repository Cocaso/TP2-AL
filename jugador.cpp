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

void Jugador::agregarTropa(Ubicacion posicionTropa, int nroTropa, Artilleria tipoTropa){
    InfoTropa* nuevaTropa = new(InfoTropa);
    nuevaTropa->tropa = tipoTropa;
    nuevaTropa->posicion = posicionTropa;
    nuevaTropa->nroTropa = nroTropa;
    this->tropas->add(nuevaTropa);
    if (tipoTropa == SOLDADO){
        this->vidas++;
    }
}

void Jugador::nombreCarta( tipos numDeCarta){
    switch(numDeCarta){
    case ATAQUEQUIMICO:
        cout<<"ATAQUE QUIMICO"<<endl;
        break;
    case AVIONRADAR:
        cout<<"AVION RADAR"<<endl;
        break;
    case INVOCARBARCO:
        cout<<"INVOCAR BARCO"<<endl;
        break;
    case POTOFGREED:
        cout<<"Pot of greed"<<endl;
        break;
    case SOLDADOEXTRA:
        cout<<"Soldados extras"<<endl;
        break;
    case RAYOLASER:
        cout<<"Rayo laser"<<endl;
        break;
    }
}   

void Jugador::nombrarCartas(){
    tipos* carta;
    int contadorCarta = 1;
    this->cartas->reiniciarCursor();
    while(avanzarCursor()){
        cout<<"Numero de carta "<< contadorCarta <<" : ";
        carta = getCursor();
        carta->nombreCarta();
        contadorCarta++;
    }
}  

int Jugador::removerTropa(int nroTropa, Artilleria tipoTropa){
    if (tipoTropa == SOLDADO){
        this->vidas --;
    }
    // Falta hacer delete de la tropa ya que al agregar usamos new sino vamos a tener memoria colgada
    //sacamos de la lista el numero de soldado
    this->tropas->remover(getPosicionTropaEnLista(nroTropa, tipoTropa));
    return this->vidas;
}

int Jugador::getNumeroJugador(){
    return this->numDeJugador;
}

int Jugador::getPosicionTropaEnLista(int nroTropaBuscada, Artilleria tipoTropa){
    int posicionTropa = 1;
    this->tropas->reiniciarCursor();
    while(this->tropas->avanzarCursor()){
        if(this->tropas->getCursor()->nroTropa == nroTropaBuscada  && this->tropas->getCursor()->tropa == tipoTropa){
            return posicionTropa;
        }
        posicionTropa ++;
    }
}

int getNumSiguienteSoldado(){
    this->numSiguienteSoldado++;
    return this->numSiguienteSoldado;
}

int getNumSiguienteBarco(){
    this->numSiguienteBarco++;
    return this->numSiguienteBarco;
}

int getNumSiguienteAvion(){
    this->numSiguienteAvion++;
    return this->numSiguienteAvion;
}  

int Jugador::cantidadCartas(){
    return this->cartas->contarElementos();
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

Lista<tipos*>* Jugador::getListaCartas(){
    return this->cartas;
}

void Jugador::addCarta(){
    srand(time(NULL));
    this->cartas->add((rand() % 6));
}

tipos Jugador::getCarta(int nroCarta){
    this->cartas->reiniciarCursor();
    return this->cartas->get(nroCarta);
}
