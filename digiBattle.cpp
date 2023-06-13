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


    cout << "Ingrese el tamaño del mapa (min 10x10x3): ";
    cin >> tableroSize.x;
    cin >> tableroSize.y;       //Revisar esto que esta mal
    cin >> tableroSize.z;       //Hay que aclarar la disposicion de las coordenadas al usuario

    cout << "Ingrese cantidad de jugadores: " << endl;
    cin >> cantidadJugadores;

    cout<<"Ingrese la cantidad de tropas por jugador: "<< endl;
    cin>>cantidadSoldados;

    //crear tablero (con el constructor2)
    this->tablero->Tablero(tableroSize);
    

    //crear jugadores y colocar tropas
    int nroJugador;
    for (int j = 0 ; j < cantidadJugadores; j++){

        //Crea el jugador
        nroJugador = j;
        Jugador* nuevoJugador = new(Jugador(nroJugador, cantidadSoldados));
        
        //Lo deja poner sus tropas
        for (int i = 1 ; i <= cantidadSoldados; i++){
            posicionSoldado = this->pedirUbicacion(SOLDADO);
            nroSoldado = i;
            nuevoJugador->agregarSoldado(posicionSoldado, nroSoldado);  //agrego soldado
            this->ponerSoldado(posicionSoldado,nroJugador,nroSoldado);  //pone el soldado en el tablero
        }
        
        this->jugadores->add(nuevoJugador);
        delete nuevoJugador;
    }
    //
}

void DigiBattle::turno(){
    Jugador* jugadorActual;
    Carta* carta;
    string opcion;
    
    jugadores->reiniciarCursor();
    while(!comprobarVictoria()){
        //Determina a quien le toca jugar
        if( !jugadores->avanzarCursor()){
            jugadores->reiniciarCursor();   
        }
        jugadorActual = this->jugadores->getCursor();
        //
        
        //Le da una carta al jugador
        this->obtenerCarta(jugadorActual);
        //

        //Poner mina (y disparar con el barco??)
        ponerMina(jugadorActual->numDeJugador);
        //

        //Vemos si quiere mover alguna tropa
        do {
           cou<<"Quiere realizar un movimiento de alguna tropa ? S/N "<<endl;
           cin>>opcion;
        }while(opcion != "S" || opcion != "N")
        
        if (opcion == "S"){
            moverTropa();
        }

        //Elige si usa una carta o no y cuál
        do {
           cou<<"Quiere invocar alguna de sus cartas ? S/N "<<endl;
           cin>>opcion;
        }while(opcion != "S" || opcion != "N")
        
        if (opcion == "S"){
            //usarCarta();
        }

        //Reducir cuenta de los casilleros inactivos
        reducirCasilleroInactivo();
        //

    }
    //Lo que pasa cuando termina el juego yo que se
    anunciarGanador();
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
    
    this->resolverColision(casillero,tipoArtilleria,jugador);

    // falta ver donde implementamos el poder de la mina

}

