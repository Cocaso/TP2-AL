//clonado? asdafsaf
#include <iostream>
#include <fstream>  //tentativo 
#include <cstdio>
using namespace std;
#include "BMP/EasyBMP.h"


int main() {
    BMP casilla1, casilla2, casilla3;
    casilla1.ReadFromFile("Casilleros/agua.bmp");
    casilla2.ReadFromFile("Casilleros/barco.bmp");
    casilla3.ReadFromFile("Casilleros/nadando.bmp");
    
    BMP Tablero;
    Tablero.SetSize(320, 320);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            BMP* casilla_a_dibujar;
            if (i % 2 == j % 2) {
                casilla_a_dibujar = &casilla1;
            } else if (i % 3 == 0) {
                casilla_a_dibujar = &casilla2;
            } else {
                casilla_a_dibujar = &casilla3;
            }

            for (int x = 0; x < 32; ++x) {
                for (int y = 0; y < 32; ++y) {
                    RGBApixel pixel = (casilla_a_dibujar)(x, y);
                    Tablero(i*32 + x, j*32 + y)->Red = pixel.Red;
                    Tablero(i*32 + x, j*32 + y)->Green = pixel.Green;
                    Tablero(i*32 + x, j*32 + y)->Blue = pixel.Blue;
                    Tablero(i*32 + x, j*32 + y)->Alpha = pixel.Alpha;
                }
            }
        }
    }

    Tablero.WriteToFile("Tablero.bmp");

    return 0;
}