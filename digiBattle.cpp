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
    int nroSoldado; // unused
    int dimension;

    cout << "Ingrese la dimension del mapa: " << endl;
    cin >> dimension;
    //cin >> dimensionZ
    tableroSize.x = dimension;
    tableroSize.y = dimension;    //Revisar esto que esta mal
    tableroSize.z = dimension;    //Hay que aclarar la disposicion de las coordenadas al usuario

    this->tablero = new Tablero(tableroSize); //crear tablero
    this->tablero->crearTerreno();
    this->tablero->mostrarTablero();
    
    cout << "Ingrese cantidad de jugadores: " << endl;
    cin >> cantidadJugadores;

    cout <<"Ingrese la cantidad de tropas por jugador: "<< endl;
    cin >> cantidadSoldados;
    


    jugadores->reiniciarCursor();
    for (int i = 1 ; i <= cantidadJugadores; i++){ //crear jugadores y colocar tropas

        //importante NO TOCAR
        
        Jugador* nuevoJugador = new Jugador(i);
        this->jugadores->add(nuevoJugador);
        cout << endl << "Jugador numero: " << i << endl;
        //Lo deja poner sus tropas
        for (int j = 1 ; j <= cantidadSoldados; j++){
            do {
                cout << "Soldado numero: " << j << endl;
                posicionSoldado = this->pedirUbicacion(SOLDADO);
            } while (friendlyFire(posicionSoldado, i));
            
            nuevoJugador->agregarTropa(posicionSoldado, j, SOLDADO);  //agrego soldado
            this->tablero->getCasillero(posicionSoldado)->ponerArtilleria(SOLDADO, i, j);  //pone el soldado en el tablero
            this->tablero->mostrarTablero();
        }
        
        
    }
}

bool DigiBattle::friendlyFire(Ubicacion posicionSoldado, int numJugador){
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
        this->tablero->mostrarTablero();
        //Determina a quien le toca jugar
        if (!this->jugadores->avanzarCursor()){
            this->jugadores->reiniciarCursor();
        }
        jugadorActual = this->jugadores->getCursor();
        cout <<"Turno del jugador numero " << jugadorActual->getNumeroJugador() <<endl;
        //Le da una carta al jugador
        this->obtenerCarta(jugadorActual);

        //Poner mina (y disparar con el barco??)
        cout <<"Momento de colocar una mina " << endl;
        this->ponerMina();
        this->tablero->mostrarTablero();
        this->dispararBarco();
        this->tablero->mostrarTablero();
        
        //Vemos si quiere mover alguna tropa
        do {
           cout << "Quiere realizar un movimiento de alguna tropa ? S/N "<<endl;
           cin >> opcion;
        } while (opcion != 'S' && opcion != 'N');

        if (opcion == 'S'){
            this->moverTropa();
        }
        this->tablero->mostrarTablero();
        
        //Elige si usa una carta o no y cuál
        do { 
           cout << "Quiere invocar alguna de sus cartas ? S/N "<<endl;
           cin >> opcion;
        } while (opcion != 'S' && opcion != 'N');
        
        if (opcion == 'S'){
            this->usarCarta(jugadorActual);
        }

        //Reducir cuenta de los casilleros inactivos
        this->reducirCasilleroInactivo();
    }
    this->anunciarGanador(); //termino el juego
}

void DigiBattle::ponerMina(){
    Ubicacion ubicacionObjetivo;
    Casillero* casilleroObjetivo;
    Artilleria tipoArtilleria = MINA;
    int nroJugador = this->jugadores->getCursor()->getNumeroJugador();
    int turnosCasillaDesactivada = poderMina();


    ubicacionObjetivo = pedirUbicacion(tipoArtilleria);
    casilleroObjetivo = this->tablero->getCasillero(ubicacionObjetivo);
    
    //resolver colision para minas y misiles
    if (!this->resolverColision(casilleroObjetivo)){
        casilleroObjetivo->desactivarCasilla(turnosCasillaDesactivada);
    } else {
        casilleroObjetivo->ponerArtilleria(MINA, nroJugador);
    }

}

