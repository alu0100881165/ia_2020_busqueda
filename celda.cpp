#include "celda.hpp"

Celda_t::Celda_t():     // Constructor por defecto
    valor_('\0'),
    padre_(),
    movimientos_(),
    valorF(),
    valorG(0),
    valorH()
    {}

Celda_t::~Celda_t(void) //Destructor
{
    destroyCelda();
}

void Celda_t::destroyCelda(void)    // Se encarga de vaciar el contenido de los atributos, hay que hacerlo para el vector de mmovimientos
{
    setValor('\0');
}

char Celda_t::getValor(void)    // Devuelve el símbolo de la celda
{
    return valor_;
}

vector<pair<int, int>> Celda_t::getMovimientos(void)   // Devuelve el vector de movimientos
{
    return movimientos_;
}

pair<int, int> Celda_t::getMovimiento(int i)   // Devuelve un movimiento, según el valor de i sea 0, 1, 2 o 3
{
    return movimientos_[i];
}

pair<int, int> Celda_t::getPadre(void)
{
    return padre_;
}

int Celda_t::getF(void)
{
    return valorF;
}

int Celda_t::getG(void)
{
    return valorG;
}

int Celda_t::getH(void)
{
    return valorH;
}

void Celda_t::setValor(char valor)  // Set del símbolo de la celda
{
    valor_ = valor;
}

void Celda_t::setMovimientos(vector<pair<int, int>> movimientos)   // Set del vector de movimientos de la celda
{
    movimientos_ = movimientos;
}

void Celda_t::setPadre(pair<int, int> nuevo)
{
    padre_ = nuevo;
}

void Celda_t::setF(void)
{
    valorF = valorG + valorH;
}

void Celda_t::setG(int g)
{
    valorG = g; 
}

void Celda_t::setH(int h)
{
    valorH = h;    
}

ostream& Celda_t::write(ostream& os)    // Método para imprimir por pantalla la celda
{
    if(valor_ == '&')           // azul
    {
        os << "\E[34m" << setw(2) << valor_ << "\E[34m";
    }
    else if(valor_ == '=')      // rojo
    {
        os << "\E[31m" << setw(2) << valor_ << "\E[31m";
    }
    else if( valor_ == '#')     // verde
    {
        os<< "\E[32m" << setw(2) << valor_ << "\E[32m";
    }
    else                        // blanco
    {
        os << "\E[97m" << setw(2) << valor_ << "\E[97m";
    }

    return os;
}