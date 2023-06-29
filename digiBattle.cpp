#include "digiBattle.h"
using namespace std;

int obtenerSigno(int valor) {
    return (0 < valor) - (valor < 0);
}

DigiBattle::DigiBattle(){
    this->tablero = new(Tablero);
    this->jugadores = new(Lista<Jugador*>) ;
    this->casillerosInactivos = new(Lista<Casillero*>);
}

DigiBattle::~DigiBattle(){
    delete (this->tablero);
    delete (this->jugadores);
    delete (this->casillerosInactivos);
}

void DigiBattle::iniciarJuego(){

    Ubicacion tableroSize;
    Ubicacion posicionSoldado;
    int cantidadJugadores;
    int cantidadSoldados;
    int dimension;
    do {
        cout << "Ingrese la dimension del mapa (minimo 10): ";
        cin >> dimension;
        cout << endl;
    } while (dimension < 10);
    
    //cin >> dimensionZ
    tableroSize.setX(dimension);
    tableroSize.setY(dimension);    //Revisar esto que esta mal
    tableroSize.setZ(dimension);    //Hay que aclarar la disposicion de las coordenadas al usuario

    this->tablero = new Tablero(tableroSize); //crear tablero
    this->tablero->crearTerreno();
    this->tablero->mostrarTablero(-1);
    
    cout << "Ingrese cantidad de jugadores: ";
    cin >> cantidadJugadores;

    cout <<"Ingrese la cantidad de tropas por jugador: ";
    cin >> cantidadSoldados;
    
    cout << endl;


    jugadores->reiniciarCursor();
    for (int i = 1 ; i <= cantidadJugadores; i++){ //crear jugadores y colocar tropas
        this->tablero->mostrarTablero(i);
        //importante NO TOCAR
        Jugador* nuevoJugador = new Jugador(i);
        this->jugadores->add(nuevoJugador);
        cout << endl << "JUGADOR " << i << endl;
        //Lo deja poner sus tropas
        for (int j = 1 ; j <= cantidadSoldados; j++){
            do {
                cout << "Soldado numero " << j << endl;
                posicionSoldado = this->pedirUbicacion(SOLDADO);
            } while (colisionSoldado(posicionSoldado));
            
            nuevoJugador->agregarTropa(posicionSoldado, j, SOLDADO);  //agrego soldado
            this->tablero->getCasillero(posicionSoldado)->ponerArtilleria(SOLDADO, i, j);  //pone el soldado en el tablero
            this->tablero->mostrarTablero(i);
        }
        
        
    }
}

bool DigiBattle::colisionSoldado(Ubicacion posicionSoldado){
    Casillero* test = this->tablero->getCasillero(posicionSoldado);
    bool check = (test->devolverArtilleria() == SOLDADO);
    if (check == true){
        cout << "No puede ingresar un soldado sobre otro" << endl;
    }
    return check;
}

void DigiBattle::turno(){
    Jugador* jugadorActual;
    char opcion;
    this->jugadores->reiniciarCursor();
    while(!comprobarVictoria()){
        //Determina a quien le toca jugar
        if (!this->jugadores->avanzarCursor()){

            this->jugadores->reiniciarCursor();
            this->jugadores->avanzarCursor();
            this->reducirCasilleroInactivo();
        }
        jugadorActual = this->jugadores->getCursor();
        cout << endl << "TURNO DEL JUGADOR " << jugadorActual->getNumeroJugador() << endl << endl;
        
        this->tablero->mostrarTablero(jugadorActual->getNumeroJugador());
        //Le da una carta al jugador
        this->obtenerCarta(jugadorActual);

        //Poner mina (y disparar con el barco??)
        cout <<"Momento de colocar una mina" << endl;
        this->ponerMina();
        this->tablero->mostrarTablero(jugadorActual->getNumeroJugador());
        this->dispararBarco();
        this->tablero->mostrarTablero(jugadorActual->getNumeroJugador());
        
        //Vemos si quiere mover alguna tropa
        do {
           cout << "Desea mover una tropa? (S/N) "<<endl;
           cin >> opcion;
           cout << endl;
        } while (opcion != 'S' && opcion != 'N' && 
                 opcion != 's' && opcion != 'n');

        if (opcion == 'S' || opcion == 's'){
            this->moverTropa();
        }
        this->tablero->mostrarTablero(jugadorActual->getNumeroJugador());
        
        //Elige si usa una carta o no y cuál
        do { 
           cout << "Desea usar una carta? (S/N) "<<endl;
           cin >> opcion;
           cout << endl;
        } while (opcion != 'S' && opcion != 'N' && 
                 opcion != 's' && opcion != 'n');
        
        if (opcion == 'S' || opcion == 's'){
            this->usarCarta(jugadorActual);
        }
        comprobarVidasDeJugadores(jugadorActual);

    }
    //termina el juego
    this->anunciarGanador(); 
}

