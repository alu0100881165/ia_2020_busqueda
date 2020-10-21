#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Celda_t {
    private:
        char valor_;
        vector<int> movimientos_;   //Los movimientos van en este orden: izquierda, arriba, derecha, abajo

        void destroyCelda(void);

    public:

    Celda_t(void);

    ~Celda_t(void);

    char getValor(void);
    vector<int> getMovimientos(void);
    int getMovimiento(int i);

    void setValor(char valor);
    void setMovimientos(vector<int> movimientos);

    ostream& write(ostream& os);
};