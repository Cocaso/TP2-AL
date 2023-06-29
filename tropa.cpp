#include "tropa.h"

Tropa::Tropa(Ubicacion ubicacionTropa, int nroTropa, Artilleria tipoTropa){
    this->ubicacion.setUbicacion(ubicacionTropa);
    this->nroDeTropa = nroTropa;
    this->tipoDeTropa = tipoTropa;
    if (tipoTropa == BARCO){
        this->vidasBarco = 3;
    } else{
        this->vidasBarco = 0;
    };
}

Tropa::~Tropa(){
}

Artilleria Tropa::getTipoTropa(){
    return this->tipoDeTropa;
}

int Tropa::getNroTropa(){
    return this->nroDeTropa;
}

Ubicacion Tropa::getUbicacion(){
    return this->ubicacion;
}

int Tropa::getVidasBarco(){
    return this->vidasBarco;
}

void Tropa::setTipoTropa(Artilleria tipoTropa){
    this->tipoDeTropa = tipoTropa;
}

void Tropa::setNroTropa(int nroTropa){
    this->nroDeTropa = nroTropa;
}

void Tropa::setUbicacion(Ubicacion ubicacionNueva){
    this->ubicacion.setUbicacion(ubicacionNueva);
}

void Tropa::bajarVidasBarco(){
    this->vidasBarco --;
}

