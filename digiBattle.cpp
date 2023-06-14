#include "digiBattle.h"
using namespace std;


DigiBattle::DigiBattle(){
    this->tableroArchivo = fopen("tablero4k.bmp", "w");
    this->tablero = new(Tablero);
    this->jugadores = new(Lista<Jugador*>) ;
    this->casillerosInactivos = new(Lista<Casillero*>);
}

DigiBattle::~DigiBattle(){
    delete tablero;
    delete jugadores;
    delete casillerosInactivos;
}

void DigiBattle::iniciarJuego(){

    Ubicacion tableroSize;
    Ubicacion posicionSoldado;
    int cantidadJugadores;
    int cantidadSoldados;
    int nroSoldado;


    cout << "Ingrese el tamaño del mapa (min 10x10x3): " << endl;
    cin >> tableroSize.x;
    cin >> tableroSize.y;       //Revisar esto que esta mal
    cin >> tableroSize.z;       //Hay que aclarar la disposicion de las coordenadas al usuario

    cout << "Ingrese cantidad de jugadores: " << endl;
    cin >> cantidadJugadores;

    cout <<"Ingrese la cantidad de tropas por jugador: "<< endl;
    cin >> cantidadSoldados;
    
    this->tablero = new Tablero(tableroSize); //crear tablero

    int nroJugador;
    for (int j = 0 ; j < cantidadJugadores; j++){ //crear jugadores y colocar tropas

        //Crea el jugador
        nroJugador = j;
        Jugador* nuevoJugador = new Jugador(nroJugador, cantidadSoldados);
        
        //Lo deja poner sus tropas
        for (int i = 1 ; i <= cantidadSoldados; i++){
            posicionSoldado = this->pedirUbicacion(SOLDADO);
            nroSoldado = i;
            nuevoJugador->agregarTropa(posicionSoldado, nroSoldado, SOLDADO);  //agrego soldado
            this->ponerSoldado(posicionSoldado,nroJugador,nroSoldado);  //pone el soldado en el tablero
        }
        
        this->jugadores->add(nuevoJugador);
        delete nuevoJugador;
    }
}

void DigiBattle::turno(){
    Jugador* jugadorActual;
    string opcion;
    
    jugadores->reiniciarCursor();
    while(!comprobarVictoria()){
        //Determina a quien le toca jugar
        if (!jugadores->avanzarCursor()){
            jugadores->reiniciarCursor();
        }
        jugadorActual = this->jugadores->getCursor();
        
        //Le da una carta al jugador
        this->obtenerCarta(jugadorActual);

        //Poner mina (y disparar con el barco??)
        ponerMina(jugadorActual->getNumeroJugador());
        dispararBarco();
        //Vemos si quiere mover alguna tropa
        do {
           cout<<"Quiere realizar un movimiento de alguna tropa ? S/N "<<endl;
           cin>>opcion;
        }while(opcion != "S" || opcion != "N");
        
        if (opcion == "S"){
            moverTropa();
        }

        do { //Elige si usa una carta o no y cuál
           cout<<"Quiere invocar alguna de sus cartas ? S/N "<<endl;
           cin>>opcion;
        }while(opcion != "S" || opcion != "N");
        
        if (opcion == "S"){
            usarCarta( jugadorActual);
        }

        //Reducir cuenta de los casilleros inactivos
        reducirCasilleroInactivo();
    }
    anunciarGanador(); //termino el juego
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
        this->sacarTropaJugador(nroJugadorEnemigo, nroSoldadoEnemigo, SOLDADO);
        this->sacarTropaJugador(nroJugador, nroSoldado, SOLDADO);
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
    
    this->resolverColision(casillero, tipoArtilleria, jugador);
    // falta ver donde implementamos el poder de la mina

}

void DigiBattle::dispararBarco(){
    Casillero * casilleroDisparado;
    Ubicacion ubicacionDisparo = pedirUbicacion();
    casilleroDisparado = this->tablero->getCasillero(ubicacionDisparo);
    

}

