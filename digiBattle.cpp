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

    //crear tablero

    //
    

    //crear jugadores y colocar soldados
    for (int j = 0 ; j < cantidadJugadores; j++){
        int nroJugador = j;
        Jugador* nuevo = new(Jugador);
        

        for (int i = 0 ; i < cantidadSoldados; i++){
            Ubicacion soldado = this->pedirUbicacion(SOLDADO);
            //nroSoldado = i;
            nuevo->agregarSoldado(soldado); //agrego soldado
            this->ponerSoldado(ubicacionSoldado,nroJugador,nroSoldado);
        }

        
        this->jugadores->add(nuevo);
        delete nuevo;
    }
    //
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
        
        //Le da una carta al jugador
        this->obtenerCarta(jugadorActual)
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

void DigiBattle::ponerSoldado(Ubicacion ubicacionSoldado,int nroJugador,int nroSoldado){
    Casillero* casillero;
    casillero = this->tablero->getCasillero(ubicacionSoldado);
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

void DigiBattle::ponerMina(int jugador){
    Ubicacion ubicacionMina;
    Casillero* casillero;
    Terreno tipo = AIRE;
    Artilleria tipoArtilleria = MINA;
    int sinSoldado = 0;

    ubicacionMina = pedirUbicacion(tipoArtilleria);
    
    casillero = this->tablero->getCasillero(ubicacionMina);
    
    this->resolverColision(casillero,tipoArtilleria);

}

void DigiBattle::moverTropa(int nroJugador){
    Terreno tipo = AIRE;
    int nroSoldado;
    Ubicacion ubiSoldado;
    bicacion ubiNueva;
    Casillero* casillero;
    Artilleria sinArtilleria = VACIO;
    Artilleria tipoArilleria = SOLDADO;
    
    Jugador* jugador = this->jugadores->get(nroJugador);
    
    do{
        cout<<"Ingrese numero de soldado a mover "<<endl;
        cin>>nroSoldado;
    }while ()//ver que esta vivo el soldado
    ubiSoldado = jugador->soldados->get(nroSoldado);

    do{
        ubiNueva = pedirUbicacion(tipoArilleria);
        
    }while (validarMovimiento(ubiSoldado ,ubiNueva))
    
    //Vacio la casilla vieja
    casillero = this->tablero->getCasillero(ubiSoldado);
    casillero->ponerArtilleria( sinArtilleria, numJugador);
    
    casillero = this->tablero->getCasillero(ubiNueva);
    this->resolverColision( casillero,  artilleria,  nroJugador,  nroSoldado)
}

bool DigiBattle::validarCasillero(Ubicacion posicion, Artilleria tipo){
    Casillero* casillero;

    if(!this->tablero->validarCoordenadas(posicion)){
        cout<<"Pusiste mal la coordenada pa"<< endl;
        return false;  //valido coodenadas
    }

    casillero = this->tablero->getCasillero(posicion);
    if(casillero->comprobarTerreno(tipo)){
        cout<<"Terreno seleccionado invalido"<< endl;
        return false;  //valido que no sea casillero aire
    }
    
    return true;
}

bool DigiBattle::validarMovimiento(Ubicacion ubiSoldado ,Ubicacion ubiNueva ){
    int casillaDistancia;
    if (ubiSoldado.x == ubiNueva.x ){
        if (ubiSoldado.y == ubiNueva.y + casillaDistancia || ubiSoldado.y == ubiNueva.y - casillaDistancia){
            return true
        }
    }else if (ubiSoldado.y == ubiNueva.y ){
        if (ubiSoldado.x == ubiNueva.x + casillaDistancia || ubiSoldado.x == ubiNueva.x - casillaDistancia){
            return true
        }
    }else if(ubiSoldado.x == ubiNueva.x + casillaDistancia ){
        if( ubiSoldado.y == ubiNueva.y + casillaDistancia || ubiSoldado.y == ubiNueva.y - casillaDistancia){
            return true
        } 
    }else if(ubiSoldado.x == ubiNueva.x - casillaDistancia ){
        if(ubiSoldado.y == ubiNueva.y - casillaDistancia || ubiSoldado.y == ubiNueva.y + casillaDistancia){
            return true
        }
    }
    return false
}

Ubicacion DigiBattle::pedirUbicacion(Artilleria tipo){
    Ubicacion posicion;
    cout<<"Ingrese coordenada X : "<< endl;
    cin>>posicion.x;
    cout<<"Ingrese coordenada Y : "<< endl;
    cin>>posicion.y;
    cout<<"Ingrese coordenada Z : "<< endl;
    cin>>posicion.z;
    
    while (!validarCasillero(posicion, tipo)){
        cout<< "Ingrese una coordenada valida"<< endl
        cout<<"Ingrese coordenada X : "<< endl;
        cin>>posicion.x;
        cout<<"Ingrese coordenada Y : "<< endl;
        cin>>posicion.y;
        cout<<"Ingrese coordenada Z : "<< endl;
        cin>>posicion.z;
    }
    Ubicacion* ubicacion = new(Ubicacion);
    ubicacion->x = x ;
    ubicacion->y = y ;
    ubicacion->z = z ;
    return *ubicacion;
}

void DigiBattle::obtenerCarta(Jugador * jugador){
    Carta carta = new (Carta);
    jugador->cartas->add(carta);
    delete carta;
}

void DigiBattle::usarCarta(int nroJugador, Carta* carta){

   // Jugador* jugador = this->jugadores->get(nroJugador);
    //if(jugador->cartas>)
}

void DigiBattle::resolverColision(Casillero* casillero, Artilleria artilleria, int nroJugador, int nroSoldado){
    int turnosDesactivar = 5;
    if (casillero->devolverArtilleria() == VACIO){
        casillero->ponerArtilleria(artilleria,nroJugador);
        
    }else if(casillero->devolverArtilleria() == SOLDADO){

        bajarVidaJugador(nroJugador,nroSoldado);
        int jugadorEnemigo = casillero->devolverNroJugador(); // con este numero jugador habria que sacarle soldado al jugador
        int nroSoldadoEnemigo = casillero->devolverNroSoldado();
        bajarVidaJugador(jugadorEnemigo,nroSoldadoEnemigo);
        casillero->ponerArtilleriaVacia();

    }else if (casillero->devolverArtilleria() == MINA){
        casillero->desactivarCasilla(turnosDesactivar);
        this->casillerosInactivos->add(casillero);
        bajarVidaJugador(nroJugador,nroSoldado);
        casillero->ponerArtilleriaVacia();
    }
}

void DigiBattle::resolverColision(Casillero* casillero, Artilleria artilleria, int nroJugador){
    int inactivo = 5;
    //casos solo para poner mina barco
    switch (casillero->devolverArtilleria()){
    case VACIO:
        casillero->ponerArtilleria(artilleria,nroJugador);
        break;
    case SOLDADO:
        if (artilleria == MINA){
            casillero->desactivarCasilla(inactivo);
            this->casillerosInactivos->add(casillero);
        }

        int jugadorEnemigo = casillero->devolverNroJugador(); // con este numero jugador habria que sacarle soldado al jugador
        int nroSoldadoEnemigo = casillero->devolverNroSoldado();
        bajarVidaJugador(jugadorEnemigo,nroSoldadoEnemigo);
        casillero->ponerArtilleriaVacia();
        break;

    case MINA:
        casillero->desactivarCasilla(inactivo);
        this->casillerosInactivos->add(casillero);
        casillero->ponerArtilleria(VACIO,nroJugador);
        break;
    }
}

bool DigiBattle::comprobarVictoria(int nroJugador){ 
        int perdio = 0; // nombre rancio
        Jugador* jugador = this->jugadores->get(nroJugador);
        if(jugador->vidas == perdio){  // aca comprueba que un gil se quedó sin vidas, pero solo serviria para un 1v1
            return true;
        }
        return false;
         
}

void DigiBattle::bajarVidaJugador(int nroJugador,int nroSoldado){
    Jugador* jugador = this->jugadores->get(nroJugador);
    jugador->soldados->remover(nroSoldado); //le saco el soldado
    jugador->vidas -- ; //le resto una vida
    
    jugador->soldados->reiniciarCursor;
    while(jugador->soldados->)
    
    jugador->vidas --
}




