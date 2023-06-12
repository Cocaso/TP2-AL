#include "tablero.h"


Tablero::Tablero(){
    this->tablero = NULL;
    this->maxX = 0;
    this->maxY = 0;
    this->maxZ = 0;    
}

Tablero::Tablero(Ubicacion maxSize) {
    this->tablero = new(Lista<Lista<Lista<Casillero*>*>*>);
    this->maxX = maxSize.x;
    this->maxY = maxSize.y;
    this->maxZ = maxSize.z;

}

Tablero::~Tablero() {
    delete this->tablero;

}

void Tablero::crearTerreno(){
    unsigned int x ,y ,z;
    unsigned int indiceUno, indiceDos;
    Casillero* casillero;
    Lista<Casillero*>* listaX ;
    Lista<Lista<Casillero*>*>* listaY;
    
    
    //Primero se llena la capa inferior con el diseño del mapa
    listaY = new(Lista<Lista<Casillero*>*>);

    for (y = 0; y < this->maxY ; y++){
        listaX = new(Lista<Casillero*>);

        indiceDos = y%20;       // da el resto (0-19) uwu
        for (x = 0; x < this->maxX; x++){
            casillero = new(Casillero);
            
            indiceUno = x%20;   // da el resto (0-19) uwu
            casillero->cambiarTerreno(mapaTemplate[indiceUno][indiceDos]); 
            listaX->add(casillero);

            delete casillero;
        }
    } 
    listaY->add(listaX);

    delete listaX;
            
    this->tablero->add(listaY);
    //---------------------------------------------------------

    //Se llenauna listaX con aire, una listaY con copias de listaX, 
    //y el resto del tablero con copias de listaY
    casillero = new(Casillero); 
    listaX = new(Lista<Casillero*>);
    for (x = 0; x < this->maxX ; x++){
        listaX->add(casillero);
    }
    listaY = new(Lista<Lista<Casillero*>*>);
    for (y = 0; y < this->maxY ; y++){
        listaY->add(listaX);
    }
    for (z = 1; z < this->maxZ; z++){
        this->tablero->add(listaY);
    }
    //---------------------------------------------------------
}

void Tablero::mostrarTablero(){
    //usar bmp aaaaaaaaaaaaaa
}

Casillero* Tablero::getCasillero(Ubicacion posicion){
    Lista<Lista<Casillero*>*>* listaY;
    Lista<Casillero*>* listaX;

    listaY = this->tablero->get(posicion.z);
    listaX = listaY->get(posicion.y);
    return listaX->get(posicion.x);
}
   
bool Tablero::validarCoordenadas(Ubicacion posicion){
    if((this->maxX > posicion.x && 
        this->maxY > posicion.y && 
        this->maxZ > posicion.z) 
        && 
        (0 < posicion.x && 
        0 < posicion.y && 
        0 < posicion.z )){
        return true;
    }
    return false;
}

//ignorar jeje
/*
for (x = 0; x < this->maxX ; x++){
        listaY = new(Lista<Lista<Casillero*>*>);
        if (x == 0){
           for (y = 0; y < this->maxY ; y++){
            listaZ = new(Lista<Casillero*>);

            indiceDos = y%20;       // da el resto (0-19) uwu
            for (z = 0; z < this->maxZ ; z++){
                casillero = new(Casillero);
                
                indiceUno = z%20;   // da el resto (0-19) uwu
                if (x == 0 ){
                    casillero->cambiarTerreno(mapaTemplate[indiceUno][indiceDos]); 
                }
                listaZ->add(casillero);
                delete casillero;
            } 
            listaY->add(listaZ);

            delete listaZ;
            
        }
        this->tablero->add(listaY);
*/