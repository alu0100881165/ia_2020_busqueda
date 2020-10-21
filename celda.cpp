#include "celda.hpp"

Celda_t::Celda_t():     // Constructor por defecto
    valor_('\0'),
    movimientos_(4)     // Siempre inicializa a 4 ya que hay 4 movimientos posibles
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

vector<int> Celda_t::getMovimientos(void)   // Devuelve el vector de movimientos
{
    return movimientos_;
}

int Celda_t::getMovimiento(int i)   // Devuelve un movimiento, según el valor de i sea 0, 1, 2 o 3
{
    return movimientos_[i];
}

void Celda_t::setValor(char valor)  // Set del símbolo de la celda
{
    valor_ = valor;
}

void Celda_t::setMovimientos(vector<int> movimientos)   // Set del vector de movimientos de la celda
{
    movimientos_ = movimientos;
}

ostream& Celda_t::write(ostream& os)    // Método para imprimir por pantalla la celda
{
    cout << valor_;

    return os;
}