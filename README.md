# ia_2020_busqueda

Práctica de la asignatura de Inteligencia Artificial, en la que se utiliza un algoritmo de búsqueda que permita a un "coche" autónomo llegar a su destino.

Primero, el programa pide por pantalla si desea leer los datos a través de un fichero(1) o no(0).

  - En el caso de que se seleccione 1, se leerá a través de un fichero creado los valores para la 
creación de la matriz, recogiendo por orden: filas, columnas, posición coche, posición destino y
obstáculos. 
  - En caso contrario, se pide por pantalla las filas y las columnas(>=4). Deberá elegir la 
introducción de los obstáculos de manera manual(0) o aleatoria(1). En ambas elecciones, se pedirá 
que introduzca la posición del coche y del destino(no pueden coincidir ni con una pared ni entre 
ellos).
  - Ahora toca con la insercción de los obstáculos. Si se seleccionó la opción manual, deberá 
  introducir la posición que quiera del obstáculo(no puede ser una pared, ni la posición del coche
  o del destino, ni de otro obstáculo ya introducido). En caso del aleatorio, se introducirá un
  porcentaje(0-100) de aparición de los obtáculos en nuestra matriz.