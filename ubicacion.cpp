#include "ubicacion.h"

Ubicacion::Ubicacion(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Ubicacion::Ubicacion(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
}

int Ubicacion::getX(){
    return this->x;
}

int Ubicacion::getY(){
    return this->y;
}

int Ubicacion::getZ(){
    return this->z;
}

void Ubicacion::setX(int x){
    this->x = x;
}

void Ubicacion::setY(int y){
    this->y = y;
}

void Ubicacion::setZ(int z){
    this->z = z;
}

void Ubicacion::setUbicacion(int x, int y, int z){
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}


void Ubicacion::setUbicacion(Ubicacion ubicacionNueva){
    this->x = ubicacionNueva.getX();
    this->y = ubicacionNueva.getY();
    this->z = ubicacionNueva.getZ();
}