void DigiBattle::dispararBarco(){
    Casillero * casilleroDisparado;
    int tirosRestantes = this->jugadores->getCursor()->cantidadTropas(BARCO);
    while(tirosRestantes > 0){
        cout << "Tiro de barcos restantes: " << tirosRestantes << endl;
        Ubicacion ubicacionDisparo = pedirUbicacion();
        casilleroDisparado = this->tablero->getCasillero(ubicacionDisparo);
        this->resolverColision(casilleroDisparado);
        tirosRestantes--;
    }

    //usar resolverColision() para minas y misiles
}

void DigiBattle::moverTropa(){
    Ubicacion ubiTropa, ubiNueva;    
    Jugador* jugador = this->jugadores->getCursor();
    int nroTropaElegida;
 
    Lista<InfoTropa*>* tropasDelJugador;
    int tipoTropa;
    Artilleria seleccionTropa = VACIO;


    //Pregunta qué tipo de tropa se quiere mover
    cout << "Elige que tipo de tropa mover: " << endl;

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
    } while (!comprobarSeleccionTropa(seleccionTropa, aviones, barcos));
    //Mostrar las tropas disponibles a usar y elegir la tropa a mover
    mostrarTropasDisponibles(seleccionTropa, tropasDelJugador);
    nroTropaElegida = pedirNumeroTropa(jugador, seleccionTropa);
    ubiTropa = jugador->getUbicacionTropa(nroTropaElegida, seleccionTropa);

    //Pedir ubicacion y mover a la tropa
    ubiNueva = this->pedirUbicacion(seleccionTropa);

    bool tropaViva = true;
    int diferenciaX = ubiNueva.x - ubiTropa.x;
    int diferenciaY = ubiNueva.y - ubiTropa.y;
    int cant = (diferenciaX != 0) ? abs(diferenciaX) : abs(diferenciaY);

    //Si el movimiento es valido y la tropa no es avion, movemos
    if (seleccionTropa != AVION){
        while(!validarDestinoSoldado(ubiTropa, ubiNueva)){
            cout<<"Ingreso coordenadas fuera del alcance del soldado"<<endl;
            ubiNueva = this->pedirUbicacion(seleccionTropa);
            diferenciaX = ubiNueva.x - ubiTropa.x;
            diferenciaY = ubiNueva.y - ubiTropa.y;
            cant = (diferenciaX != 0) ? abs(diferenciaX) : abs(diferenciaY);
        }
        Ubicacion ubiActual = ubiTropa;
        while (tropaViva && (cant > 0)) {   //cant == movimientos restantes
            ubiTropa = ubiActual;
            ubiActual.x += obtenerSigno(diferenciaX);
            ubiActual.y += obtenerSigno(diferenciaY);
            tropaViva = resolverColision(tablero->getCasillero(ubiTropa), tablero->getCasillero(ubiActual), ubiActual);

            //controla que no se mueva más de la cuenta
            cant--;
        }
    } else if (seleccionTropa == AVION) {
        while(!resolverColision(tablero->getCasillero(ubiTropa), tablero->getCasillero(ubiNueva), ubiNueva)){
            cout << "La posicion elegida tiene un avion ya existente" << endl;
            ubiNueva = this->pedirUbicacion(seleccionTropa);
        }
    }
}

int DigiBattle::pedirNumeroTropa(Jugador * jugador, Artilleria seleccionTropa){
    int nroTropaElegida;
    do{
        cout << "Elija el numero de tropa a mover" << endl;
        cin >> nroTropaElegida;
    } while(jugador->tropaViva(nroTropaElegida, seleccionTropa));
    return nroTropaElegida;
}