void DigiBattle::comprobarVidasDeJugadores(Jugador* jugadorActual){
    bool jugadorActualMuerto = false;
    int nroPosicionJugador = this->getPosicionJugadorEnLista(jugadorActual->getNumeroJugador());
    this->jugadores->reiniciarCursor();
    while(this->jugadores->avanzarCursor()){
        if(this->jugadores->getCursor()->getVidas() == 0){
            if(jugadorActual == this->jugadores->getCursor()){
                jugadorActualMuerto = true;
            }
            removerJugador(this->jugadores->getCursor());
        }
    }
    if (jugadorActualMuerto){
        this->jugadores->avanzarCursor(nroPosicionJugador - 1);
    } else {
        this->jugadores->avanzarCursor(nroPosicionJugador);
    }
}

void DigiBattle::removerJugador(Jugador* jugadorActual){
    delete jugadorActual;
    this->jugadores->remover(this->getPosicionJugadorEnLista(jugadorActual->getNumeroJugador()));
}

void DigiBattle::ponerMina(){
    Ubicacion ubicacionObjetivo;
    Casillero* casilleroObjetivo;
    Artilleria tipoArtilleria = MINA;
    int nroJugador = this->jugadores->getCursor()->getNumeroJugador();
    ubicacionObjetivo = pedirUbicacion(tipoArtilleria);
    casilleroObjetivo = this->tablero->getCasillero(ubicacionObjetivo);

    //resolver colision para minas y misiles
    if (this->resolverColision(casilleroObjetivo)){
        casilleroObjetivo->ponerArtilleria(MINA, nroJugador);
    }

}

void DigiBattle::dispararBarco(){
    Casillero * casilleroDisparado;
    int tirosRestantes = this->jugadores->getCursor()->cantidadTropas(BARCO);

    if (tirosRestantes > 0){
        cout << "Misiles nauticos // ";
    }
    while(tirosRestantes > 0){
        cout << tirosRestantes << " restantes" << endl;
        Ubicacion ubicacionDisparo = pedirUbicacion(MINA);
        casilleroDisparado = this->tablero->getCasillero(ubicacionDisparo);
        this->resolverColision(casilleroDisparado);
        tirosRestantes--;
    }
}

