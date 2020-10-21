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

#include <string>


bool casos_int(int& valor)   // Cuando haces una entrada revisa la entrada
{
    cin >> valor;
    bool casos = cin.good(); // Devuelve 0 si la secuencia no existe 
    if (!casos)
    {
        system("clear");

        cin.clear();    // Limpiamos
        cin.ignore();   // Eliminamos el contenido
        cout << endl << "\E[31mLa respuesta no ha sido un numero\E[39m" << endl;
    }

    return !casos;
}

int main(void)
{
    bool opcion;
    int filas, columnas;
    fstream ficheroEntrada; // Variable que almacena el fichero del que se lee
    string nombreFichero;   // Variable que almacena el nombre del fichero para después abrirlo
    Mapa_t mapa;            // Mapa vacío
    
//    system("clear");
    cout << "\e[1m\e[36m¿Desea leer desde fichero o no? (1 si, 0 no): \e[1m\e[36m"; // Si el usuario presiona 1 lee desde fichero, no está hecho de momento la opción manual
    cin >> opcion;

    if(opcion)  // Opción de fichero
    {
        cout << endl << "\E[33m- Introduzca el nombre del fichero: \E[33m";        // filas -> naranja 
        cin >> nombreFichero;

        ficheroEntrada.open(nombreFichero.c_str(), fstream::in);    // Se abre el fichero de entrada
        if(ficheroEntrada.is_open())    // Comprobamos que el fichero se haya abierto bien
        {
            ficheroEntrada >> filas >> columnas;    // Las dos primeras líneas del fichero son las filas y las columnas, las almacenamos en sus respectivas variables

            mapa.setMapa(filas, columnas, ficheroEntrada);  // Se pasa al método setMapa lo necesario para construir todo el mapa sin punto de salida ni de llegada
        }
        else    // En caso de error al abrir el fichero se indica al usuario y termina la ejecución del programa
        {
            cout << endl << "\E[31mEl fichero no existe o no tiene permisos\E[39m" << endl;
            return 1;
        }
    }
    else    // Opción manual, falta por hacerse
    {      
        cout << endl << "\e[1m\e[36mDIMENSIONES DEL TABLERO.\e[1m\e[36m" << endl;       // cian negrita    

        do
        {
            cout << endl << "\E[33m- Introduzca el número de filas de la tabla: \E[33m";        // filas -> naranja
        } 
        while (casos_int(filas));

        do
        {
            cout << endl << "\E[33m- Introduzca el número de columnas de la tabla: \E[33m";      // columnas -> naranja
        } 
        while (casos_int(columnas));
    }

    mapa.write(cout);   // Al final, se imprime por pantalla el contenido del mapa.

    // system("clear");
	// cout<<endl<<"\E[45mPOSICIÓN INICIAL DEL VEHÍCULO.\E[45m"<< endl;

    return 0;

}