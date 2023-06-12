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

    Ubicacion tableroSize;
    Ubicacion posicionSoldado;
    int cantidadJugadores;
    int cantidadSoldados;
    int nroSoldado;
    int i, j;


    cout << "Ingrese el tamaño del mapa (min 10x10x3): ";
    cin >> tableroSize.x;
    cin >> tableroSize.y;       //Revisar esto que esta mal
    cin >> tableroSize.z;       //Hay que aclarar la disposicion de las coordenadas al usuario

    cout << "Ingrese cantidad de jugadores: " << endl;
    cin >> cantidadJugadores;

    cout<<"Ingrese la cantidad de soldados por jugador: "<< endl;
    cin>>cantidadSoldados;

    //crear tablero (con el constructor2)
    this->tablero(tableroSize);
    //
    

    //crear jugadores y colocar soldados
    int nroJugador;
    for (j = 0 ; j < cantidadJugadores; j++){

        //Crea el jugador
        nroJugador = j;
        Jugador* nuevoJugador = new(Jugador(nroJugador, cantidadSoldados));
        
        //Lo deja poner sus soldados
        for (int i = 1 ; i <= cantidadSoldados; i++){
            posicionSoldado = this->pedirUbicacion(SOLDADO);
            nroSoldado = i;
            nuevoJugador->agregarSoldado(posicionSoldado, nroSoldado); //agrego soldado
            this->ponerSoldado(posicionSoldado,nroJugador,nroSoldado);
        }
        
        this->jugadores->add(nuevoJugador);
        delete nuevoJugador;
    }
    //
}

void DigiBattle::turno(){
    int turno = 1;
    Jugador* jugadorActual;
    Carta* carta;

    jugadores->reiniciarCursor();
    while(!comprobarVictoria()){
        //Determina a quien le toca jugar
        if(turno > jugadores->contarElementos()){
            jugadores->reiniciarCursor();
            turno = 1;
        }
        this->jugadores->avanzarCursor();
        jugadorActual = this->jugadores->getCursor();
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

        //Reducir cuenta de los casilleros inactivos
        //

        turno++;
    }

    //Lo que pasa cuando termina el juego yo que se
    
}

void DigiBattle::ponerSoldado(Ubicacion ubicacionSoldado, int nroJugador, int nroSoldado){
    Casillero* casillero;
    casillero = this->tablero->getCasillero(ubicacionSoldado);
    int inactivo = 5;

    switch (casillero->devolverArtilleria()){
    case VACIO:
        casillero->ponerArtilleria(SOLDADO, nroJugador);
        break;
    case SOLDADO:
        int nroJugadorEnemigo = casillero->devolverNroJugador();
        int nroSoldadoEnemigo = casillero->devolverNroSoldado();
        this->bajarVidaJugador(nroJugadorEnemigo, nroSoldadoEnemigo);
        this->bajarVidaJugador(nroJugador, nroSoldado);
        casillero->desactivarCasilla(inactivo);
        casillero->ponerArtilleria(VACIO, nroJugador);
        break;
    }
}

void DigiBattle::ponerMina(int jugador){
    Ubicacion ubicacionMina;
    Casillero* casillero;
    Artilleria tipoArtilleria = MINA;

    ubicacionMina = pedirUbicacion(tipoArtilleria);
    
    casillero = this->tablero->getCasillero(ubicacionMina);
    
    this->resolverColision(casillero,tipoArtilleria);

    // falta ver donde implementamos el poder de la mina

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
        
    }while (validarMovimiento(ubiSoldado, ubiNueva))
    
    //Vacio la casilla vieja
    casillero = this->tablero->getCasillero(ubiSoldado);
    casillero->ponerArtilleria(sinArtilleria, numJugador);
    
    casillero = this->tablero->getCasillero(ubiNueva);
    this->resolverColision(casillero,  artilleria,  nroJugador,  nroSoldado)
}

bool DigiBattle::validarCasillero(Ubicacion posicion, Artilleria tipo){
    Casillero* casillero;

    //si las coordenadas existen sigue, sino false
    if(!this->tablero->validarCoordenadas(posicion)){
        cout<<"Coodenadas ingresadas fuera rango"<< endl;
        return false;
    }

    casillero = this->tablero->getCasillero(posicion);

    //si el terreno es compatible con la artillería sigue, sino false
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

    //si las coordenadas no son válidas, vuelve a pedir
    do{
        //solo pide Z (altura) si la artillería es un avión
        if (tipo != AVION) {
            posicion.z = 0;
            cout<<"Ingrese coordenada X : "<< endl;
            cin>>posicion.x;
            cout<<"Ingrese coordenada Y : "<< endl;
            cin>>posicion.y;
        
        } else {
            cout<<"Ingrese coordenada X : "<< endl;
            cin>>posicion.x;
            cout<<"Ingrese coordenada Y : "<< endl;
            cin>>posicion.y;
            cout<<"Ingrese coordenada Z : "<< endl;
            cin>>posicion.z;
        } 
    }while (!validarCasillero(posicion, tipo));

    return posicion;
}

void DigiBattle::obtenerCarta(Jugador * jugador){
    Carta carta = new (Carta);
    jugador->cartas->add(carta);
    delete carta;
}

Jugador* DigiBattle::buscarJugador(int nroJugador){
    Jugador* jugadorBuscado = NULL;
    
    //Guardamos el numero de jugador anterior
    int jugadorAntiguo = this->jugadores->getCursor()->getNumeroJugador();
    int posicionAntiguaEncontrada = false;
    
    //Reiniciamos el cursor y buscamos al jugador objetivo
    this->jugadores->reiniciarCursor();
    while(this->jugadores->avanzarCursor() && jugadorBuscado == NULL){
        if (jugadores->getCursor()->getNumeroJugador() == nroJugador){
            jugadorBuscado = jugadores->getCursor();
        }
    }
    
    //Devuelve el cursor a su posicion previa
    jugadores->reiniciarCursor();
    while(this->jugadores->avanzarCursor() && posicionAntiguaEncontrada == false){
        if (jugadores->getCursor()->getNumeroJugador() == jugadorAntiguo){
            posicionAntiguaEncontrada = true;
        }
    }

    return jugadorBuscado;
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
    //condicion de corte,,,,,,,,,,, si no hayy mas jugadores, ganó el que quedó
    Jugador* ganador = this->jugadores->get(nroJugador);
    
    return (this->jugadores->contarElementos() == 1);
    
}

void DigiBattle::bajarVidaJugador(int nroJugador,int nroSoldado){
    Jugador* jugador = this->buscarJugador(nroJugador);
    jugador->soldados->remover(nroSoldado); //le saco el soldado
    
    jugador->soldados->reiniciarCursor;
    while(jugador->soldados->)
    
    //comprueba si efectivamente el jugador perdio todos sus soldados/vidas
    if (jugador->reducirVidaJugador == 0){
        this->jugadores->remover(nroJugador);
    }
}




