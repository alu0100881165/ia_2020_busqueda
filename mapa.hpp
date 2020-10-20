#pragma once

#include <cstdio>
#include <iostream>

using namespace std;

class Mapa_t
{
    private:
        int n_;        // Filas
        int m_;        // Columnas
        char[] mapa_;  // Matriz

        void destroyMap(void);

    public:
        
        Mapa_t(void);           // Constructor
        Mapa_t(int n, int m);   // Constructor de copia
        
        ~Mapa_t(void);          // Destructor
        
        int get_m(void);        // Getter columnas
        int get_n(void);        // Getter filas
        char[] get_mapa(void);  // Getter mapa

        void set_m(int m);      // Setter columnas
        void set_n(int n);      // Setter filas
        void set_mapa(char[] mapa); // Setter mapa
};