void DigiBattle::moverTropa(){
    Ubicacion ubiTropa, ubiNueva;    
    Jugador* jugador = this->jugadores->getCursor();
    int nroTropaElegida;
 
    Lista<Tropa*>* tropasDelJugador;
    int tipoTropa;
    Artilleria seleccionTropa = VACIO;


    //Pregunta qué tipo de tropa se quiere mover
    cout << "Elija el tipo de tropa" << endl;

        //Se fija cuales están disponibles
        tropasDelJugador = this->jugadores->getCursor()->getListaTropas();
        int soldados = 0;
        int barcos = 0;
        int aviones = 0;
        tropasDelJugador->reiniciarCursor();
        while(tropasDelJugador->avanzarCursor()){
            if (tropasDelJugador->getCursor()->getTipoTropa() == SOLDADO){
                soldados++;
            } else if (tropasDelJugador->getCursor()->getTipoTropa() == BARCO){
                barcos++;
            } else if (tropasDelJugador->getCursor()->getTipoTropa() == AVION){
                aviones++;
            }
        }
    
    cout << "1 - Soldados Disponibles: " << soldados << endl;
    cout << "2 - Aviones Disponibles: " << aviones << endl;
    cout << "3 - Barcos Disponibles: " << barcos << endl << endl;

    //Permite elgir
    do{
        cout << "Elige con sabiduria: ";
        cin >> tipoTropa;
        cout << endl;
        seleccionTropa = static_cast<Artilleria>(tipoTropa);
    } while (!comprobarSeleccionTropa(seleccionTropa, aviones, barcos));

    //Muestra las tropas del tipo disponibles para usar y permite elegir la tropa a mover
    mostrarTropasDisponibles(seleccionTropa, tropasDelJugador);
    nroTropaElegida = pedirNumeroTropa(jugador, seleccionTropa);
    ubiTropa = jugador->getUbicacionTropa(nroTropaElegida, seleccionTropa);

    //Pedir ubicacion y mover a la tropa
    ubiNueva = this->pedirUbicacion(seleccionTropa);

    bool tropaViva = true;
    int diferenciaX = ubiNueva.getX() - ubiTropa.getX();
    int diferenciaY = ubiNueva.getY() - ubiTropa.getY();
    int cant = (diferenciaX != 0) ? abs(diferenciaX) : abs(diferenciaY);

    //Si el movimiento es valido y la tropa no es avion, movemos
    if (seleccionTropa != AVION){
        while(!validarDestinoSoldado(ubiTropa, ubiNueva)){
            cout<<"Coordenadas fuera del alcance del soldado"<<endl;
            ubiNueva = this->pedirUbicacion(seleccionTropa);
            diferenciaX = ubiNueva.getX() - ubiTropa.getX();
            diferenciaY = ubiNueva.getY() - ubiTropa.getY();
            cant = (diferenciaX != 0) ? abs(diferenciaX) : abs(diferenciaY);
        }
        Ubicacion ubiActual = ubiTropa;
        while (tropaViva && (cant > 0)) {   //cant == movimientos restantes
            ubiTropa = ubiActual;
            ubiActual.setX(ubiActual.getX() + obtenerSigno(diferenciaX));
            ubiActual.setY(ubiActual.getY() + obtenerSigno(diferenciaY));
            tropaViva = resolverColision(tablero->getCasillero(ubiTropa), tablero->getCasillero(ubiActual), ubiActual);

            //controla que no se mueva más de la cuenta
            cant--;
        }
    } else if (seleccionTropa == AVION) {
        while(!resolverColision(tablero->getCasillero(ubiTropa), tablero->getCasillero(ubiNueva), ubiNueva)){
            cout << "La posicion elegida ya tiene un avion" << endl;
            ubiNueva = this->pedirUbicacion(seleccionTropa);
        }
    }
}

int DigiBattle::pedirNumeroTropa(Jugador * jugador, Artilleria seleccionTropa){
    int nroTropaElegida;
    do{
        cout << "Mover tropa numero: ";
        cin >> nroTropaElegida;
        cout << endl;
    } while(jugador->tropaViva(nroTropaElegida, seleccionTropa));
    return nroTropaElegida;
}

void DigiBattle::mostrarTropasDisponibles(Artilleria seleccionTropa, Lista<Tropa*>* tropasDelJugador){
    Ubicacion posicion;
    
    cout << "TROPAS DISPONIBLES" << endl;
    
    tropasDelJugador->reiniciarCursor();
    while(tropasDelJugador->avanzarCursor()){
        if(tropasDelJugador->getCursor()->getTipoTropa() == seleccionTropa){
            posicion = tropasDelJugador->getCursor()->getUbicacion();

            cout << "Tropa Numero: " << tropasDelJugador->getCursor()->getNroTropa();
            cout << " // Posicion X: " << posicion.getX();
            cout << " Y: " << posicion.getY() << endl;
            //Soldado No 1 // Posicion X:7 Y:4
        }
    }
}

bool DigiBattle::comprobarSeleccionTropa(Artilleria seleccionTropa, int cantidadAviones, int cantidadBarcos){
    if ((seleccionTropa == AVION && cantidadAviones == 0) || 
        (seleccionTropa == BARCO && cantidadBarcos == 0) || 
        (seleccionTropa > 3) || (seleccionTropa < 1)){
        return false;
    }
    return true;
}