void DigiBattle::moverTropa(){
    Ubicacion ubiTropa, ubiNueva;
    Casillero* casillero;
    Artilleria sinArtilleria = VACIO;
    
    Jugador* jugador = this->jugadores->getCursor();
    int nroTropaElegida;
 
    Lista<InfoTropa*>* tropasDelJugador;
    int tipoTropa;
    Artilleria seleccionTropa = VACIO;
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

    //Mostrar las tropas disponibles a usar y elegir la tropa a mover
    mostrarTropasDisponibles(seleccionTropa, tropasDelJugador);
    nroTropaElegida = pedirTropaAElegir(jugador, seleccionTropa);
    ubiTropa = jugador->getPosicionTropa(nroTropaElegida, seleccionTropa);

    //Pedir ubicacion y mover a la tropa
    ubiNueva = this->pedirUbicacion(seleccionTropa);
    

    bool soldadoVivo = true;
    int diferenciaX = ubiNueva.x - ubiTropa.x;
    int diferenciaY = ubiNueva.y - ubiTropa.y;
    int cant;
    if(diferenciaX != 0){
        cant = abs(diferenciaX);
    } else {
        cant = abs(diferenciaY);
    }

    if (validarMovimiento(ubiTropa, ubiNueva) && seleccionTropa != AVION){
        while (soldadoVivo && (cant > 0)) {   //cant == caantidad de casilleros
            Ubicacion ubiActual = ubiTropa;
            int dirX, dirY;
            if(diferenciaX > 0){ // determinar direccion
                dirX = 1;
            } else if(diferenciaX < 0){
                dirX = -1;
            } else {
                dirX = 0;
            }

            if(diferenciaY > 0){
                dirY = 1;
            } else if(diferenciaY < 0){
                dirY = -1;
            } else {
                dirY = 0;
            }

            switch (dirX){
            case 0:
                switch (dirY){
                case 1: 
                    //Mover hacia arriba
                    ubiActual.y++;
                    soldadoVivo = resolverColision(tablero->getCasillero(ubiActual), tablero->getCasillero(ubiTropa));
                    break;
                case -1:
                    //Mover hacia abajo
                    ubiActual.y--;
                    soldadoVivo = resolverColision(tablero->getCasillero(ubiActual), tablero->getCasillero(ubiTropa));
                    break;
                }
                break;

            case 1:
                switch (dirY){
                case 0: 
                    //Mover hacia derecha
                    ubiActual.x++;
                    soldadoVivo = resolverColision(tablero->getCasillero(ubiActual), tablero->getCasillero(ubiTropa));
                    break;
                case 1:
                    //Mover hacia arriba derecha
                    ubiActual.y++;
                    ubiActual.x++;
                    soldadoVivo = resolverColision(tablero->getCasillero(ubiActual), tablero->getCasillero(ubiTropa));
                    break;
                case -1:
                    //Mover hacia abajo derecha
                    ubiActual.y--;
                    ubiActual.x++;
                    soldadoVivo = resolverColision(tablero->getCasillero(ubiActual), tablero->getCasillero(ubiTropa));
                    break;
                }
                break;

            case -1: 
                switch (dirY){
                case 0: 
                    //Mover hacia izquierda
                    ubiActual.x--;
                    soldadoVivo = resolverColision(tablero->getCasillero(ubiActual), tablero->getCasillero(ubiTropa));
                    break;
                case 1:
                    //Mover hacia arriba izquierda
                    ubiActual.y++;
                    ubiActual.x--;
                    soldadoVivo = resolverColision(tablero->getCasillero(ubiActual), tablero->getCasillero(ubiTropa));
                    break;
                case -1:
                    //Mover hacia abajo izquierda
                    ubiActual.y--;
                    ubiActual.x--;
                    soldadoVivo = resolverColision(tablero->getCasillero(ubiActual), tablero->getCasillero(ubiTropa));
                    break;
                }
                break;

            }
            //controla que no se mueva más de la cuenta
            cant--;
        }
    } else if (seleccionTropa != AVION) {
        
    }
    
    //
    /*
    //Falta revisar esto de aca 
    //Vacio la casilla vieja
    casillero = this->tablero->getCasillero(ubiTropa);
    casillero->ponerArtilleria(sinArtilleria, 0);//pone artilleria en casillero

    casillero = this->tablero->getCasillero(ubiNueva);//
    this->resolverColision(casillero,  seleccionTropa,  nroJugador,  nroTropaElegida);
    */
}

