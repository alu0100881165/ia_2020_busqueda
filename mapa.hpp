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
        Celda_t* mapa_;  // Matriz (array de celdas)
        pair<int, int> destino_;

        void destroyMapa(void);

    public:
        
        Mapa_t(void);                 // Constructor
        Mapa_t(int n, int m);         // Constructor de copia
        
        ~Mapa_t(void);                // Destructor
        
        int getM(void);              // Getter columnas
        int getN(void);              // Getter filas
        Celda_t* getMapa(void);         // Getter mapa
        int getMapaPos(int n, int m);
        pair<int, int> getDestino(void);

        void setM(int m);            // Setter columnas
        void setN(int n);            // Setter filas
        void setMapa(int n, int m);  // Setter mapa, crea un mapa de tamaño n * m
        fstream& setMapa(int n, int m, fstream& fichero);   // Setter del mapa que sirve para leer desde un fichero la información del mismo 
                                                            // y crear el mapa de tamaño n * m, rellenarlo y añadirle los obstáculos.
        void setDestino(pair<int, int> pos);

        void rellenarMapa(void);                            // Recorre el mapa, y lo rellena poniendo en los bordes el símbolo '#', y en el interior '.'
                                                            // Además llama al mñetodo setMovimientos cada vez que se crea un borde, para dejar claro que no
                                                            // se puede desplazar desde esa posición (que además es inalcanzable) a otra.
        fstream& rellenarCoche(fstream& fichero);
        fstream& rellenarObstaculos(fstream& fichero);      // Lee desde el fichero que se pasa la posición de los obstáculos y los
                                                            // coloca en el mapa. Además llama a rellenar movimientos (que no itera en los
                                                            // bordes del mapa), que se encarga de indicar qué movimientos se pueden hacer
                                                            // desde esa celda.
        void rellenarManual(int n, int m, char c);          // Función que rellena la celda con el símbolo correspondiente depende de dónde se llame:
                                                            // '&' para el vehículo, '=' para el destino y '#' para los obstáculos.
        void rellenarMovimientos(int i, int j);             // Revisa la posición del mapa que se pasa como argumento, y se comprueba qué hay en
                                                            // las cuatro direcciones de la celda, y almacena en un vector de enteros con un 0
                                                            // aquellos movimientos que puede realizar, y con un 1 aquellos que no.

        ostream& write(ostream& os);                        // Método que pinta por pantalla el mapa. Pasa por referencia un ostream, esto no es necesario
                                                            // pero queda bien, y llama al método write de la celda que hace lo mismo.
};