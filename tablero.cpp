#include "tablero.h"


Tablero::Tablero(){
    this->tablero = NULL;
    this->maxX = 0;
    this->maxY = 0;
    this->maxZ = 0;    
}

Tablero::Tablero(Ubicacion maxSize) {
    this->tablero = new(Lista<Lista<Lista<Casillero*>*>*>);
    this->maxX = maxSize.getX();
    this->maxY = maxSize.getY();
    this->maxZ = maxSize.getZ();
}

Tablero::~Tablero() {
    Lista<Lista<Casillero*>*>* x;
    Lista<Casillero*>* y;
    
    this->tablero->reiniciarCursor();
    while(this->tablero->avanzarCursor()){ //listaDeListasDelistas
        x = this->tablero->getCursor();
        x->reiniciarCursor(); //listaDeListas
        while(x->avanzarCursor()){
            y = x->getCursor();
            y->reiniciarCursor(); //listas
            while(y->avanzarCursor()){
                y->getCursor()->~Casillero();
                delete y->getCursor();
            }
        }
    }
    delete(this->tablero);
}

void Tablero::crearTerreno(){
    int x ,y ,z;
    int indiceUno, indiceDos;
    Casillero* casillero;
    Lista<Casillero*>* listaX ;
    Lista<Lista<Casillero*>*>* listaY;
    
    
    //Primero se llena la capa inferior con el diseño del mapa
    for (z = 0; z < 5; z++){

        listaY = new(Lista<Lista<Casillero*>*>);
        
        for (y = 0; y < this->maxY ; y++){
            listaX = new(Lista<Casillero*>);

            indiceDos = (y%20);       // da el resto (0-19) uwu 
            for (x = 0; x < this->maxX; x++){
                casillero = new(Casillero);
                
                indiceUno = (x%20);   // da el resto (0-19) uwu
                casillero->cambiarTerreno(mapaTemplate[indiceUno][indiceDos]);
                listaX->add(casillero);
            }
            listaY->add(listaX);
        }
        this->tablero->add(listaY);
    }
    for(z = 5; z < this->maxZ; z++){
        listaY = new(Lista<Lista<Casillero*>*>);
        for (y = 0; y < this->maxY ; y++){
            listaX = new(Lista<Casillero*>);
            for (x = 0; x < this->maxX; x++){
                casillero = new(Casillero);
                listaX->add(casillero);
            }
            listaY->add(listaX);
        }
        this->tablero->add(listaY);
    }
}