void DigiBattle::moverTropa(){
    Ubicacion ubiTropa;
    Ubicacion ubiNueva;
    Casillero* casillero;
    Artilleria sinArtilleria = VACIO;
    
    Jugador* jugador = this->jugadores->getCursor();
    int nroTropaElegida;
 
    Lista<InfoTropa*>* tropasDelJugador;
    int tipoTropa;
    Artilleria seleccionTropa = 0;
    Ubicacion posicion;

    int nroJugador = jugador->getNumeroJugador();
    
    //Pregunta qué tipo de tropa se quiere mover
    cout << "Elige qué tipo de tropa mover: " << endl;

        //Se fija cuales están disponibles
        tropasDelJugador = this->jugadores->getCursor()->getListaTropas();
        int soldados = 0;
        int barcos = 0;
        int aviones = 0;
        tropasDelJugador->reiniciarCursor();
        while(tropasDelJugador->avanzarCursor()){
            if (tropasDelJugador->getCursor()->tropa == SOLDADO){
                soldados++;
            } else if (tropasDelJugador->getCursor()->tropa == BARCO){
                barcos++;
            } else if (tropasDelJugador->getCursor()->tropa == AVION){
                aviones++;
            }
        }
    
    cout << "1 - Soldados Disponibles: " << soldados << endl;
    cout << "2 - Aviones Disponibles: " << aviones << endl;
    cout << "3 - Barcos Disponibles: " << barcos << endl << endl;
    do{
        cout << "Elige con sabiduria: ";
        cin >> tipoTropa;
        seleccionTropa = static_cast<Artilleria>(tipoTropa);
    }while(comprobarSeleccionTropa(seleccionTropa, aviones, barcos));
    //

    //Mostrar las tropas disponibles a usar y elegir la tropa a mover
    mostrarTropasDisponibles(seleccionTropa, tropasDelJugador);
    do{
    cout << "Elija el N° de tropa a mover" << endl;
    cin >> nroTropaElegida;
    } while(jugador->tropaViva(nroTropaElegida, seleccionTropa));
    ubiTropa = jugador->getPosicionTropa(nroTropaElegida, seleccionTropa);
    //

    //Pedir ubicacion y validar el movimiento de la tropa
    ubiNueva = this->pedirUbicacion(seleccionTropa);

    while (validarMovimiento(ubiTropa, ubiNueva) && seleccionTropa != AVION) {
        
    }
    //

    //Falta revisar esto de aca
    //Vacio la casilla vieja
    casillero = this->tablero->getCasillero(ubiTropa);
    casillero->ponerArtilleria(sinArtilleria, 0);

    casillero = this->tablero->getCasillero(ubiNueva);
    this->resolverColision(casillero,  seleccionTropa,  nroJugador,  nroTropaElegida);
    //

    /*antiguo
    int nroSoldado;
    Ubicacion* ubiSoldado;
    Ubicacion ubiNueva;
    Casillero* casillero;
    Artilleria sinArtilleria = VACIO;
    Artilleria tipoArilleria = SOLDADO;
    Jugador* jugador = this->buscarJugador(nroJugador);


    do{
        cout << "Ingrese numero de tropa a mover "<<endl;
        cin >> nroTropa;
        ubiSoldado = jugador->getPosicionSoldado(nroTropa,);
    } while (!tropaViva(nroTropa, SOLDADO)); //ver que esta vivo el soldado
    
    
    do {
        ubiNueva = pedirUbicacion(tipoArilleria);
        
    } while (validarMovimiento(ubiSoldado, ubiNueva)){
    
    //Vacio la casilla vieja
    casillero = this->tablero->getCasillero(ubiSoldado);
    casillero->ponerArtilleria(sinArtilleria, nroJugador);
    
    casillero = this->tablero->getCasillero(ubiNueva);
    this->resolverColision(casillero,  artilleria,  nroJugador,  nroTropa);
    */
}

