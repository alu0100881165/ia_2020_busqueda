#pragma once

#include "mapa.hpp"

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <unistd.h>


using namespace std;

class Coche_t
{
    private:   
        pair<int, int> posicion_;
        vector<pair<int, int>> camino_;
        int contNodosGenerados_;

        void destroyCoche(void);

    public:
        Coche_t();   // Constructor
        Coche_t(pair<int, int> posicion); // Constructor de copia
        ~Coche_t();  // Destructor
        
        pair<int, int> getPosicion(void);       // Getter posiciones
        vector<pair<int, int>> getCamino(void); // Getter caminos
        int getContNodosGenerados(void);        // Getter Contador De los nodos ya generados

        void setPosicion(pair<int, int> posicion);          // Setter posiciones
        void setAppendCamino(pair<int, int>);               // Setter Anexar Caminos
        void setContNodosGenerados(int contNodosGenerados); // Setter Contador Nodos ya generados

        ostream& write(ostream& os);
        
        bool aStar(Mapa_t& mapa, bool heur);

        int heuristicaManhattan(pair<int, int> actual, pair<int, int> destino);
        int heuristicaEuclidean(pair<int, int> actual, pair<int, int> destino);
};
