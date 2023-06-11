#include "tablero.h"


Tablero::Tablero(){
    this->tablero = NULL;
    this->maxX = 0;
    this->maxY = 0;
    this->maxZ = 0;    
}

Tablero::Tablero(unsigned int x, unsigned int y, unsigned int z) {
    this->tablero = new(Lista<Lista<Lista<Casillero*>*>*>);
    this->maxX = x;
    this->maxY = y;
    this->maxZ = z;

}

void Tablero::crearTerreno(){
    unsigned int x ,y ,z;
    unsigned int indiceUno, indiceDos;
    Casillero* casillero ;
    Lista<Casillero*>* listaZ ;
    Lista<Lista<Casillero*>*>* listaY ;
    
    
    //Primero se llena la capa inferior con el diseño del mapa
    listaY = new(Lista<Lista<Casillero*>*>);

    for (y = 0; y < this->maxY ; y++){
        listaZ = new(Lista<Casillero*>);

        indiceDos = y%20;       // da el resto (0-19) uwu
        for (z = 0; z < this->maxZ ; z++){
            casillero = new(Casillero);
            
            indiceUno = z%20;   // da el resto (0-19) uwu
            casillero->cambiarTerreno(mapaTemplate[indiceUno][indiceDos]); 
            listaZ->add(casillero);

            delete casillero;
        }
    } 
    listaY->add(listaZ);

    delete listaZ;
            
    this->tablero->add(listaY);
    //---------------------------------------------------------

    //Se llenauna listaZ con aire, una listaY con copias de listaZ, 
    //y el resto del tablero con copias de listaY
    casillero = new(Casillero);
    listaZ = new(Lista<Casillero*>);
    for (z = 0; z < this->maxZ ; z++){
        listaZ->add(casillero);
    }
    listaY = new(Lista<Lista<Casillero*>*>);
    for (y = 0; y < this->maxY ; y++){
        listaY->add(listaZ);
    }
    for (x = 1; x < this->maxX; x++){
        this->tablero->add(listaY);
    }
    //---------------------------------------------------------
}

void Tablero::mostrarTablero(){
    //usar bmp aaaaaaaaaaaaaa
}

Casillero* Tablero::getCasillero(unsigned int x, unsigned int y, unsigned int z){
    Lista<Lista<Casillero*>*>* listaY;
    Lista<Casillero*>* listaZ;

    if (validarCoordenadas(x, y, z)){
        listaY = this->tablero->get(x);
        listaZ = listaY->get(y);
        return listaZ->get(z);
    } else {
        throw "Casillero fuera de límites";
    }
}

Tablero::~Tablero() {
    

}
                //revisar donde se usó esto lmao
bool Tablero::validarCoordenadas(unsigned int x, unsigned int y, unsigned int z){
    if((this->maxX > x && this->maxY > y && this->maxZ > z) 
        && (0 < x && 0 < y && 0 < z )){
        return true;
    }
    //throw("Coodenadas fuera de rango ");
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