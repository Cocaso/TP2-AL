#include "jugador.h"
using namespace std;

Jugador::Jugador(){
    this->vidas = 0;
    this->numDeJugador = 0;
    this->tropas = NULL;
    this->cartas = NULL;
    this->numSiguienteBarco = 0;
    this->numSiguienteAvion = 0;
}

Jugador::Jugador(int nroJugador){
    this->vidas = 0;
    this->numSiguienteSoldado = 1;
    this->numSiguienteBarco = 1;
    this->numSiguienteAvion = 1;
    this->numDeJugador = nroJugador;
    this->tropas = new(Lista<Tropa*>);
    this->cartas = new(Lista<Tipos>);
}

Jugador::~Jugador(){
    delete this->tropas;
    delete this->cartas;
}

void Jugador::agregarTropa(Ubicacion posicionTropa, int nroTropa, Artilleria tipoTropa){
    Tropa* nuevaTropa = new Tropa(posicionTropa, nroTropa, tipoTropa);
    this->tropas->add(nuevaTropa);
    if (tipoTropa == SOLDADO){
        this->vidas++;
        this->numSiguienteSoldado++;
    }else if(tipoTropa == AVION){
        this->numSiguienteAvion++;
    }else if(tipoTropa == BARCO){
        this->numSiguienteBarco++;
    }
}

void Jugador::setPosicionTropa(int nroTropaPedida, Artilleria tipoArtilleria, Ubicacion ubicacion){
    Tropa* tropaActual = this->getTropa(nroTropaPedida, tipoArtilleria);
    tropaActual->setUbicacion(ubicacion);
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
    Tipos tipoCarta;
    int contadorCarta = 1;
    this->cartas->reiniciarCursor();
    while(this->cartas->avanzarCursor()){
        tipoCarta = cartas->getCursor();
        cout << contadorCarta << " - ";
        this->nombreCarta(tipoCarta);
        contadorCarta ++;
    }
    cout << endl;
}  

bool Jugador::bajarVidaBarco(int nroTropa){
    Tropa* tropa = this->getTropa(nroTropa, BARCO);
    if (tropa->getVidasBarco() == 1){
        tropa->bajarVidasBarco();
        return false;
    } else {
        tropa->bajarVidasBarco();
        return true;
    }
}

void Jugador::addCarta(){
    srand(time(NULL));
    this->cartas->add((static_cast<Tipos> (rand() % 6)));
}

int Jugador::removerTropa(int nroTropa, Artilleria tipoTropa){
    if (tipoTropa == SOLDADO){
        this->vidas--;
    }
    Tropa* tropa = this->getTropa(nroTropa, tipoTropa);
    this->tropas->remover(getPosicionTropaEnLista(nroTropa, tipoTropa));
    delete tropa;
    return this->vidas;
}

int Jugador::getNumeroJugador(){
    return this->numDeJugador;
}

int Jugador::getVidas(){
    return this->vidas;
}

int Jugador::cantidadTropas(Artilleria tipoTropa){
    this->tropas->reiniciarCursor();
    int cantidadTropa = 0;

    while(this->tropas->avanzarCursor()){
        if(this->tropas->getCursor()->getTipoTropa() == tipoTropa){
            cantidadTropa ++;
        }
    }
    return cantidadTropa;
}

int Jugador::getPosicionTropaEnLista(int nroTropaBuscada, Artilleria tipoTropa){
    int posicionTropa = 1;
    this->tropas->reiniciarCursor();
    while(this->tropas->avanzarCursor()){
        if(this->tropas->getCursor()->getNroTropa() == nroTropaBuscada  && this->tropas->getCursor()->getTipoTropa() == tipoTropa){
            return posicionTropa;
        }
        posicionTropa ++;
    }
}

int Jugador::getNumSiguienteSoldado(){
    return this->numSiguienteSoldado;
}

int Jugador::getNumSiguienteBarco(){
    return this->numSiguienteBarco;
}

int Jugador::getNumSiguienteAvion(){
    return this->numSiguienteAvion;
}  

int Jugador::cantidadCartas(){
    return this->cartas->contarElementos();
}

bool Jugador::tropaViva(int nroTropa, Artilleria tipoArtilleria){
    Tropa* tropa = this->getTropa(nroTropa, tipoArtilleria);
    return (tropa ==  NULL);
}

Ubicacion Jugador::getUbicacionTropa(int nroTropa, Artilleria tipoArtilleria){
    Tropa* tropa = getTropa(nroTropa, tipoArtilleria);
    return tropa->getUbicacion();
}

Tipos Jugador::getCarta(int numeroCarta){
    Tipos carta;
    carta = this->cartas->get(numeroCarta);
    this->cartas->remover(numeroCarta);
    return carta;
    //Falta validar
}

Tropa* Jugador::getTropa(int nroTropaPedida, Artilleria tipoArtilleria){
    Tropa* tropaBuscada = NULL;
    this->tropas->reiniciarCursor();
    while(tropaBuscada == NULL && this->tropas->avanzarCursor()){
        if(this->tropas->getCursor()->getNroTropa() == nroTropaPedida  && this->tropas->getCursor()->getTipoTropa() == tipoArtilleria){
            tropaBuscada = this->tropas->getCursor();
        }
    }
    return tropaBuscada;
}

Lista<Tropa*>* Jugador::getListaTropas(){
    return this->tropas;
}

Lista<Tipos>* Jugador::getListaCartas(){
    return this->cartas;
}