void DigiBattle::mostrarTropasDisponibles(Artilleria seleccionTropa, Lista<InfoTropa*>* tropasDelJugador){
    Ubicacion posicion;
    
    cout << "TROPAS DISPONIBLES" << endl;
    
    tropasDelJugador->reiniciarCursor();
    while(tropasDelJugador->avanzarCursor()){
        if(tropasDelJugador->getCursor()->tropa == seleccionTropa){
            posicion = tropasDelJugador->getCursor()->posicion;

            cout << "Tropa N°: " << tropasDelJugador->getCursor()->nroTropa;
            cout << " // Posicion X: " << posicion.x;
            cout << " Y: " << posicion.y << endl;
            //Soldado No 1 // Posicion X:7 Y:4
        }
    }
    /*  VERSION LARGA
    if(seleccionTropa == 1){
        cout << "SOLDADOS DISPONIBLES" << endl;
        tropasDelJugador->reiniciarCursor();
        for(i = 0; i > soldados; i++){
            tropasDelJugador->avanzarCursor();
            Ubicacion posicion = tropasDelJugador->getCursor()->posicion;
            cout << "Soldado N°: " << tropasDelJugador->getCursor()->nroTropa;
            cout <<"// Posicion X: " << posicion.x;
            cout <<" Y: " << posicion.y << endl;
            //Soldado No 1 // Posicion X:7 Y:4
        }
    } else if (seleccionTropa == 2){
        cout << "AVIONES DISPONIBLES" << endl;
        tropasDelJugador->reiniciarCursor();
        while(tropasDelJugador->avanzarCursor()){
            if(tropasDelJugador->getCursor()->tropa == AVION){
                Ubicacion posicion = tropasDelJugador->getCursor()->posicion;
                cout << "Avion N°: " << tropasDelJugador->getCursor()->nroTropa;
                cout <<"// Posicion X: " << posicion.x;
                cout <<" Y: " << posicion.y;
            }
        }
    } else if (seleccionTropa == 3){
        cout << "BARCOS DISPONIBLES" << endl;
        tropasDelJugador->reiniciarCursor();
        while(tropasDelJugador->avanzarCursor()){
            if(tropasDelJugador->getCursor()->tropa == BARCO){
                Ubicacion posicion = tropasDelJugador->getCursor()->posicion;
                cout << "Barco N°: " << tropasDelJugador->getCursor()->nroTropa;
                cout <<"// Posicion X: " << posicion.x;
                cout <<" Y: " << posicion.y;
            }
        }
    }
    */


}

bool DigiBattle::comprobarSeleccionTropa(Artilleria seleccionTropa, int cantidadAviones, int cantidadBarcos){
    const int SINTROPAS = 0;
    if ((seleccionTropa == AVION && cantidadAviones == SINTROPAS) || 
        (seleccionTropa == BARCO && cantidadBarcos == SINTROPAS) || 
        (seleccionTropa > 3) || (seleccionTropa < 1)){
        return false;
    }
    return true;

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
    
        //vemos si el casillero no esta inactivo
    if(casillero->comprobarEstado()){
        cout<<"casillero seleccionado momentaneamente inactivo"<< endl;
        return false;  //valido que no sea casillero aire
    }

    return true;
}

bool DigiBattle::validarMovimiento(Ubicacion ubiSoldado, Ubicacion ubiNueva){
    int distanciaX = abs(ubiSoldado.x - ubiNueva.x);
    int distanciaY = abs(ubiSoldado.y - ubiNueva.y);
    // Valida que la distancia a mover sea inferior a 3, y que solo se pueda mover en diagonal u horizontal :)
    if((distanciaX > 3 || distanciaY > 3) ||
        (distanciaX != distanciaY && distanciaX != 0 && distanciaY != 0)){
        return false;
    }
    return true;
    /*
    if(distanciaX > distanciaY){
        distancia = distanciaX
    } else{
        distancia = distanciaY
    }
    
    while (i < distancia){
        if(ubiSoldado.x - ubiNueva.x > 0 && ubiSoldado.y - ubiNueva.y > 0)

        i++;
    }

    if (this->tablero->getCasillero(ubiSoldado)->comprobarTerreno(SOLDADO) && this->tablero->getCasillero(ubiSoldado)->devolverArtilleria() == SOLDADO){
        casillaDistancia = 1;
    }else{
        casillaDistancia = 3;
    }
    */
    /*
    horizontal
    if (ubiSoldado.x <= ubiNueva.x + 3 || ubiSoldado.x <= ubiNueva.x - 3){
        if (ubiSoldado.y == ubiNueva.y){
            return true
        }
        vertical
    if (ubiSoldado.y <= ubiNueva.y + 3 || ubiSoldado.y <= ubiNueva.y - 3){
        if (ubiSoldado.x == ubiNueva.x ){
            return true
        }

    diagonal
    if (ubiSoldado.x <= ubiNueva.x + 3 && ubiSoldado.y <= ubiNueva.y + 3)return true
    if (ubiSoldado.x <= ubiNueva.x -3 && ubiSoldado.y <= ubiNueva.x - 3)return true
    if (ubiSoldado.x <= ubiNueva.x -3 && ubiSoldado.y <= ubiNueva.x + 3)return true
    if (ubiSoldado.x <= ubiNueva.x +3 && ubiSoldado.y <= ubiNueva.x - 3)return true
    return false
    */
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
    } while (!validarCasillero(posicion, tipo));

    return posicion;
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

