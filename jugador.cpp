#include "jugador.h"
using namespace std;

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
    this->cartas = new(Lista<Tipos>);

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

void Jugador::nombreCarta(Tipos numDeCarta){
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
    case SOLDADOSEXTRA:
        cout<<"Soldados extras"<<endl;
        break;
    case RAYOLASER:
        cout<<"Rayo laser"<<endl;
        break;
    }
}   

void Jugador::informarCartasDisponibles(){
    Tipos carta;
    int contadorCarta = 1;
    this->cartas->reiniciarCursor();
    while(this->cartas->avanzarCursor()){
        cout<<"Carta numero "<< contadorCarta <<": ";
        carta = cartas->getCursor();
        this->nombreCarta(this->getCarta(contadorCarta));
        contadorCarta++;
    }
}  

int Jugador::removerTropa(int nroTropa, Artilleria tipoTropa){
    if (tipoTropa == SOLDADO){
        this->vidas--;
    }
    InfoTropa * tropa = this->getTropa(nroTropa, tipoTropa);
    delete(tropa);
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

int Jugador::getNumSiguienteSoldado(){
    this->numSiguienteSoldado++;
    return this->numSiguienteSoldado;
}

int Jugador::getNumSiguienteBarco(){
    this->numSiguienteBarco++;
    return this->numSiguienteBarco;
}

int Jugador::getNumSiguienteAvion(){
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

void Jugador::setPosicionTropa(int nroTropaPedida, Artilleria tipoArtilleria, Ubicacion ubicacion){
    InfoTropa* tropaActual = this->getTropa(nroTropaPedida, tipoArtilleria);
    tropaActual->posicion = ubicacion;
}


Lista<InfoTropa*>* Jugador::getListaTropas(){
    return this->tropas;
}

Lista<casilleroUbi>* Jugador::getListaCasillerosVisibles(){
    return this->casillerosVisibles;
}

bool Jugador::tropaViva(int nroTropa, Artilleria tipoArtilleria){
    InfoTropa* tropa = this->getTropa(nroTropa, tipoArtilleria);
    return (tropa ==  NULL);
}

Lista<Tipos>* Jugador::getListaCartas(){
    return this->cartas;
}

void Jugador::addCarta(){
    srand(time(NULL));
    this->cartas->add((static_cast<Tipos> (rand() % 6)));
}

Tipos Jugador::getCarta(int nroCarta){
    this->cartas->reiniciarCursor();
    return this->cartas->get(nroCarta);
}
