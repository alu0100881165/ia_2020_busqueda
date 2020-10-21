#pragma once

#include "celda.hpp"

#include <cstdio>
#include <fstream>

using namespace std;

class Mapa_t
{
    private:
        int n_;        // Filas
        int m_;        // Columnas
        Celda_t* mapa_;  // Matriz

        void destroyMapa(void);

    public:
        
        Mapa_t(void);                 // Constructor
        Mapa_t(int n, int m);         // Constructor de copia
        
        ~Mapa_t(void);                // Destructor
        
        int getM(void);              // Getter columnas
        int getN(void);              // Getter filas
        Celda_t* getMapa(void);         // Getter mapa
        int getMapaPos(int n, int m);

        void setM(int m);            // Setter columnas
        void setN(int n);            // Setter filas
        void setMapa(int n, int m);  // Setter mapa
        fstream& setMapa(int n, int m, fstream& fichero);

        void rellenarMapa(void);
        fstream& rellenarObstaculos(fstream& fichero);
        void rellenarMovimientos(int i, int j);

        ostream& write(ostream& os);
};