int distanciaEuclidea(int x1, int y1, int x2, int y2) {
    return round(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void Tablero::mostrarTablero(int nroJugador){

    // Tomamos los bitmaps creados
    bitmap_image gas("Casilleros/gas.bmp");
    bitmap_image tierra("Casilleros/tierra.bmp");
    bitmap_image tierraInactiva("Casilleros/tierra_inactiva.bmp");
    bitmap_image agua("Casilleros/agua.bmp");
    bitmap_image aguaInactiva("Casilleros/muC.bmp");
    bitmap_image soldado("Casilleros/soldado.bmp");
    bitmap_image soldadoNadando("Casilleros/nadando.bmp");
    bitmap_image mina("Casilleros/mina.bmp");
    bitmap_image minaAgua("Casilleros/mina_agua.bmp");
    bitmap_image barco("Casilleros/barco.bmp");
    bitmap_image avionTierra("Casilleros/avion_tierra.bmp");
    bitmap_image avionAgua("Casilleros/avion_agua.bmp");
    bitmap_image bmpTablero(static_cast<unsigned>(maxX*32), static_cast<unsigned>(maxY*32));
    bitmap_image* casilleroADibujar;

    Lista<Lista<Lista<Casillero*>*>*>* listaZ = this->tablero;
    Lista<Lista<Casillero*>*>*listaY;
    Lista<Casillero*>* listaX;
    Lista<Ubicacion>* ubicacionAviones;
    ubicacionAviones = new Lista<Ubicacion>;
    Ubicacion ubicacionActual;
    ubicacionActual.setZ(5);
    ubicacionActual.setY(0);
    ubicacionActual.setX(0);

    //Guardamos las ubicaciones de todos los aviones
    listaZ->reiniciarCursor();
    listaZ->avanzarCursor(5);
    while(listaZ->avanzarCursor()){
        ubicacionActual.setZ(ubicacionActual.getZ() + 1);
        listaY = listaZ->getCursor();
        listaY->reiniciarCursor();
        while(listaY->avanzarCursor()){
            ubicacionActual.setY(ubicacionActual.getY() + 1);
            listaX = listaY->getCursor();
            listaX->reiniciarCursor();
            while(listaX->avanzarCursor()){
                ubicacionActual.setX(ubicacionActual.getX() + 1);
                if(listaX->getCursor()->devolverArtilleria() == AVION){
                    ubicacionAviones->add(ubicacionActual);
                }
            } ubicacionActual.setX(0);
        } ubicacionActual.setY(0);
    }

    this->tablero->reiniciarCursor();
    this->tablero->avanzarCursor(5);

    listaY = this->tablero->getCursor();
    Casillero* casilleroActual;
    unsigned char r, g, b;
    int x, y, i = 0, j = 0;

    listaY->reiniciarCursor();
    while(listaY->avanzarCursor()){
        listaX = listaY->getCursor();
        listaX->reiniciarCursor();
        j = 0;
        while (listaX->avanzarCursor()){
            casilleroActual = listaX->getCursor();
            bool esDelJugador = casilleroActual->devolverNroJugador() == nroJugador;
            bool tieneAvion = false;
            if(!ubicacionAviones->vacia()){
                ubicacionAviones->reiniciarCursor();
                while(ubicacionAviones->avanzarCursor()){
                    double distancia = distanciaEuclidea(j + 1, i + 1, ubicacionAviones->getCursor().getX(), ubicacionAviones->getCursor().getY());
                    if(distancia == 0){
                        tieneAvion = true;
                    } else if (distancia < 3 && this->getCasillero(ubicacionAviones->getCursor())->devolverNroJugador() == nroJugador){
                        esDelJugador = true;
                    }
                }
            }
            
            //Elige qué casillero dibujar
            if(!casilleroActual->esToxico() && !tieneAvion){
                if (casilleroActual->devolverTerreno() == TIERRA){
                    switch (casilleroActual->devolverArtilleria()) {
                    case VACIO:
                        if(casilleroActual->devolverTurnosInactivos() > 0){
                            casilleroADibujar = &tierraInactiva;
                            break;
                        } else {
                            casilleroADibujar = &tierra;
                            break;
                        }
                    case SOLDADO:
                        if(esDelJugador){
                            casilleroADibujar = &soldado;
                            break;
                        } else {
                            casilleroADibujar = &tierra;
                            break;
                        }
                    case MINA:
                        if(esDelJugador){
                            casilleroADibujar = &mina;
                            break;
                        } else {
                            casilleroADibujar = &tierra;
                            break;
                        }
                    default:
                        casilleroADibujar = &tierra;
                        break;
                    }

                } else if (casilleroActual->devolverTerreno() == AGUA){
                    switch (casilleroActual->devolverArtilleria()) {
                    case VACIO:
                        if(casilleroActual->devolverTurnosInactivos() > 0){
                            casilleroADibujar = &aguaInactiva;
                            break;
                        } else {
                            casilleroADibujar = &agua;
                            break;
                        }
                    case SOLDADO:
                        if(esDelJugador){
                            casilleroADibujar = &soldadoNadando;
                            break;
                        } else {
                            casilleroADibujar = &agua;
                            break;
                        }
                    case MINA:
                        if(esDelJugador){
                            casilleroADibujar = &minaAgua;
                            break;
                        } else {
                            casilleroADibujar = &agua;
                            break;
                        }
                    case BARCO:
                        casilleroADibujar = &barco;
                        break;
                    default:
                        casilleroADibujar = &agua;
                        break;
                    }
                }
            } else if(!tieneAvion) {
                casilleroADibujar = &gas;
            } else {
                if (casilleroActual->devolverTerreno() == AGUA){
                    casilleroADibujar = &avionAgua;
                } else {
                    casilleroADibujar = &avionTierra;
                }
            }

            //Dibujar el casillero
            for (x = 0; x < 32; x++) {
                for (y = 0; y < 32; y++) {
                    (*casilleroADibujar).get_pixel(x, y, r, g, b);
                    bmpTablero.set_pixel(i*32 + x, j*32 + y, r, g, b);
                }
            }
            j++;    //Variable de posicion del tablero
        }
        i++;        //Variable de posicion del tablero
    }

    bmpTablero.save_image("tablero.bmp");
    delete ubicacionAviones;

}

Casillero * Tablero::getCasillero(Ubicacion posicion){
    // Revisar listaX y listaY estan inversas
    Lista<Lista<Casillero*>*>* listaY;
    Lista<Casillero*>* listaX;

    listaY = this->tablero->get(posicion.getZ());
    listaX = listaY->get(posicion.getX());   // cambiado y
    return listaX->get(posicion.getY());     //cambiado x t
}
   
bool Tablero::validarCoordenadas(Ubicacion posicion){
    if((posicion.getX() <= this->maxX && 
        posicion.getY() <= this->maxY && 
        posicion.getZ() <= this->maxZ ) 
        && 
        (posicion.getX() > 0 && 
        posicion.getY() > 0 && 
        posicion.getZ() > 0 )){
        return true;
    }
    return false;
}

int Tablero::getTamanhoTableroX(){
    return this->maxX;
}

int Tablero::getTamanhoTableroY(){
    return this->maxY;
}

int Tablero::getTamanhoTableroZ(){
    return this->maxZ;
}