#include <digiBattle.h>


DigiBattle::DigiBattle(){
    this->tableroArchivo = fopen("tablero4k.bmp", "w");
    this->tablero;
    this->jugadores = NULL;
    this->casillerosInactivos = NULL;
}