bool DigiBattle::validarCasillero(Ubicacion posicion, Artilleria tipo){
    Casillero* casillero;

    //si las coordenadas existen sigue, sino false
    if(!this->tablero->validarCoordenadas(posicion)){
        cout<<"Coordenadas ingresadas fuera de rango"<< endl;
        return false;
    }

    casillero = this->tablero->getCasillero(posicion);

    //si el terreno es compatible con la artillería sigue, sino false
    if(!casillero->comprobarTerreno(tipo)){
        cout<<"Terreno seleccionado invalido"<< endl;
        return false;  //valido que no sea casillero aire
    }   
        //vemos si el casillero no esta inactivo
    if(!casillero->comprobarEstado()){
        cout<<"Casillero seleccionado momentaneamente inactivo"<< endl;
        return false;  //valido que no sea casillero aire
    }

    return true;
}

bool DigiBattle::validarDestinoSoldado(Ubicacion ubiAnterior, Ubicacion ubiNueva){
    int distanciaX = abs(ubiAnterior.getX() - ubiNueva.getX());
    int distanciaY = abs(ubiAnterior.getY() - ubiNueva.getY());
    // Valida que la distancia a mover sea inferior a 3, que no se mueva al mismo casillero y que solo se pueda mover en diagonal u horizontal :)
    if((distanciaX > 3 || distanciaY > 3) ||
       (distanciaX != distanciaY && distanciaX != 0 && distanciaY != 0) || 
       (ubiAnterior.getX() == ubiNueva.getX() && ubiAnterior.getY() == ubiNueva.getY())){
        return false;
    }
    return true;
}

Ubicacion DigiBattle::pedirUbicacion(Artilleria tipo){
    Ubicacion posicion;
    int x, y, z;

    //si las coordenadas no son válidas, vuelve a pedir
    do{
        //solo pide Z (altura) si la artillería es un avión
        if (tipo != AVION && tipo != VACIO) {
            cout << "Coordenada X: ";
            cin >> x;
            cout << "Coordenada Y: ";
            cin >> y;
            cout << endl;
            posicion.setUbicacion(x, y, 5);
        } else {
            cout << "Coordenada X: "<< endl;
            cin >> x;
            cout << "Coordenada Y: "<< endl;
            cin >> y;
            cout << "Coordenada Z: "<< endl;
            cin >> z;
            cout << endl;
            posicion.setUbicacion(x, y, z);
        } 
    } while (!validarCasillero(posicion, tipo));

    return posicion;
}

void DigiBattle::obtenerCarta(Jugador * jugador){
    jugador->addCarta();
    int numCarta = jugador->cantidadCartas();
    cout<<"Carta obtenida: ";
    jugador->nombreCarta(jugador->getListaCartas()->get(numCarta));
    cout << endl;
    }

void DigiBattle::usarCarta(Jugador* jugador){
    jugador->informarCartasDisponibles();
    int numeroCarta;

    do{
        cout<<"Carta elegida: ";
        cin >> numeroCarta;
        cout << endl;
    }while(jugador->cantidadCartas() < numeroCarta);
    
    Tipos tipo = jugador->getCarta(numeroCarta);
    
    switch(tipo){
        case ATAQUEQUIMICO:
            cartaAtaqueQuimico();
            break;
        case AVIONRADAR:
            cartaAvionRadar(jugador);
            break;
        case INVOCARBARCO:
            cartaBarco(jugador);
            break;
        case POTOFGREED:
            cartaPotOfGreed(jugador);
            break;
        case SOLDADOSEXTRA:
            cartaAgregarSoldados(jugador);
            break;
        case RAYOLASER:
            cartaRayoLaser(jugador);
            break;
    }
}

