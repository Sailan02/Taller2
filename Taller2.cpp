#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>
#include <sstream>

const int MAX = 1;
const int MIN = -1;
int MAX_PROFUNDIDAD = 4;

std::pair<int, int> ganador(const std::vector<std::vector<int>> &tablero);
int evalua_jugada(const std::vector<std::vector<int>> &tablero, int jugador);
void ver_tablero(const std::vector<std::vector<int>> &tablero);
void inserta_ficha(std::vector<std::vector<int>> &tablero, int columna, int jugador);
bool game_over(const std::vector<std::vector<int>> &tablero);
std::pair<int, int> comprueba_linea(const std::vector<std::vector<int>> &tablero, int n, int jugador);
std::pair<int, int> negamax(const std::vector<std::vector<int>> &tablero, int jugador, int profundidad, int alfa, int beta);
std::vector<std::vector<int>> juega_humano(const std::vector<std::vector<int>> &tablero);
std::vector<std::vector<int>> juega_ordenador(const std::vector<std::vector<int>> &tablero);
std::vector<std::vector<int>> cargar_partida();
void registar(std::string nombre, int nivel, int puntaje);
int quien_conmienza(int numero);
int guardar_partida(int numero);
void subir_partida(const std::vector<std::vector<int>> &tablero);
int menu();
bool existe_contenido_en_csv();






