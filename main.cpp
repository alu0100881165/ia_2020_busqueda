/* Universidad de La Laguna, Escuela Superior de Ingeniería y Tecnología.
*  INTELIGENCIA ARTIFICIAL: **PRÁCTICA DE BÚSQUEDA**.
*  Integrantes del grupo:
*  - Daniel Nuez Wehbe
*  - José Javier Díaz González
*  - Ricardo Fariña Mesa 
*  Enunciado del problema:
* 
*      Un coche autónomo se puede suponer rectangular de dimensiones M x N 
*   y constituido por celdas libres y ocupadas, donde el coche puede efectuar acciones 
*   de movimiento, una cada vez, desde la casilla actual a una de las 4-vecinas 
*   (Norte, Sur, Este u Oeste) que no se encuentre ocupada. Las casillas ocupadas 
*   corresponden a obstáculos. Las casillas libres corresponden con celdas libres 
*   de obstáculos.
*/

#include "mapa.hpp"

int main(void)
{
    
    int filas, columnas;
    
//    system("clear");
    cout << endl << "\e[1m\e[36mDIMENSIONES DEL TABLERO.\e[1m\e[36m" << endl;       // cian negrita    

    cout<<endl<<"\E[33m- Introduzca el número de filas de la tabla: \E[33m";        // filas -> naranja
    cin >> filas;

    cout<<endl<<"\E[33m- Introduzca el número de columnas de la tabla: \E[33m";      // columnas -> naranja
    cin >> columnas;

    cout << "Número de filas: " << filas << ", número de columnas: " << columnas << endl;

    // system("clear");
	// cout<<endl<<"\E[45mPOSICIÓN INICIAL DEL VEHÍCULO.\E[45m"<< endl;

    return 0;

}