void DigiBattle::mostrarTropasDisponibles(Artilleria seleccionTropa, Lista<InfoTropa*>* tropasDelJugador){
    Ubicacion posicion;
    
    cout << "TROPAS DISPONIBLES" << endl;
    
    tropasDelJugador->reiniciarCursor();
    while(tropasDelJugador->avanzarCursor()){
        if(tropasDelJugador->getCursor()->tropa == seleccionTropa){
            posicion = tropasDelJugador->getCursor()->posicion;

            cout << "Tropa Numero: " << tropasDelJugador->getCursor()->nroTropa;
            cout << " // Posicion X: " << posicion.x;
            cout << " Y: " << posicion.y << endl;
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
        cout<<"casillero seleccionado momentaneamente inactivo"<< endl;
        return false;  //valido que no sea casillero aire
    }

    return true;
}

bool DigiBattle::validarDestinoSoldado(Ubicacion ubiAnterior, Ubicacion ubiNueva){
    int distanciaX = abs(ubiAnterior.x - ubiNueva.x);
    int distanciaY = abs(ubiAnterior.y - ubiNueva.y);
    // Valida que la distancia a mover sea inferior a 3, que no se mueva al mismo casillero y que solo se pueda mover en diagonal u horizontal :)
    if((distanciaX > 3 || distanciaY > 3) ||
       (distanciaX != distanciaY && distanciaX != 0 && distanciaY != 0) || 
       (ubiAnterior.x == ubiNueva.x && ubiAnterior.y == ubiNueva.y)){
        return false;
    }
    return true;
}

Ubicacion DigiBattle::pedirUbicacion(){
    Ubicacion posicion;
    //si las coordenadas no son válidas, vuelve a pedir
    cout<<"Ingrese coordenada X : "<< endl;
    cin>>posicion.x;
    cout<<"Ingrese coordenada Y : "<< endl;
    cin>>posicion.y;
    cout<<"Ingrese coordenada Z : "<< endl;
    cin>>posicion.z;

    while (!this->tablero->validarCoordenadas(posicion)){

        cout<<"Coodenadas ingresadas fuera rango"<< endl;

        cout<<"Ingrese coordenada X : "<< endl;
        cin>>posicion.x;
        cout<<"Ingrese coordenada Y : "<< endl;
        cin>>posicion.y;
        cout<<"Ingrese coordenada Z : "<< endl;
        cin>>posicion.z;
    }
    return posicion;
}

Ubicacion DigiBattle::pedirUbicacion(Artilleria tipo){
    Ubicacion posicion;

    //si las coordenadas no son válidas, vuelve a pedir
    do{
        //solo pide Z (altura) si la artillería es un avión
        if (tipo != AVION && tipo != VACIO) {
            posicion.z = 1;
            cout << "Ingrese coordenada X : "<< endl;
            cin >> posicion.x;
            cout << "Ingrese coordenada Y : "<< endl;
            cin >> posicion.y;
        
        } else {
            cout << "Ingrese coordenada X : "<< endl;
            cin >> posicion.x;
            cout << "Ingrese coordenada Y : "<< endl;
            cin >> posicion.y;
            cout << "Ingrese coordenada Z : "<< endl;
            cin >> posicion.z;
        } 
    } while (!validarCasillero(posicion, tipo));

    return posicion;
}

void DigiBattle::obtenerCarta(Jugador * jugador){
    jugador->addCarta();
    int numCarta = jugador->cantidadCartas();
    cout<<"Obtuvo la carta : " << endl;
    jugador->nombreCarta(jugador->getListaCartas()->get(numCarta));
}

void DigiBattle::usarCarta(Jugador* jugador){
    jugador->informarCartasDisponibles();
    int numeroCarta;

    do{
        cout<<"Ingrese el numero de carta que desea usar "<<endl;
        cin >> numeroCarta;
    }while(jugador->cantidadCartas() < numeroCarta);
    
    Tipos tipo = jugador->getCarta(numeroCarta);
    
    switch(tipo){
        case ATAQUEQUIMICO:
            cartaAtaqueQuimico(this->pedirUbicacion(VACIO));
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
    int nroSoldadoEnemigo = casilleroNuevo->devolverNroTropa();
    switch (tipoTropaDestino){
    case SOLDADO:
        sacarTropaJugador(jugadorEnemigo, nroSoldadoEnemigo, SOLDADO);
        casilleroNuevo->vaciarCasillero();
        break;
    
    case BARCO:
        sacarTropaJugador(jugadorEnemigo, nroSoldadoEnemigo, BARCO);
        casilleroNuevo->vaciarCasillero();
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
    }
}

bool DigiBattle::comprobarVictoria(){ 
    //vemos si quedo solo un jugador
    return (this->jugadores->contarElementos() == 1);   
}

void DigiBattle::sacarTropaJugador(int nroJugador, int nroTropa, Artilleria artilleria){
    Jugador* jugador = this->buscarJugador(nroJugador);

    //comprueba si efectivamente el jugador perdio todos sus tropas/vidas
    if (jugador->removerTropa(nroTropa, artilleria) == 0){
        this->jugadores->remover(getPosicionJugadorEnLista(nroJugador));
        delete jugador;
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
    int posicion = 1;
    casillerosInactivos->reiniciarCursor();
    while(casillerosInactivos->avanzarCursor()){
        casillero = casillerosInactivos->getCursor();
        if (casillero->disminuirTurnosInactivo()){
            casillerosInactivos->remover(posicion);
            if(casillero->esToxico()){
                casillero->setToxico(false);
            }
        }
        posicion ++;
    }
}

void DigiBattle::cartaAtaqueQuimico(Ubicacion posicion){
    const int RANGOATAQUEQUIMICO = 5;       // RANGOATAQUEQUIMICO debe ser impar
    int efectoAtaqueQuimico = 10;
    int radioCubo = RANGOATAQUEQUIMICO / 2;
    int i, k, j;
    Ubicacion nuevo;
    Casillero * casilleroActual;

    for(i = (-radioCubo); i <= radioCubo; i++){
        for (j = (-radioCubo); j <= radioCubo; j++){
            for (k = (-radioCubo); k <= radioCubo; k++){
                nuevo.x = posicion.x + i;
                nuevo.y = posicion.y + j;
                nuevo.z = posicion.z + k;
                if((i == 0) && (j == 0) && (k == 0)){
                    casilleroActual = this->tablero->getCasillero(posicion);
                    casilleroActual->desactivarCasilla(efectoAtaqueQuimico);
                    this->casillerosInactivos->add(casilleroActual);
                    
                } else if(abs(i) == 2 || abs(j) == 2 || abs(k) == 2){
                    casilleroActual = this->tablero->getCasillero(posicion);
                    casilleroActual->desactivarCasilla(efectoAtaqueQuimico - 4);
                    this->casillerosInactivos->add(casilleroActual);
                } else if(abs(i) == 1 || abs(j) == 1 || abs(k) == 1){
                    casilleroActual = this->tablero->getCasillero(posicion);
                    casilleroActual->desactivarCasilla(efectoAtaqueQuimico - 2);
                    this->casillerosInactivos->add(casilleroActual);
                }
            }
        }
    }
    if(tablero->validarCoordenadas(posicion)){
    }   
}

void DigiBattle::cartaAvionRadar(Jugador * jugador){
    Ubicacion posicion = pedirUbicacion(AVION);
    int posicionTropaAvion = jugador->getNumSiguienteAvion();
    jugador->agregarTropa(posicion , posicionTropaAvion, AVION);
    this->tablero->getCasillero(posicion);
}

void DigiBattle::cartaBarco(Jugador * jugador){
    Ubicacion posicion = pedirUbicacion(BARCO);
    int posicionTropaBarco = jugador->getNumSiguienteBarco();
    jugador->agregarTropa(posicion , posicionTropaBarco, BARCO);
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
        cout<<"Jugador numero: " << jugador->getNumeroJugador() << endl << endl;
        cout<<"Soldado numero: " << jugador->getNumSiguienteSoldado() << endl;
        Ubicacion posicion = pedirUbicacion(SOLDADO);
        int posicionTropaSoldado = jugador->getNumSiguienteSoldado();
        jugador->agregarTropa(posicion, posicionTropaSoldado, SOLDADO);
    }
}

void DigiBattle::cartaRayoLaser(Jugador * jugador){
    char direccion;
    int tropaElegida;
    int nroJugador;
    int nroTropa;
    Artilleria tipoArtilleriaCasilla;
    Ubicacion posicionActual;
    Lista<InfoTropa*>* tropasDelJugador;
    Casillero * casilleroActual;
    tropasDelJugador = jugador->getListaTropas();
    cout << "Elija el soldado que tirara el rayo laser:" << endl;
    mostrarTropasDisponibles(SOLDADO, tropasDelJugador);
    tropaElegida = pedirNumeroTropa(jugador, SOLDADO);
    posicionActual = jugador->getUbicacionTropa(tropaElegida, SOLDADO);
    casilleroActual = this->tablero->getCasillero(posicionActual);
    cout << "Elija la direccion del rayo:"<< endl;
    cout << "W - arriba" << endl;
    cout << "A - izquierda" << endl;
    cout << "S - abajo" << endl;
    cout << "D - derecha" << endl;
    cin >> direccion;
    while(direccion != 'W' && direccion != 'A' &&
        direccion != 'S' && direccion != 'D'){
        cout << "Elija la direccion del rayo:"<< endl;
        cin >> direccion; 
    }
    if (direccion == 'W'){
        posicionActual.y ++;
        while (posicionActual.y <= this->tablero->getTamanhoTableroY()){
            tipoArtilleriaCasilla = this->tablero->getCasillero(posicionActual)->devolverArtilleria();
            if (tipoArtilleriaCasilla == SOLDADO || tipoArtilleriaCasilla == BARCO){
                nroJugador = this->tablero->getCasillero(posicionActual)->devolverNroJugador();
                nroTropa = this->tablero->getCasillero(posicionActual)->devolverNroTropa();
                sacarTropaJugador(nroJugador, nroTropa, tipoArtilleriaCasilla);
                this->tablero->getCasillero(posicionActual)->desactivarCasilla(5);
                this->casillerosInactivos->add(casilleroActual);

            }
            posicionActual.y ++;
        }
    } else if (direccion == 'A'){
        posicionActual.x --;
        while (posicionActual.x > 0){
            tipoArtilleriaCasilla = this->tablero->getCasillero(posicionActual)->devolverArtilleria();
            if (tipoArtilleriaCasilla == SOLDADO || tipoArtilleriaCasilla == BARCO){
                nroJugador = this->tablero->getCasillero(posicionActual)->devolverNroJugador();
                nroTropa = this->tablero->getCasillero(posicionActual)->devolverNroTropa();
                sacarTropaJugador(nroJugador, nroTropa, tipoArtilleriaCasilla);
                this->tablero->getCasillero(posicionActual)->desactivarCasilla(5);
                this->casillerosInactivos->add(casilleroActual);
            }
            posicionActual.x --;

        }
    } else if (direccion == 'S'){
        posicionActual.y --;
        while (posicionActual.y > 0){
            tipoArtilleriaCasilla = this->tablero->getCasillero(posicionActual)->devolverArtilleria();
            if (tipoArtilleriaCasilla == SOLDADO || tipoArtilleriaCasilla == BARCO){
                nroJugador = this->tablero->getCasillero(posicionActual)->devolverNroJugador();
                nroTropa = this->tablero->getCasillero(posicionActual)->devolverNroTropa();
                sacarTropaJugador(nroJugador, nroTropa, tipoArtilleriaCasilla);
                this->tablero->getCasillero(posicionActual)->desactivarCasilla(5);
                this->casillerosInactivos->add(casilleroActual);
            }
            posicionActual.y --;

        }
    } else if (direccion == 'D'){
        posicionActual.x ++;
        while (posicionActual.x <= this->tablero->getTamanhoTableroX()){
            tipoArtilleriaCasilla = this->tablero->getCasillero(posicionActual)->devolverArtilleria();
            if (tipoArtilleriaCasilla == SOLDADO || tipoArtilleriaCasilla == BARCO){
                nroJugador = this->tablero->getCasillero(posicionActual)->devolverNroJugador();
                nroTropa = this->tablero->getCasillero(posicionActual)->devolverNroTropa();
                sacarTropaJugador(nroJugador, nroTropa, tipoArtilleriaCasilla);
                this->tablero->getCasillero(posicionActual)->desactivarCasilla(5);
                this->casillerosInactivos->add(casilleroActual);
            }
            posicionActual.x ++;

        }
    }
    
    

}

void DigiBattle::anunciarGanador(){
    Jugador* UltimoJugador;
    int posicionUltimoJugador = 1;
    UltimoJugador = this->jugadores->get(posicionUltimoJugador);
    
    cout<<"La sangrienta guerra llego a su fin , dejandonos como ganador al jugador numero "<< UltimoJugador->getNumeroJugador()<<endl;
    cout<<"El jugador superviviente llego a la victoria, junto con sus "<< UltimoJugador->getListaTropas()->contarElementos();
    cout<<" soldados supervivientes"<<endl;
    cout<<" FIN DEL JUEGO "<<endl;
}    
