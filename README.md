# Taller2
Implementación

Representación del Tablero:
Utilize  una matriz bidimensional para representar el tablero del juego.

Algoritmo Minimax con Poda Alfa-Beta
La poda alfa-beta me  facilito a reducir la cantidad de nodos evaluados durante la busqueda del árbol del juego, mejorando así
el redimiento de mi conecta 4.

Función Evaluación y Ganador:
La funciíon "evalua_jugada" sirve para evaluar la calidad de una jugada, basandose en la cantidad de fichas en línea de diferentes 
longitudes.
La función "Ganador" verifica si hay un ganador en el tablero. 

F. Registrar
Registra los resultados del juego en un archivo CSV, incluyendo el nivel de dificultad, el nombre del jugador y el puntaje.

Dificultad 
Configure la dificultad del juego ajutando la variable "MAX_PROFUNIDAD" que controla la profunidad máxima de búsqieda en
el árbol. 


Minimax Sin Poda
El algoritmo sin Poda, exploraria todas las ramas del árbol de juego hasta la profunidad máxima especificada.Calcularia el valor de cada nodo hoja y propagaria los valores hacia arriba hasta la raíz.
Osea que seria funcional pero seria muy lento para juegos complejos debido la gran cantidad que nodos que deberia explorar.
Minumax Con Poda
Reduce la cantidad de nodos evaluados, como dice su nombre, poda las ramas inecesarias, osea que evita explorar ramas que no afecta a la decesión final, esto mejora significamente el rediemineto de la IA.
