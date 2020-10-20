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


bool casos_int(int& valor)   // Cuando haces una entrada revisa la entrada
{
    cin >> valor;
    bool casos = cin.good(); // Devuelve 0 si la secuencia no existe 
    if (!casos)
    {
        system("clear");

        cin.clear();    // Limpiamos
        cin.ignore();   // Eliminamos el contenido
        cout << endl << "\E[31mLa respuesta no ha sido un numero\E[39m"<<endl;
    }

    return casos;
}

int main(void)
{
    
    int filas, columnas;
    
//    system("clear");
    cout << endl << "\e[1m\e[36mDIMENSIONES DEL TABLERO.\e[1m\e[36m" << endl;       // cian negrita    

    while (true)
    {
        cout << endl << "\E[33m- Introduzca el número de filas de la tabla: \E[33m";        // filas -> naranja
        //cin >> filas;
        if(casos_int(filas)) break; // crear una condicion para casos falsos
        
    }
   
    while (true)
    {
        cout << endl << "\E[33m- Introduzca el número de columnas de la tabla: \E[33m";      // columnas -> naranja
        //cin >> columnas;
        if(casos_int(columnas)) break;
    }
    
    Mapa_t mapa(filas, columnas);

    // system("clear");
	// cout<<endl<<"\E[45mPOSICIÓN INICIAL DEL VEHÍCULO.\E[45m"<< endl;

    return 0;

}