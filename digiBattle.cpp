#include "digiBattle.h"
using namespace std;

DigiBattle::DigiBattle(){
    this->tableroArchivo = fopen("tablero4k.bmp", "w");
    this->tablero = new(Tablero);
    this->jugadores = new(Lista<Jugador*>) ;
    this->casillerosInactivos = new(Lista<Casillero*>);
}

DigiBattle::~DigiBattle(){

}

void DigiBattle::iniciarJuego(){

    Jugador* jugador;
    int cantidadJugadores;
    int cantidadSoldados;
    int i, x, y, z;

    cout << "Ingrese el tamaño del mapa (min 10x10x3): ";
    cin >> x;
    cin >> y;       //Con imput formato "10x10x10" es posible que funcione
    cin >> z;       //si no funciona arreglar jeje sorry

    cout << "Ingrese cantidad de jugadores: " << endl;
    cin >> cantidadJugadores;

    cout<<"Ingrese la cantidad de soldados por jugador: "<< endl;
    cin>>cantidadSoldados;

    for(i = 1 ; i <= cantidadJugadores ; i++){
        this->colocarSoldados(cantidadSoldados, i);
        jugador = new(Jugador);
        (*jugador).vidas = cantidadSoldados;
        (*jugador).numDeJugador = i;
        (*jugador).soldados = new(Lista<Ubicacion>);
        (*jugador).cartas = new(Lista<Carta*>);
        this->jugadores->add(jugador);
        delete jugador;
    }
    
    
}

void DigiBattle::colocarSoldados(int cantidadSoldados, int cantidadJugadores){
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

}

void DigiBattle::colocarSoldado(Ubicacion ubicacionSoldado,int nroJugador,int nroSoldado){
    Casillero* casillero;
    casillero = this->tablero->getCasillero(ubicacionSoldado.x,ubicacionSoldado.y,ubicacionSoldado.z);
    int inactivo = 5;

    switch (casillero->devolverArtilleria()){
    case VACIO:
        casillero->ponerArtilleria(SOLDADO,nroJugador);
        break;
    case SOLDADO:
        int nroJugadorEnemigo = casillero->devolverNroJugador(); 
        int nroSoldadoEnemigo = casillero->devolverNroSoldado();
        this->bajarVidaJugador(nroJugadorEnemigo,nroSoldadoEnemigo);
        this->bajarVidaJugador(nroJugador,nroSoldado);
        casillero->desactivarCasilla(inactivo);
        casillero->ponerArtilleria(VACIO,nroJugador);
        break;
    }
}

void DigiBattle::turno(){
    int turno = 1;
    Jugador* jugadorActual = new(Jugador);
    Carta* carta;

    jugadores->reiniciarCursor();
    while(!comprobarVictoria()){
        //Determina a quien le toca jugar
        if(turno > jugadores->contarElementos()){
            jugadores->reiniciarCursor();
        }
        jugadores->avanzarCursor();
        jugadorActual = jugadores->getCursor();
        //
        
        //Le da una carta
        carta = new (Carta);
        jugadorActual->cartas->add(carta);
        delete carta;
        //

        //Elige si usa una carta o no y cuál
        //usarCarta();
        //

        //Poner mina (y disparar con el barco??)
        ponerMina(jugadorActual->numDeJugador);
        //

        //Permite mover las tropas
        moverTropa();
        //

        turno++;
    }

    //Lo que pasa cuando termina el juego yo que se
    
}

void DigiBattle::moverTropa(){

}

void DigiBattle::ponerMina(int jugador){
    Ubicacion ubicacionMina;
    Casillero* casillero;
    Terreno tipo = AIRE;

    ubicacionMina = pedirUbicacion(AIRE);
    
    casillero = this->tablero->getCasillero(ubicacionMina.x,ubicacionMina.y,ubicacionMina.z);
    this->comprobarColision(jugador,casillero);
}

Ubicacion DigiBattle::pedirUbicacion(Terreno tipo){
    int x;
    int y;
    int z;
    do{
        cout<<"Ingrese coordenada X : "<< endl;
        cin>>x;
        cout<<"Ingrese coordenada Y : "<< endl;
        cin>>y;
        cout<<"Ingrese coordenada Z : "<< endl;
        cin>>z;
    }while(!validarCasillero( x,  y, z,tipo));
    Ubicacion* ubicacion = new(Ubicacion);
    ubicacion->x = x ;
    ubicacion->y = y ;
    ubicacion->z = z ;
    return *ubicacion;
}

bool DigiBattle::validarCasillero(int x, int y, int z ,Terreno tipo){
    Casillero* casillero;

    if(!this->tablero->validarCoordenadas(x,y,z)){
        return false;  //valido coodenadas
    }

    casillero = this->tablero->getCasillero(x,y,z);
    if(casillero->comprobarTerreno(tipo)){
        return false;  //valido que no sea casillero aire
    }
    
    return true;
}

void DigiBattle::obtenerCarta(){

}

void DigiBattle::usarCarta(){

}

void DigiBattle::comprobarColision(int jugador, Casillero* casillero){
    int nroJugador;
    int nroSoldado;
    int Inactivo = 5;
    switch (casillero->devolverArtilleria()){
    case VACIO:
        casillero->ponerArtilleria(MINA,jugador);
        break;
    case SOLDADO:
        nroJugador = casillero->devolverNroJugador(); // con este numero jugador habria que sacarle soldado al jugador
        nroSoldado = casillero->devolverNroSoldado();
        bajarVidaJugador(nroJugador,nroSoldado);
        casillero->desactivarCasilla(Inactivo);
        casillero->ponerArtilleria(VACIO,jugador);
        break;
    default: //caso barco, mina
        casillero->desactivarCasilla(Inactivo);
        this->casillerosInactivos->add(casillero);
        casillero->ponerArtilleria(VACIO,jugador);
        
        break;
    }
}

bool DigiBattle::comprobarVictoria(){

}

void DigiBattle::bajarVidaJugador(int nroJugador,int nroSoldado){
    Jugador* jugador = this->jugadores->get(nroJugador);
    jugador->soldados->remover(nroSoldado); //le saco el soldado
    jugador->vidas -- ; //le resto una vida
}



