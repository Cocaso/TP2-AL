#ifndef DIGIBATTLE_H_
#define DIGIBATTLE_H_

#include <iostream>

class DigiBattle {
private:
    FILE* tableroArchivo;   //Archivo txt del tablero
    int tablero[20][20];    //convertir a array dinamico
    
public:
    DigiBattle();   
    ~DigiBattle();
};
#endif