int main()
{
    int opcion = menu();
    if (opcion == 1)
    {
        int numero;
        int opcion_New;
        std::string nombre;
        std::cout << "Nombre: ";
        std::cin >> nombre;
        std::vector<std::vector<int>> tablero(6, std::vector<int>(7, 0));
        std::cout << "Quien quieres que conmienze(1=Jugador//0=IA) ";
        std::cin >> numero;
        int numero1 = quien_conmienza(numero);
        bool ok = false;
        int profundidades[] = {3, 4, 6};
        int dificultad;
        while (!ok)
        {
            std::cout << "Dificultad (1=facil; 2=medio; 3=dificil): ";
            std::cin >> dificultad;

            if (std::cin.fail() || (dificultad >= 1 && dificultad <= 3))
            {
                MAX_PROFUNDIDAD = profundidades[dificultad - 1];
                ok = true;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrada no válida. Inténtalo de nuevo." << std::endl;
            }
        }
        if (numero == 1 || numero1 == 1)
        {
            while (true)
            {
                ver_tablero(tablero);
                tablero = juega_humano(tablero);
                if (game_over(tablero))
                {
                    registar(nombre, dificultad, evalua_jugada(tablero, MIN));
                    break;
                }
                tablero = juega_ordenador(tablero);
                if (game_over(tablero))
                {
                    break;
                }
            }

            ver_tablero(tablero);
        }
        else if (numero == 0 || numero1 == 0)
        {
            while (true)
            {
                tablero = juega_ordenador(tablero);
                if (game_over(tablero))
                {
                    break;
                }
                ver_tablero(tablero);
                tablero = juega_humano(tablero);
                if (game_over(tablero))
                {
                    registar(nombre, dificultad, evalua_jugada(tablero, MIN));
                    break;
                }
            }
            ver_tablero(tablero);
        }

        auto ganador_resultado = ganador(tablero);
        int g = ganador_resultado.first;
        std::string gana;
        if (g == 0)
        {
            gana = "Tablas";
        }
        else if (g == MIN)
        {
            gana = "Jugador";
        }
        else
        {
            gana = "Ordenador";
        }

        std::cout << "Ganador: " << gana << std::endl;
    }
    else if (opcion == 2)
    {
        if(!existe_contenido_en_csv()){
            exit(0);

        }
        std::string nombre;
        std::cout << "Nombre:";
        std::cin >> nombre;
        std::vector<std::vector<int>> tablero = cargar_partida();
        bool ok = false;
        int profundidades[] = {3, 4, 6};
        int dificultad;
        while (!ok)
        {
            std::cout << "Dificultad (1=facil; 2=medio; 3=dificil): ";
            std::cin >> dificultad;

            if (std::cin.fail() || (dificultad >= 1 && dificultad <= 3))
            {
                MAX_PROFUNDIDAD = profundidades[dificultad - 1];
                ok = true;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrada no válida. Inténtalo de nuevo." << std::endl;
            }
        }
        while (true)
        {
            ver_tablero(tablero);
            tablero = juega_humano(tablero);
            if (game_over(tablero))
            {
                registar(nombre, dificultad, evalua_jugada(tablero, MIN));
                break;
            }
            tablero = juega_ordenador(tablero);
            if (game_over(tablero))
            {
                break;
            }
        }

        ver_tablero(tablero);
        auto ganador_resultado = ganador(tablero);
        int g = ganador_resultado.first;
        std::string gana;
        if (g == 0)
        {
            gana = "Tablas";
        }
        else if (g == MIN)
        {
            gana = "Jugador";
        }
        else
        {
            gana = "Ordenador";
        }

        std::cout << "Ganador: " << gana << std::endl;
    }
    return 0;
}
int menu()
{
    int numero;
    std::cout << "Desear inicar un Juego Nuevo(Si=1//No=2)" << std::endl;
    std::cin >> numero;
    while (true)
    {
        if (numero == 1)
        {
            return 1;
        }
        else if (numero == 2)
        {
            return 2;
        }
        else
        {
            std::cout << "Opcion no valida" << std::endl;
            std::cin >> numero;
        }
    }
}
void registar(std::string nombre, int nivel, int puntaje)
{
    std::string nombreArchivo = "datos.csv";
    std::ofstream archivoSalida(nombreArchivo, std::ios::app);
    if (nivel == 1)
    {
        archivoSalida << nivel << "," << nombre << "," << puntaje << "\n";
    }
    else if (nivel == 2)
    {
        archivoSalida << nivel << "," << nombre << "," << puntaje << "\n";
    }
    else if (nivel == 3)
    {
        archivoSalida << nivel << "," << nombre << "," << puntaje << "\n";
    }
}
int quien_conmienza(int numero)
{
    while (true)
    {
        if (numero == 1)
        {
            std::cout << "Conmienza Jugador " << std::endl;
            return numero;
        }
        else if (numero == 0)
        {
            std::cout << "Conmienza la IA " << std::endl;
            return numero;
        }
        else
        {
            std::cout << "Opcion no valida" << std::endl;
            std::cin >> numero;
        }
    }
}
std::pair<int, int> ganador(const std::vector<std::vector<int>> &tablero)
{
    return comprueba_linea(tablero, 4, 0);
}
int evalua_jugada(const std::vector<std::vector<int>> &tablero, int jugador)
{
    int n2 = comprueba_linea(tablero, 2, jugador).second;
    int n3 = comprueba_linea(tablero, 3, jugador).second;
    int n4 = comprueba_linea(tablero, 4, jugador).second;
    return 4 * n2 + 9 * n3 + 1000 * n4;
}
void ver_tablero(const std::vector<std::vector<int>> &tablero)
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (tablero[i][j] == MAX)
            {
                std::cout << "X ";
            }
            else if (tablero[i][j] == MIN)
            {
                std::cout << "O ";
            }
            else
            {
                std::cout << '.';
                std::cout << ' ';
            }
        }
        std::cout << "\n";
    }
    std::cout << "- - - - - - -" << std::endl;
    std::cout << "1 2 3 4 5 6 7" << std::endl;
}
void inserta_ficha(std::vector<std::vector<int>> &tablero, int columna, int jugador)
{
    // encontrar la primera casilla libre en la columna y colocar la ficha
    for (int i = 5; i >= 0; --i)
    {
        if (tablero[i][columna] == 0)
        {
            tablero[i][columna] = jugador;
            break;
        }
    }
}
bool game_over(const std::vector<std::vector<int>> &tablero)
{
    // EMPATE
    bool no_tablas = false;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (tablero[i][j] == 0)
            {
                no_tablas = true;
            }
        }
    }

    // Hay ganador?
    if (ganador(tablero).first == 0 && no_tablas)
    {
        return false;
    }
    else
    {
        return true;
    }
}
std::pair<int, int> comprueba_linea(const std::vector<std::vector<int>> &tablero, int n, int jugador)
{
    int ganador = 0;
    int num_lineas = 0;
    int lineas_posibles = 7 - n;

    // Buscar línea horizontal
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < lineas_posibles; ++j)
        {
            std::vector<int> cuaterna(tablero[i].begin() + j, tablero[i].begin() + j + n);
            if (std::all_of(cuaterna.begin(), cuaterna.end(), [tablero, i, j](int x)
                            { return x == tablero[i][j] && tablero[i][j] != 0; }))
            {
                ganador = tablero[i][j];
                if (ganador == jugador)
                {
                    num_lineas++;
                }
            }
        }
    }

    // Buscar línea vertical
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < lineas_posibles; ++j)
        {
            std::vector<int> cuaterna;
            for (int k = 0; k < n; ++k)
            {
                cuaterna.push_back(tablero[j + k][i]);
            }
            if (std::all_of(cuaterna.begin(), cuaterna.end(), [tablero, j, i](int x)
                            { return x == tablero[j][i] && tablero[j][i] != 0; }))
            {
                ganador = tablero[j][i];
                if (ganador == jugador)
                {
                    num_lineas++;
                }
            }
        }
    }

    // Buscar línea diagonal
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < lineas_posibles - i; ++j)
        {
            std::vector<int> cuaterna1, cuaterna2, cuaterna3, cuaterna4;

            for (int k = 0; k < n; ++k)
            {
                cuaterna1.push_back(tablero[i + j + k][j + k]);
                cuaterna2.push_back(tablero[i + j][i + j + k]);
                cuaterna3.push_back(tablero[i + j + k][6 - (j + k)]);
                cuaterna4.push_back(tablero[j + k][6 - (i + j + k)]);
            }

            if (std::all_of(cuaterna1.begin(), cuaterna1.end(), [tablero, i, j](int x)
                            { return x == tablero[i + j][j] && tablero[i + j][j] != 0; }))
            {
                ganador = tablero[i + j][j];
                if (ganador == jugador)
                {
                    num_lineas++;
                }
            }
            else if (std::all_of(cuaterna2.begin(), cuaterna2.end(), [tablero, i, j](int x)
                                 { return x == tablero[i + j][i + j] && tablero[i + j][i + j] != 0; }))
            {
                ganador = tablero[i + j][i + j];
                if (ganador == jugador)
                {
                    num_lineas++;
                }
            }
            else if (std::all_of(cuaterna3.begin(), cuaterna3.end(), [tablero, i, j](int x)
                                 { return x == tablero[i + j][6 - j] && tablero[i + j][6 - j] != 0; }))
            {
                ganador = tablero[i + j][6 - j];
                if (ganador == jugador)
                {
                    num_lineas++;
                }
            }
            else if (std::all_of(cuaterna4.begin(), cuaterna4.end(), [tablero, j, i](int x)
                                 { return x == tablero[j][6 - (i + j)] && tablero[j][6 - (i + j)] != 0; }))
            {
                ganador = tablero[j][6 - (i + j)];
                if (ganador == jugador)
                {
                    num_lineas++;
                }
            }
        }
    }

    return {ganador, num_lineas};
}
std::pair<int, int> negamax(const std::vector<std::vector<int>> &tablero, int jugador, int profundidad, int alfa, int beta)
{
    int max_puntuacion = INT_MIN;
    int jugada_max = -1;
    int alfa_local = alfa;

    for (int jugada = 0; jugada < 7; ++jugada)
    {
        // columna totalmente llena?
        if (tablero[0][jugada] == 0)
        {
            std::vector<std::vector<int>> tableroaux = tablero;
            inserta_ficha(tableroaux, jugada, jugador);
            if (game_over(tableroaux) || profundidad == 0)
            {
                return {evalua_jugada(tableroaux, jugador), jugada};
            }
            else
            {
                int puntuacion = -negamax(tableroaux, jugador * -1, profundidad - 1, -beta, -alfa_local).first;
                if (puntuacion > max_puntuacion)
                {
                    max_puntuacion = puntuacion;
                    jugada_max = jugada;
                }

                // poda alfa beta
                if (max_puntuacion >= beta)
                {
                    break;
                }
                if (max_puntuacion > alfa_local)
                {
                    alfa_local = max_puntuacion;
                }
            }
        }
    }

    return {max_puntuacion, jugada_max};
}
std::vector<std::vector<int>> juega_humano(const std::vector<std::vector<int>> &tablero)
{
    bool ok = false;
    int col;
    while (!ok)
    {
        std::cout << "Columna (0=salir)? ";
        std::cin >> col;
        if (std::cin.fail() || (col >= 1 && col <= 7))
        {
            std::vector<std::vector<int>> tablero_modificado = tablero;
            inserta_ficha(tablero_modificado, col - 1, MIN);
            return tablero_modificado;
        }
        else if (col == 0)
        {
            int numero;
            std::cout << "Deseas guardar la partida (0=NO//1=SI)" << std::endl;
            std::cin >> numero;
            int numero1 = guardar_partida(numero);
            if (numero == 0 || numero1 == 0)
            {
                exit(0);
            }
            else if (numero == 1 || numero1 == 1)
            {
                subir_partida(tablero);
                exit(0);
            }
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Movimiento ilegal. Inténtalo de nuevo." << std::endl;
        }
    }
    return tablero;
}
void subir_partida(const std::vector<std::vector<int>> &tablero)
{
    std::ofstream archivo_salida("guardar_tablero.csv");

    // Guardar el tamaño del tablero
    archivo_salida << tablero.size() << " " << tablero[0].size() << "\n";

    // Guardar el contenido del tablero
    for (const auto &fila : tablero)
    {
        for (int valor : fila)
        {
            archivo_salida << valor << " ";
        }
        archivo_salida << "\n";
    }
}
int guardar_partida(int numero)
{
    while (true)
    {
        if (numero == 0)
        {
            std::cout << "ADIOS" << std::endl;
            return 0;
        }
        else if (numero == 1)
        {

            return 1;
        }
        else
        {
            std::cout << "Opcion no Valida" << std::endl;
            std::cin >> numero;
        }
    }
}
std::vector<std::vector<int>> cargar_partida()
{
    std::ifstream archivo_entrada("guardar_tablero.csv");
    int filas, columnas;

    // Leer el tamaño del tablero
    archivo_entrada >> filas >> columnas;


    // Crear un nuevo tablero con el tamaño leído
    std::vector<std::vector<int>> tablero(filas, std::vector<int>(columnas));

    // Leer el contenido del tablero
    for (auto &fila : tablero)
    {
        for (int &valor : fila)
        {
            archivo_entrada >> valor;
        }
    }

    return tablero;
}
bool existe_contenido_en_csv()
{
    std::ifstream archivo_entrada("guardar_tablero.csv");

    int primer_valor;
    archivo_entrada >> primer_valor;

    // Verificar si la lectura fue exitosa
    if (archivo_entrada.fail())
    {
        std::cerr << "No existe un juego guardado" << std::endl;
        return false;
    }
    return true;
}
std::vector<std::vector<int>> juega_ordenador(const std::vector<std::vector<int>> &tablero)
{
    std::vector<std::vector<int>> tablerotmp = tablero;
    auto result = negamax(tablerotmp, MAX, MAX_PROFUNDIDAD, -INT_MAX, INT_MAX);
    inserta_ficha(tablerotmp, result.second, MAX);
    return tablerotmp;
}