Jugador* DigiBattle::buscarJugador(int nroJugador){
    Jugador* jugadorBuscado = NULL;
    
    //Guardamos el numero de jugador anterior
    int jugadorAntiguo = this->jugadores->getCursor()->getNumeroJugador();
    bool posicionAntiguaEncontrada = false;
    
    //Reiniciamos el cursor y buscamos al jugador objetivo
    this->jugadores->reiniciarCursor();
    while(jugadorBuscado == NULL && this->jugadores->avanzarCursor()){
        if (this->jugadores->getCursor()->getNumeroJugador() == nroJugador){
            jugadorBuscado = this->jugadores->getCursor();
        }
    }
    
    //Vuelve a poner el cursor en la posicion anterior
    jugadores->reiniciarCursor();
    while(posicionAntiguaEncontrada == false && this->jugadores->avanzarCursor()){
        if (jugadores->getCursor()->getNumeroJugador() == jugadorAntiguo){
            posicionAntiguaEncontrada = true;
        }
    }
    return jugadorBuscado;
}

int DigiBattle::poderMina(){
    srand(time(NULL));
    return(3 + (rand() % 4));
}

bool DigiBattle::resolverColision(Casillero* casilleroNuevo){
    Artilleria tipoTropaDestino = casilleroNuevo->devolverArtilleria();
    int jugadorEnemigo = casilleroNuevo->devolverNroJugador();
    int nroTropaEnemiga = casilleroNuevo->devolverNroTropa();
    switch (tipoTropaDestino){
    case SOLDADO:
        sacarTropaJugador(jugadorEnemigo, nroTropaEnemiga, SOLDADO);
        casilleroNuevo->desactivarCasilla(this->poderMina());
        this->casillerosInactivos->add(casilleroNuevo);
        return false;
        break;
    case BARCO:
        if (!this->buscarJugador(jugadorEnemigo)->bajarVidaBarco(nroTropaEnemiga)){
            sacarTropaJugador(jugadorEnemigo, nroTropaEnemiga, BARCO);
            casilleroNuevo->desactivarCasilla(this->poderMina());
            this->casillerosInactivos->add(casilleroNuevo);
        }
        return false;
        break;

    case VACIO:
        return true;
        break;
    }
    return false;
}

bool DigiBattle::resolverColision(Casillero* casilleroAnterior, Casillero* casilleroNuevo, Ubicacion ubicacion){

    Artilleria tipoTropaOrigen = casilleroAnterior->devolverArtilleria();
    Artilleria tipoTropaDestino = casilleroNuevo->devolverArtilleria();
    int nroJugadorDuenho = casilleroAnterior->devolverNroJugador();
    int nroTropaOrigen = casilleroAnterior->devolverNroTropa();
    Jugador* jugadorActual;

    //si el casillero destino está vacío, se mueve la tropa
    if (tipoTropaDestino == VACIO){
        //coloca la tropa en el casillero nuevo
        casilleroAnterior->vaciarCasillero();
        casilleroNuevo->ponerArtilleria(tipoTropaOrigen, nroJugadorDuenho, nroTropaOrigen);
        //actualiza la lista del jugador
        jugadorActual = buscarJugador(nroJugadorDuenho);
        jugadorActual->setPosicionTropa(nroTropaOrigen, tipoTropaOrigen, ubicacion);
        return true;
    
    } else if(tipoTropaOrigen == SOLDADO && tipoTropaDestino == SOLDADO){
        sacarTropaJugador(nroJugadorDuenho, nroTropaOrigen, SOLDADO);
        int jugadorEnemigo = casilleroNuevo->devolverNroJugador(); // con este numero jugador habria que sacarle soldado al jugador
        int nroSoldadoEnemigo = casilleroNuevo->devolverNroTropa();
        sacarTropaJugador(jugadorEnemigo, nroSoldadoEnemigo, SOLDADO);
        casilleroAnterior->vaciarCasillero();
        casilleroNuevo->vaciarCasillero();
        return false;
    } else if (tipoTropaDestino == MINA){
        int turnosDesactivar = poderMina();
        casilleroAnterior->vaciarCasillero();
        casilleroNuevo->desactivarCasilla(turnosDesactivar);
        this->casillerosInactivos->add(casilleroNuevo);
        sacarTropaJugador(nroJugadorDuenho,nroTropaOrigen, SOLDADO);
        return false;
    } else if (tipoTropaOrigen == AVION && tipoTropaDestino == AVION){
        return false;
    } else if (tipoTropaOrigen == SOLDADO && tipoTropaDestino == BARCO){
        sacarTropaJugador(nroJugadorDuenho, nroTropaOrigen, SOLDADO);
        casilleroAnterior->vaciarCasillero();
        int jugadorEnemigo = casilleroNuevo->devolverNroJugador();
        int nroTropaEnemiga = casilleroNuevo->devolverNroTropa();
        if (!this->buscarJugador(jugadorEnemigo)->bajarVidaBarco(nroTropaEnemiga)){
            sacarTropaJugador(jugadorEnemigo, nroTropaEnemiga, BARCO);
            casilleroNuevo->vaciarCasillero();
        }
        return false;
    }
}