Jugador* DigiBattle::buscarJugador(int nroJugador){
    Jugador* jugadorBuscado = NULL;
    
    //Guardamos el numero de jugador anterior
    int jugadorAntiguo = this->jugadores->getCursor()->getNumeroJugador();
    bool posicionAntiguaEncontrada = false;
    
    //Reiniciamos el cursor y buscamos al jugador objetivo
    this->jugadores->reiniciarCursor();
    while(this->jugadores->avanzarCursor() && jugadorBuscado == NULL){
        if (this->jugadores->getCursor()->getNumeroJugador() == nroJugador){
            jugadorBuscado = this->jugadores->getCursor();
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

void DigiBattle::resolverColision(Casillero* casillero, Artilleria artilleria, int nroJugador, int nroSoldado){
    int turnosDesactivar = 5;
    if (casillero->devolverArtilleria() == VACIO){
        casillero->ponerArtilleria(artilleria, nroJugador);
        
    }else if(casillero->devolverArtilleria() == SOLDADO && artilleria == SOLDADO){
        bajarVidaJugador(nroJugador, nroSoldado);
        int jugadorEnemigo = casillero->devolverNroJugador(); // con este numero jugador habria que sacarle soldado al jugador
        int nroSoldadoEnemigo = casillero->devolverNroSoldado();
        bajarVidaJugador(jugadorEnemigo, nroSoldadoEnemigo);
        casillero->ponerArtilleria(VACIO);

    }else if (casillero->devolverArtilleria() == MINA){
        casillero->desactivarCasilla(turnosDesactivar);
        this->casillerosInactivos->add(casillero);
        bajarVidaJugador(nroJugador,nroSoldado);
        casillero->ponerArtilleria(VACIO);
    }
}

void DigiBattle::resolverColision(Casillero* casillero, Artilleria artilleria, int nroJugador){
    int inactivo = 5;
    //casos solo para poner mina barco
    switch(casillero->devolverArtilleria()){
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
        casillero->ponerArtilleria(VACIO);
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
    
    //comprueba si efectivamente el jugador perdio todos sus tropas/vidas
    if (jugador->removerSoldado(nroSoldado) == 0){
        this->jugadores->remover(getPosicionJugadorEnLista(nroJugador));
    }
}

int DigiBattle::getPosicionJugadorEnLista(int nroJugador){
    int posicionJugador = 1;
    this->jugadores->reiniciarCursor();
    while(this->jugadores->avanzarCursor()){
        if(this->jugadores->getCursor()->getNumeroJugador() == nroJugador){
            return posicionJugador;
        }
        posicionJugador ++;
    }

}

Lista<Jugador*>* DigiBattle::getListaJugadores(){
    return this->jugadores;
}

void DigiBattle::reducirCasilleroInactivo(){
    Lista<Casillero*>* casillerosInactivos = this->casillerosInactivos;
    Casillero* casillero;
    int posicion;
    casillerosInactivos->reiniciarCursor();

    while(casillerosInactivos->avanzarCursor()){
        casillero = casillerosInactivos->getCursor();
        if (casillero->disminuirTurnosInactivo()){
            casillerosInactivos->remover(posicion);
        }
        posicion ++;
    }
}

void DigiBattle::anunciarGanador(){
    Jugador* UltimoJugador;
    PosicionUltimoJugador = 0;
    UltimoJugador = this->jugadores->get(PosicionUltimoJugador);
    
    cout<<"La sangrienta guerra llego a su fin , dejandonos como ganador al jugador numero "<< UltimoJugador->getNumeroJugador()<<endl;
    cout<<"El jugador superviviente llego a la victoria,junto con sus "<<UltimoJugador->getListaTropas()->contarElementos();
    cout<<" soldados superviviente"<<endl;
    cout<<" FIN DEL JUEGO "<<endl;
}