#include <tablero.h>


Tablero::Tablero(){
    this->tablero = NULL;
    this->maxX = 0;
    this->maxY = 0;
    this->maxZ = 0;    
}

Tablero::Tablero(int x, int y, int z) {
    this->tablero = new(Lista<Lista<Lista<Casillero*>*>*>);
    this->maxX = x;
    this->maxY = y;
    this->maxZ = z;

}

void Tablero::crearTerreno(){
    int x ,y ,z;
    int indiceUno, indiceDos;
    Casillero* casillero = new(Casillero);
    Lista<Lista<Casillero*>*>* listaY = new(Lista<Lista<Casillero*>*>);
    Lista<Casillero*>* listaZ = new(Lista<Casillero*>);
    

    //falta hacer que no dibje el terreno donde va el aire
    for (x = 0; x < this->maxX ; x++){
        for (y = 0; y < this->maxY ; y++){
            indiceDos = y%20;       // da el resto (0-19) uwu
            for (z = 0; z < this->maxZ ; z++){
                indiceUno = z%20;   // da el resto (0-19) uwu
                casillero->cambiarTerreno(mapaTemplate[indiceUno][indiceDos]);
                listaZ->add(casillero);
            } 
            listaY->add(listaZ);
            //falta llamar al destructor de la listaZ para vaciarla
        }
        this->tablero->add(listaY);
        //tambien el destructor de la listaY acá
    }
    
    delete casillero;
    delete listaY;
    delete listaZ;
}

void Tablero::mostrarTablero(){
    //usar bmp aaaaaaaaaaaaaa
}

Tablero::~Tablero() {
    




}