bool DigiBattle::comprobarVictoria(){ 
    //vemos si quedo solo un jugador
    return (this->jugadores->contarElementos() == 1);   
}

void DigiBattle::sacarTropaJugador(int nroJugador, int nroTropa, Artilleria artilleria){
    Jugador* jugador = this->buscarJugador(nroJugador);
    jugador->removerTropa(nroTropa, artilleria);
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

void DigiBattle::reducirCasilleroInactivo(){
    Lista<Casillero*>* casillerosInactivos = this->casillerosInactivos;
    Casillero* casillero;
    int posicion = 1;
    casillerosInactivos->reiniciarCursor();
    while(casillerosInactivos->avanzarCursor()){
        casillero = casillerosInactivos->getCursor();
        if (casillero->disminuirTurnosInactivo()){
            if(casillero->esToxico()){
                casillero->setToxico(false);
            }
            casillero->vaciarCasillero();
            casillerosInactivos->remover(posicion);
            casillerosInactivos->avanzarCursor(posicion - 1);
        } else {
            posicion ++;
        }
    }
}

void DigiBattle::resolverColisionQuimico(Casillero* casilleroNuevo, int inactivo){
    Artilleria tipoTropaDestino = casilleroNuevo->devolverArtilleria();
    int jugadorEnemigo = casilleroNuevo->devolverNroJugador();
    int nroTropaEnemiga = casilleroNuevo->devolverNroTropa();
    if (tipoTropaDestino == SOLDADO || tipoTropaDestino == BARCO){
        sacarTropaJugador(jugadorEnemigo, nroTropaEnemiga, tipoTropaDestino);
        casilleroNuevo->desactivarCasilla(inactivo);
        this->casillerosInactivos->add(casilleroNuevo);
    }
    casilleroNuevo->desactivarCasilla(inactivo);
    this->casillerosInactivos->add(casilleroNuevo);
    casilleroNuevo->setToxico(true);
}

void DigiBattle::cartaAtaqueQuimico(){
    const int RANGOATAQUEQUIMICO = 5;       // RANGOATAQUEQUIMICO debe ser impar
    int efectoAtaqueQuimico = 10;
    int radioCubo = RANGOATAQUEQUIMICO / 2;
    int i, j, k;
    Ubicacion nuevaUbicacion;
    Casillero * casilleroActual;
    Ubicacion ubicacion = this->pedirUbicacion(VACIO);
    while(ubicacion.getX() < 3 || ubicacion.getY() < 3 || ubicacion.getZ() < 3 ||
        ubicacion.getX() > (this->tablero->getTamanhoTableroX() - 2) ||
        ubicacion.getY() > (this->tablero->getTamanhoTableroY() - 2) || 
        ubicacion.getZ() > (this->tablero->getTamanhoTableroZ() - 2)){
            cout << "Coordenadas ingresadas no validas" << endl;
            ubicacion = this->pedirUbicacion(VACIO);
        }
    for(i = (-radioCubo); i <= radioCubo; i++){
        for (j = (-radioCubo); j <= radioCubo; j++){
            for (k = (-radioCubo); k <= radioCubo; k++){
                nuevaUbicacion.setX(ubicacion.getX() + i);
                nuevaUbicacion.setY(ubicacion.getY() + j);
                nuevaUbicacion.setZ(ubicacion.getZ() + k);
                if((i == 0) && (j == 0) && (k == 0)){        
                    casilleroActual = this->tablero->getCasillero(nuevaUbicacion);
                    resolverColisionQuimico(casilleroActual, efectoAtaqueQuimico);
                } else if(abs(i) == 2 || abs(j) == 2 || abs(k) == 2){
                    casilleroActual = this->tablero->getCasillero(nuevaUbicacion);
                    resolverColisionQuimico(casilleroActual, efectoAtaqueQuimico - 4);
                } else if(abs(i) == 1 || abs(j) == 1 || abs(k) == 1){
                    casilleroActual = this->tablero->getCasillero(nuevaUbicacion);
                    resolverColisionQuimico(casilleroActual, efectoAtaqueQuimico - 2);
                }
            }
        }
    }
}

void DigiBattle::cartaAvionRadar(Jugador * jugador){
    Ubicacion posicion = pedirUbicacion(AVION);
    Casillero* casilleroActual = this->tablero->getCasillero(posicion);
    int posicionTropaAvion = jugador->getNumSiguienteAvion();
    casilleroActual->ponerArtilleria(AVION, jugador->getNumeroJugador(), jugador->getNumSiguienteAvion());
    jugador->agregarTropa(posicion , posicionTropaAvion, AVION);
}

void DigiBattle::cartaBarco(Jugador * jugador){
    Ubicacion ubicacion = pedirUbicacion(BARCO);
    int nroTropaBarco = jugador->getNumSiguienteBarco();
    jugador->agregarTropa(ubicacion , nroTropaBarco, BARCO);
    this->tablero->getCasillero(ubicacion);
    this->tablero->getCasillero(ubicacion)->ponerArtilleria(BARCO, jugador->getNumeroJugador(), nroTropaBarco);  //pone la tropa en el tablero
}

void DigiBattle::cartaPotOfGreed(Jugador * jugador){
    int i;
    for (i = 1; i <= 2; i++){
        this->obtenerCarta(jugador);
    }
}

void DigiBattle::cartaAgregarSoldados(Jugador * jugador){
    int i;
    for (i = 1; i <= 2; i++){
        int nroSiguienteSoldado = jugador->getNumSiguienteSoldado();
        cout <<"Soldado numero " << nroSiguienteSoldado << endl;
        Ubicacion ubicacion = pedirUbicacion(SOLDADO);
        if(resolverColision(this->tablero->getCasillero(ubicacion))){
            jugador->agregarTropa(ubicacion, nroSiguienteSoldado, SOLDADO);
            this->tablero->getCasillero(ubicacion)->ponerArtilleria(SOLDADO, jugador->getNumeroJugador(), nroSiguienteSoldado);
        }
    this->tablero->mostrarTablero(jugador->getNumeroJugador());
    }
}

void DigiBattle::cartaRayoLaser(Jugador * jugador){
    char direccion;
    int tropaElegida;
    int nroJugador;
    int nroTropa;
    Artilleria tipoArtilleriaCasilla;
    Ubicacion posicionActual;
    Lista<Tropa*>* tropasDelJugador;
    Casillero * casilleroActual;
    tropasDelJugador = jugador->getListaTropas();
    cout << "Elija el soldado que tirara el rayo laser" << endl;
    mostrarTropasDisponibles(SOLDADO, tropasDelJugador);
    tropaElegida = pedirNumeroTropa(jugador, SOLDADO);
    posicionActual = jugador->getUbicacionTropa(tropaElegida, SOLDADO);
    casilleroActual = this->tablero->getCasillero(posicionActual);
    cout << "Elija la direccion del rayo"<< endl;
    cout << "W - arriba" << endl;
    cout << "A - izquierda" << endl;
    cout << "S - abajo" << endl;
    cout << "D - derecha" << endl << endl;
    cout << "Seleccion: ";
    cin >> direccion;
    cout << endl;
    while(direccion != 'W' && direccion != 'A' &&
        direccion != 'S' && direccion != 'D'){
        cout << "Seleccion invalida: ";
        cin >> direccion;
        cout << endl;
    }
    if (direccion == 'S'){
        posicionActual.setY(posicionActual.getY() + 1);
        while (posicionActual.getY() <= this->tablero->getTamanhoTableroY()){
            tipoArtilleriaCasilla = this->tablero->getCasillero(posicionActual)->devolverArtilleria();
            if (tipoArtilleriaCasilla == SOLDADO || tipoArtilleriaCasilla == BARCO){
                nroJugador = this->tablero->getCasillero(posicionActual)->devolverNroJugador();
                nroTropa = this->tablero->getCasillero(posicionActual)->devolverNroTropa();
                sacarTropaJugador(nroJugador, nroTropa, tipoArtilleriaCasilla);
            }
            this->tablero->getCasillero(posicionActual)->desactivarCasilla(5);
            this->casillerosInactivos->add(casilleroActual);
            posicionActual.setY(posicionActual.getY() + 1);
        }
    } else if (direccion == 'A'){
        posicionActual.setX(posicionActual.getX() - 1);
        while (posicionActual.getX() > 0){
            tipoArtilleriaCasilla = this->tablero->getCasillero(posicionActual)->devolverArtilleria();
            if (tipoArtilleriaCasilla == SOLDADO || tipoArtilleriaCasilla == BARCO){
                nroJugador = this->tablero->getCasillero(posicionActual)->devolverNroJugador();
                nroTropa = this->tablero->getCasillero(posicionActual)->devolverNroTropa();
                sacarTropaJugador(nroJugador, nroTropa, tipoArtilleriaCasilla);
            }
            this->tablero->getCasillero(posicionActual)->desactivarCasilla(5);
            this->casillerosInactivos->add(casilleroActual);
            posicionActual.setX(posicionActual.getX() - 1);

        }
    } else if (direccion == 'W'){
        posicionActual.setY(posicionActual.getY() - 1);
        while (posicionActual.getY() > 0){
            tipoArtilleriaCasilla = this->tablero->getCasillero(posicionActual)->devolverArtilleria();
            if (tipoArtilleriaCasilla == SOLDADO || tipoArtilleriaCasilla == BARCO){
                nroJugador = this->tablero->getCasillero(posicionActual)->devolverNroJugador();
                nroTropa = this->tablero->getCasillero(posicionActual)->devolverNroTropa();
                sacarTropaJugador(nroJugador, nroTropa, tipoArtilleriaCasilla);
            }
            this->tablero->getCasillero(posicionActual)->desactivarCasilla(5);
            this->casillerosInactivos->add(casilleroActual);
            posicionActual.setY(posicionActual.getY() - 1);

        }
    } else if (direccion == 'D'){
        posicionActual.setX(posicionActual.getX() + 1);
        while (posicionActual.getX() <= this->tablero->getTamanhoTableroX()){
            tipoArtilleriaCasilla = this->tablero->getCasillero(posicionActual)->devolverArtilleria();
            if (tipoArtilleriaCasilla == SOLDADO || tipoArtilleriaCasilla == BARCO){
                nroJugador = this->tablero->getCasillero(posicionActual)->devolverNroJugador();
                nroTropa = this->tablero->getCasillero(posicionActual)->devolverNroTropa();
                sacarTropaJugador(nroJugador, nroTropa, tipoArtilleriaCasilla);
            }
            this->tablero->getCasillero(posicionActual)->desactivarCasilla(5);
            this->casillerosInactivos->add(casilleroActual);
            posicionActual.setX(posicionActual.getX() + 1);
        }
    }
    
    

}

void DigiBattle::anunciarGanador(){
    this->jugadores->reiniciarCursor();
    this->jugadores->avanzarCursor();
    Jugador* ganador = this->jugadores->getCursor();
    cout << endl;
    cout << "-----------------------------------------------------------------------------------"<<endl;
    cout << "La sangrienta guerra llego a su fin , dejandonos como ganador al jugador "<< ganador->getNumeroJugador() << endl;
    cout << "El jugador superviviente llego a la victoria, junto con sus "<< ganador->getListaTropas()->contarElementos();
    cout <<" soldados supervivientes"<<endl;
    cout <<" FIN DEL JUEGO "<<endl;
    cout <<"-----------------------------------------------------------------------------------"<<endl;
}    
