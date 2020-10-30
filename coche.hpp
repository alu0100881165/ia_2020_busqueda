#pragma once

#include "mapa.hpp"

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

class Coche_t
{
    private:   
        pair<int, int> posicion_;
        vector<pair<int, int>> camino_;
        void destroyCoche(void);

    public:
        Coche_t();   // Constructor
        Coche_t(pair<int, int> posicion); // Constructor de copia
        ~Coche_t();  // Destructor
        
        pair<int, int> getPosicion(void);  // Getter posiciones
        void setPosicion(pair<int, int> posicion); // Setter posiciones

        ostream& write(ostream& os);

        void aStar(Mapa_t& mapa);

        int heuristicaManhattan(pair<int, int> destino);
};