int DigiBattle::pedirTropaAElegir(Jugador * jugador, Artilleria seleccionTropa){
    int nroTropaElegida;
    do{
        cout << "Elija el N° de tropa a mover" << endl;
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

            cout << "Tropa N°: " << tropasDelJugador->getCursor()->nroTropa;
            cout << " // Posicion X: " << posicion.x;
            cout << " Y: " << posicion.y << endl;
            //Soldado No 1 // Posicion X:7 Y:4
        }
    }
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
    if(!casillero->comprobarEstado()){
        cout<<"casillero seleccionado momentaneamente inactivo"<< endl;
        return false;  //valido que no sea casillero aire
    }

    return true;
}

//falta validar que no se mueva hacia el mismo casillero en el que está xd
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
    jugador->addCarta();
}

void DigiBattle::usarCarta(Jugador* jugador){
    jugador->nombrarCartas();
    int numeroCarta;

    do{
        cout<<"Ingrese el numero de carta que desea usar "<<endl;
        cin>>numeroCarta;
    }while(numeroCarta > jugador->cantidadCartas());

    tipos tipo = jugador->getCarta(numeroCarta);
   
    switch(tipo){
    case ATAQUEQUIMICO:
        cartaAtaqueQuimico(this->pedirUbicacion(VACIO));
        break;
    case AVIONRADAR:
        cartaAvionRadar(this->pedirUbicacion(AVION), this->buscarJugador(jugador->getNumeroJugador()));
        break;
    case INVOCARBARCO:
        cartaBarco(this->pedirUbicacion(BARCO), this->buscarJugador(jugador->getNumeroJugador()));
        break;
    case POTOFGREED:
        cartaPotOfGreed(this->buscarJugador(jugador->getNumeroJugador()));
        break;
    case SOLDADOEXTRA:
        cartaAgregarSoldado(this->buscarJugador(jugador->getNumeroJugador()));
        break;
    case RAYOLASER:
        cartaRayoLaser(this->buscarJugador(jugador->getNumeroJugador()));
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
    while(this->jugadores->avanzarCursor() && jugadorBuscado == NULL){
        if (this->jugadores->getCursor()->getNumeroJugador() == nroJugador){
            jugadorBuscado = this->jugadores->getCursor();
        }
    }
    
    jugadores->reiniciarCursor();
    while(this->jugadores->avanzarCursor() && posicionAntiguaEncontrada == false){
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

bool DigiBattle::resolverColision(Casillero* casilleroAnterior, Casillero* casilleroNuevo, Ubicacion posicionNueva){
    int turnosDesactivar = poderMina();

    if (casillero->devolverArtilleria() == VACIO){
        //coloca el soldado en el casillero
        casillero->ponerArtilleria(artilleria, nroJugador);
        //actualiza la lista del jugador
        jugadores->getCursor()
        
    } else if(casillero->devolverArtilleria() == SOLDADO && artilleria == SOLDADO){
        sacarTropaJugador(nroJugador, nroSoldado, SOLDADO);
        int jugadorEnemigo = casillero->devolverNroJugador(); // con este numero jugador habria que sacarle soldado al jugador
        int nroSoldadoEnemigo = casillero->devolverNroSoldado();
        sacarTropaJugador(jugadorEnemigo, nroSoldadoEnemigo, SOLDADO);
        casillero->ponerArtilleria(VACIO);

    } else if (casillero->devolverArtilleria() == MINA){
        casillero->desactivarCasilla(turnosDesactivar);
        this->casillerosInactivos->add(casillero);
        sacarTropaJugador(nroJugador,nroSoldado, SOLDADO);
        casillero->ponerArtilleria(VACIO);
    }
}

//Usar el casillero anterior de la tropa para sacar los ultimos 3 parametros
//Esto tambien eliminaria la necesidad del overload para el soldado en especifico
/*bool DigiBattle::resolverColision(Casillero* casillero, Artilleria artilleria, int nroJugador){
   int inactivo = poderMina();
   if (casillero->devolverArtilleria() == VACIO) {
        casillero->ponerArtilleria(artilleria, nroJugador);
    
   } else if (casillero->devolverArtilleria() == SOLDADO){
        if (artilleria == MINA){
            casillero->desactivarCasilla(inactivo);
            this->casillerosInactivos->add(casillero);
        }

        int jugadorEnemigo = casillero->devolverNroJugador(); // con este numero jugador habria que sacarle soldado al jugador
        int nroSoldadoEnemigo = casillero->devolverNroSoldado();
        sacarTropaJugador(jugadorEnemigo, nroSoldadoEnemigo, SOLDADO);
        casillero->ponerArtilleria(VACIO);
   }

   /*

    //casos solo para poner mina barco
     
    
    
    switch(casillero->devolverArtilleria()){
    case VACIO:
    
        
        break;
        
    case SOLDADO:
        
        break;
        
    case MINA:
        casillero->desactivarCasilla(inactivo);
        this->casillerosInactivos->add(casillero);
        casillero->ponerArtilleria(VACIO);
        break;

    }
    
}
*/

bool DigiBattle::comprobarVictoria(int nroJugador){ 
    //vemos si quedo solo un jugador
    return (this->jugadores->contarElementos() == 1);   
}

void DigiBattle::sacarTropaJugador(int nroJugador, int nroTropa, Artilleria artilleria){
    Jugador* jugador = this->buscarJugador(nroJugador);

    //comprueba si efectivamente el jugador perdio todos sus tropas/vidas
    if (jugador->removerTropa(nroTropa, artilleria) == 0){
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
    int posicion = 1;
    casillerosInactivos->reiniciarCursor();

    while(casillerosInactivos->avanzarCursor()){
        casillero = casillerosInactivos->getCursor();
        if (casillero->disminuirTurnosInactivo()){
            casillerosInactivos->remover(posicion);
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

    for(i = (-radioCubo); i <= radioCubo; i++){
        for (j = (-radioCubo); j <= radioCubo; j++){
            for (k = (-radioCubo); k <= radioCubo; k++){
                nuevo.x = posicion.x + i;
                nuevo.y = posicion.y + j;
                nuevo.z = posicion.z + k;
                if((i == 0) && (j == 0) && (k == 0)){
                    this->tablero->getCasillero(posicion)->desactivarCasilla(efectoAtaqueQuimico);
                } else if(abs(i) == 2 || abs(j) == 2 || abs(k) == 2){
                    this->tablero->getCasillero(nuevo)->desactivarCasilla(efectoAtaqueQuimico - 4);
                } else if(abs(i) == 1 || abs(j) == 1 || abs(k) == 1){
                    this->tablero->getCasillero(nuevo)->desactivarCasilla(efectoAtaqueQuimico - 2);
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
}

void DigiBattle::cartaBarco(Jugador * jugador){
    Ubicacion posicion = pedirUbicacion(BARCO);
    int posicionTropaBarco = jugador->getNumSiguienteBarco();
    jugador->agregarTropa(posicion , posicionTropaBarco, BARCO);
}

void DigiBattle::cartaPotOfGreed(Jugador * jugador){
    int i;
    for (i = 1; i <= 2; i++){
        this->obtenerCarta(jugador)
    }
}

void DigiBattle::cartaAgregarSoldados(Jugador * jugador){
    int i;
    for (i = 1; i <= 2; i++){
        Ubicacion posicion = pedirUbicacion(SOLDADO);
        int posicionTropaSoldado = jugador->getNumSiguienteSoldado();
        jugador->agregarTropa(posicion , posicionTropaSoldado, SOLDADO);
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
    tropaElegida = pedirTropaAElegir(jugador, SOLDADO);
    posicionActual = jugador->getPosicionTropa(tropaElegida, SOLDADO);
    cout << "Elija la direccion del rayo:"<< endl;
    cout << "W - arriba" << endl;
    cout << "A - izquierda" << endl;
    cout << "S - abajo" << endl;
    cout << "D - derecha" << endl;
    cin >> direccion;
    while(direccion != 'W' || direccion != 'A' ||
        direccion != 'S' || direccion != 'D'){
        cout << "Elija la direccion del rayo:"<< endl;
        cin >> direccion; 
    }
    if (direccion == 'W'){
        posicionActual.y ++;
        while (posicionActual.y <= this->tablero->getTamañoTableroY()){
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
        while (posicionActual.x <= this->tablero->getTamañoTableroX()){
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

void DigiBattle::archivo(){
    this->tableroArchivo = fopen();
}