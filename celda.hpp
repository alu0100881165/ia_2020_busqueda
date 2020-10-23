#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Celda_t {
    private:
        char valor_;    // Símbolo que representa esa celda: 
                        // # pared
                        // $ obstáculo
                        // & coche
                        // € destino
        vector<int> movimientos_;   //Los movimientos van en este orden: izquierda, arriba, derecha, abajo

        void destroyCelda(void);    // Misma idea que el destroyMap

    public:

        Celda_t(void);      // Constructor por defecto

        ~Celda_t(void);     // Destructor

        char getValor(void);    // Devuelve el símbolo de la celda
        vector<int> getMovimientos(void);   // Devuelve el vector de movimientos
        int getMovimiento(int i);   // Devuelve un movimiento, según el valor de i sea 0, 1, 2 o 3

        void setValor(char valor);  // Set del símbolo de la celda
        void setMovimientos(vector<int> movimientos);   // Set del vector de movimientos de la celda

        ostream& write(ostream& os);    // Método para imprimir por pantalla la celda
};