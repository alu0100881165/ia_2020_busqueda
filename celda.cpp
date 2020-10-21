#include "celda.hpp"

Celda_t::Celda_t():
    valor_('\0'),
    movimientos_(4)
    {}

Celda_t::~Celda_t(void)
{
    destroyCelda();
}

void Celda_t::destroyCelda(void)
{
    setValor('\0');
}

char Celda_t::getValor(void)
{
    return valor_;
}

vector<int> Celda_t::getMovimientos(void)
{
    return movimientos_;
}

int Celda_t::getMovimiento(int i)
{
    return movimientos_[i];
}

void Celda_t::setValor(char valor)
{
    valor_ = valor;
}

void Celda_t::setMovimientos(vector<int> movimientos)
{
    movimientos_ = movimientos;
}

ostream& Celda_t::write(ostream& os)
{
    cout << valor_;

    return os;
}