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
    int x ,y ,z;
    int indiceUno, indiceDos;
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
    bitmap_image tierra("Casillero/tierra.bmp");
    bitmap_image agua("Casillero/agua.bmp");
    bitmap_image soldado("Casillero/soldado.bmp");
    bitmap_image soldadoNadando("Casillero/nadando.bmp");
    bitmap_image mina("Casillero/mina.bmp");
    bitmap_image minaAgua("Casillero/mina_agua.bmp");
    bitmap_image barco("Casillero/barco.bmp");
    bitmap_image avion("Casillero/avion.bmp");
    bitmap_image bmpTablero(maxY*32, maxX*32);
    bitmap_image* casilleroADibujar;



    this->tablero->reiniciarCursor();
    this->tablero->avanzarCursor();

    Lista<Lista<Casillero*>*>*listaY = this->tablero->getCursor();
    Lista<Casillero*>* listaX;
    Casillero* casilleroActual;
    unsigned char r, g, b;
    int y, x, i = 0, j = 0;

    listaY->reiniciarCursor();
    while(listaY->avanzarCursor()){
        listaX = listaY->getCursor();
        listaX->reiniciarCursor();
        while (listaX->avanzarCursor()){
            casilleroActual = listaX->getCursor();

            //Elige qué casillero dibujar
            if (casilleroActual->devolverTerreno() = TIERRA){
                switch (casilleroActual->devolverArtilleria()) {
                case VACIO:
                    casilleroADibujar = &tierra;
                    break;
                case SOLDADO:
                    casilleroADibujar = &soldado;
                    break;
                case MINA:
                    casilleroADibujar = &mina;
                    break;
                default:
                    break;
                }
            } else if (casilleroActual->devolverTerreno() = AGUA){
                switch (casilleroActual->devolverArtilleria()) {
                case VACIO:
                    casilleroADibujar = &agua;
                    break;
                case SOLDADO:
                    casilleroADibujar = &soldadoNadando;
                    break;
                case MINA:
                    casilleroADibujar = &minaAgua;
                    break;
                case BARCO:
                    casilleroADibujar = &barco;
                default:
                    break;
                }
            }

            //Dibujar el casillero
            for (x = 0; x < 32; x++) {
                for (y = 0; y < 32; y++) {
                    (*casilleroADibujar).get_pixel(x, y, r, g, b);
                    Board.set_pixel(i*32 + x, j*32 + y, r, g, b);
                }
            }
            j++;    //Variable de posicion del tablero
        }
        i++;        //Variable de posicion del tablero
    }
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