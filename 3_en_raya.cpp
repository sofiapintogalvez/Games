#include <iostream>
#include <cstdlib>
#include <ctime>

void identificacion_alumno()
{
    std::system("cls");            // Comando para borrar todo el contenido de la pantalla
    std::cout << "\x1B[H";          // Codigo para colocar el cursor en el canto superior izquierdo
    std::cout << "\x1B[3;35m";         // Mostrar el siguiente texto en modo de letra italico "[3;" y color azul "[ ;34m"   
    std::cout << "/***************************************************/" << std::endl; 
    std::cout << "\x1B[m";             // Resetear color a valor por defecto
    std::cout << "Universidad Catolica San Pablo" << std::endl; 
    std::cout << "Escuela Profesional de Ciencia de la Computacion" << std::endl; 
    std::cout << "Curso de Ciencia de la Computacion I" << std::endl; 
    std::cout << "Prof. D.Sc. Manuel Eduardo Loaiza Fernandez" << std::endl;
    std::cout << "Alumnos: Sofia Alejandra Pinto Galvez y Lucius Matheo Caldenhoven Loayza" << std::endl;
    std::cout << "Arequipa 2023 - I" << std::endl; 
    std::cout << "\x1B[3;35m";         // Mostrar el siguiente texto en modo de letra italico "[3;" y color azul "[ ;34m"   
    std::cout << "/***************************************************/" << std::endl;
    std::cout << "\x1B[m";             // Resetear color a valor por defecto
}

void tablero(char y1, char y2, char y3, char y4, char y5, char y6, char y7, char y8, char y9)
{
    std::cout << "\x1B[3;33m";
    std::cout << y1 << " | " << y2 << " | " << y3 << "\n";
    std::cout << "---------" << std::endl;
    std::cout << y4 << " | " << y5 << " | " << y6 << "\n";
    std::cout << "---------" << std::endl;
    std::cout << y7 << " | " << y8 << " | " << y9 << "\n\n";
    std::cout << "\x1B[m";
}

bool ingresar_jugada(char simbolo, char &out_y, int &out_turno)
{
    if(out_y != 'X' && out_y != 'O')
    {
        out_y = simbolo;
        out_turno++;
        return false;
    }
    else
    {
        return true;
    }
}

void puntaje(int p_bot, int p_jugador)
{
    std::cout << "BOT: " << p_bot << "  " << "JUGADOR: " << p_jugador << "\n\n";
}

bool ganador(char y1, char y2, char y3, char y4, char y5, char y6, char y7, char y8, char y9, char simbolo)
{
    if((y1 == y2 && y2 == y3 && y3 == simbolo) || (y4 == y5 && y5 == y6 && y6 == simbolo) || (y7 == y8 && y8 == y9 && y9 == simbolo) || (y1 == y4 && y4 == y7 && y7 == simbolo) || 
        (y2 == y5 && y5 == y8 && y8 == simbolo) || (y3 == y6 && y6 == y9 && y9 == simbolo) || (y1 == y5 && y5 == y9 && y9 == simbolo) || (y3 == y5 && y5 == y7 && y7 == simbolo))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool tablero_lleno(char y1, char y2, char y3, char y4, char y5, char y6, char y7, char y8, char y9)
{
    return y1 != '1' && y2 != '2' && y3 != '3' && y4 != '4' && y5 != '5' && y6 != '6' && y7 != '7' && y8 != '8' && y9 != '9';
}

bool jugar_de_nuevo(char &out_y1, char &out_y2, char &out_y3, char &out_y4, char &out_y5, char &out_y6, char &out_y7, char &out_y8, char &out_y9, int &out_turno)
{
    char respuesta;

    std::cout << "\nDesea jugar de nuevo? (s/n): ";
    std::cin >> respuesta;

    if(respuesta == 's' || respuesta == 'S')
    {
        out_y1 = '1', out_y2 = '2', out_y3 = '3', out_y4 = '4', out_y5 = '5', out_y6 = '6', out_y7 = '7', out_y8 = '8', out_y9 = '9';
        out_turno = 1;
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    char y1{'1'}, y2{'2'}, y3{'3'}, y4{'4'}, y5{'5'}, y6{'6'}, y7{'7'}, y8{'8'}, y9{'9'};
    char bot{'X'}, jugador{'O'};
    int puntaje_bot{0}, puntaje_jugador{0};
    int turno{1};
    int posicion;
    srand(time(NULL));

    identificacion_alumno();
    tablero(y1, y2, y3, y4, y5, y6, y7, y8, y9);

    do
    {
        bool ocupado = false;

        if(turno%2 == 1)
        {
            if(y1 == y5 && y5 == 'X' && y9 != 'X' && y9 != 'O')
            {
                y9 = bot;
                turno++;
            }
            else if(y5 == y9 && y9 == 'X' && y1 != 'X' && y1 != 'O')
            {
                y1 = bot;
                turno++;
            }
            else if(y1 == y9 && y9 == 'X' && y5 != 'X' && y5 != 'O')
            {
                y5 = bot;
                turno++;
            }
            else if(y3 == y5 && y5 == 'X' && y7 != 'X' && y7 != 'O')
            {
                y7 = bot;
                turno++;
            }
            else if(y5 == y7 && y7 == 'X' && y3 != 'X' && y3 != 'O')
            {
                y3 = bot;
                turno++;
            }
            else if(y3 == y7 && y7 == 'X' && y5 != 'X' && y5 != 'O')
            {
                y5 = bot;
                turno++;
            }
            else if(y1 == y4 && y4 == 'X' && y7 != 'X' && y7 != 'O')
            {
                y7 = bot;
                turno++;
            }
            else if(y4 == y7 && y7 == 'X' && y1 != 'X' && y1 != 'O')
            {
                y1 = bot;
                turno++;
            }
            else if(y1 == y7 && y7 == 'X' && y4 != 'X' && y4 != 'O')
            {
                y4 = bot;
                turno++;
            }
            else if(y2 == y5 && y5 == 'X' && y8 != 'X' && y8 != 'O')
            {
                y8 = bot;
                turno++;
            }
            else if(y5 == y8 && y8 == 'X' && y2 != 'X' && y2 != 'O')
            {
                y2 = bot;
                turno++;
            }
            else if(y2 == y8 && y8 == 'X' && y5 != 'X' && y5 != 'O')
            {
                y5 = bot;
                turno++;
            }
            else if(y3 == y6 && y6 == 'X' && y9 != 'X' && y9 != 'O')
            {
                y9 = bot;
                turno++;
            }
            else if(y6 == y9 && y9 == 'X' && y3 != 'X' && y3 != 'O')
            {
                y3 = bot;
                turno++;
            }
            else if(y3 == y9 && y9 == 'X' && y6 != 'X' && y6 != 'O')
            {
                y6 = bot;
                turno++;
            }
            else if(y1 == y2 && y2 == 'X' && y3 != 'X' && y3 != 'O')
            {
                y3 = bot;
                turno++;
            }
            else if(y2 == y3 && y3 == 'X' && y1 != 'X' && y1 != 'O')
            {
                y1 = bot;
                turno++;
            }
            else if(y4 == y5 && y5 == 'X' && y6 != 'X' && y6 != 'O')
            {
                y6 = bot;
                turno++;
            }
            else if(y5 == y6 && y6 == 'X' && y4 != 'X' && y4 != 'O')
            {
                y4 = bot;
                turno++;
            }
            else if(y7 == y8 && y8 == 'X' && y9 != 'X' && y9 != 'O')
            {
                y9 = bot;
                turno++;
            }
            else if(y8 == y9 && y9 == 'X' && y7 != 'X' && y7 != 'O')
            {
                y7 = bot;
                turno++;
            }
            else if(y1 == y3 && y3 == 'X' && y2 != 'X' && y2 != 'O')
            {
                y2 = bot;
                turno++;
            }
            else if(y4 == y6 && y6 == 'X' && y5 != 'X' && y5 != 'O')
            {
                y5 = bot;
                turno++;
            }
            else if(y7 == y9 && y9 == 'X' && y8 != 'X' && y8 != 'O')
            {
                y8 = bot;
                turno++;
            }
            else if(y1 == y5 && y5 == 'O' && y9 != 'X')
            {
                y9 = bot;
                turno++;
            }
            else if(y5 == y9 && y9 == 'O' && y1 != 'X')
            {
                y1 = bot;
                turno++;
            }
            else if(y1 == y9 && y9 == 'O' && y5 != 'X')
            {
                y5 = bot;
                turno++;
            }
            else if(y3 == y5 && y5 == 'O' && y7 != 'X')
            {
                y7 = bot;
                turno++;
            }
            else if(y5 == y7 && y7 == 'O' && y3 != 'X')
            {
                y3 = bot;
                turno++;
            }
            else if(y3 == y7 && y7 == 'O' && y5 != 'X')
            {
                y5 = bot;
                turno++;
            }
            else if(y1 == y4 && y4 == 'O' && y7 != 'X')
            {
                y7 = bot;
                turno++;
            }
            else if(y4 == y7 && y7 == 'O' && y1 != 'X')
            {
                y1 = bot;
                turno++;
            }
            else if(y1 == y7 && y7 == 'O' && y4 != 'X')
            {
                y4 = bot;
                turno++;
            }
            else if(y2 == y5 && y5 == 'O' && y8 != 'X')
            {
                y8 = bot;
                turno++;
            }
            else if(y5 == y8 && y8 == 'O' && y2 != 'X')
            {
                y2 = bot;
                turno++;
            }
            else if(y2 == y8 && y8 == 'O' && y5 != 'X')
            {
                y5 = bot;
                turno++;
            }
            else if(y3 == y6 && y6 == 'O' && y9 != 'X')
            {
                y9 = bot;
                turno++;
            }
            else if(y6 == y9 && y9 == 'O' && y3 != 'X')
            {
                y3 = bot;
                turno++;
            }
            else if(y3 == y9 && y9 == 'O' && y6 != 'X')
            {
                y6 = bot;
                turno++;
            }
            else if(y1 == y2 && y2 == 'O' && y3 != 'X')
            {
                y3 = bot;
                turno++;
            }
            else if(y2 == y3 && y3 == 'O' && y1 != 'X')
            {
                y1 = bot;
                turno++;
            }
            else if(y4 == y5 && y5 == 'O' && y6 != 'X')
            {
                y6 = bot;
                turno++;
            }
            else if(y5 == y6 && y6 == 'O' && y4 != 'X')
            {
                y4 = bot;
                turno++;
            }
            else if(y7 == y8 && y8 == 'O' && y9 != 'X')
            {
                y9 = bot;
                turno++;
            }
            else if(y8 == y9 && y9 == 'O' && y7 != 'X')
            {
                y7 = bot;
                turno++;
            }
            else if(y1 == y3 && y3 == 'O' && y2 != 'X')
            {
                y2 = bot;
                turno++;
            }
            else if(y4 == y6 && y6 == 'O' && y5 != 'X')
            {
                y5 = bot;
                turno++;
            }
            else if(y7 == y9 && y9 == 'O' && y8 != 'X')
            {
                y8 = bot;
                turno++;
            }
            else
            {                
                srand(time(NULL));
                posicion = 1 + (std::rand() % (9));

                switch(posicion)
                {
                    case 1:
                    ocupado = ingresar_jugada(bot,y1,turno);
                    break;

                    case 2:
                    ocupado = ingresar_jugada(bot,y2,turno);
                    break;

                    case 3:
                    ocupado = ingresar_jugada(bot,y3,turno);
                    break;

                    case 4:
                    ocupado = ingresar_jugada(bot,y4,turno);
                    break;

                    case 5:
                    ocupado = ingresar_jugada(bot,y5,turno);
                    break;

                    case 6:
                    ocupado = ingresar_jugada(bot,y6,turno);
                    break;

                    case 7:
                    ocupado = ingresar_jugada(bot,y7,turno);
                    break;

                    case 8:
                    ocupado = ingresar_jugada(bot,y8,turno);
                    break;

                    case 9:
                    ocupado = ingresar_jugada(bot,y9,turno);
                    break;
                }
            }
        }
        else
        {
            std::cout << "Jugador ingrese posicion: ";
            std::cin >> posicion;

            switch(posicion)
            {
                case 1:
                ocupado = ingresar_jugada(jugador,y1,turno);
                break;

                case 2:
                ocupado = ingresar_jugada(jugador,y2,turno);
                break;

                case 3:
                ocupado = ingresar_jugada(jugador,y3,turno);
                break;

                case 4:
                ocupado = ingresar_jugada(jugador,y4,turno);
                break;

                case 5:
                ocupado = ingresar_jugada(jugador,y5,turno);
                break;

                case 6:
                ocupado = ingresar_jugada(jugador,y6,turno);
                break;

                case 7:
                ocupado = ingresar_jugada(jugador,y7,turno);
                break;

                case 8:
                ocupado = ingresar_jugada(jugador,y8,turno);
                break;

                case 9:
                ocupado = ingresar_jugada(jugador,y9,turno);
                break;

                default:
                std::cout << "\nUPS! No existe esa posicion, vuelva a intentar\n\n";
                continue;
            }
        }

        if(ocupado)
        {
            if(turno%2 == 0)
            {
                std::cout << "\nUPS! Esta casilla esta ocupada\n\n";
                continue;
            }
            else
            {
                continue;
            }
        }
        else
        {
            identificacion_alumno();
            puntaje(puntaje_bot, puntaje_jugador);
            tablero(y1, y2, y3, y4, y5, y6, y7, y8, y9);
        }

        if(ganador(y1, y2, y3, y4, y5, y6, y7, y8, y9, bot))
        {
            puntaje_bot++;
            std::cout << "FELICIDADES! Ganaron las X\n";

            if(jugar_de_nuevo(y1, y2, y3, y4, y5, y6, y7, y8, y9, turno) == false)
            {
                std::cout << "\n";
                puntaje(puntaje_bot, puntaje_jugador);
                break;
            }
        }

        if(ganador(y1, y2, y3, y4, y5, y6, y7, y8, y9, jugador))
        {
            puntaje_jugador++;
            std::cout << "FELICIDADES! Ganaron las O\n";

            if(jugar_de_nuevo(y1, y2, y3, y4, y5, y6, y7, y8, y9, turno) == false)
            {
                std::cout << "\n";
                puntaje(puntaje_bot, puntaje_jugador);
                break;
            }
        }

        if(tablero_lleno(y1, y2, y3, y4, y5, y6, y7, y8, y9))
        {
            std::cout << "EMPATE! Nadie gano\n";
            if(jugar_de_nuevo(y1, y2, y3, y4, y5, y6, y7, y8, y9, turno) == false)
            {
                std::cout << "\n";
                puntaje(puntaje_bot, puntaje_jugador);
                break;
            }
        }
    }
    while(turno <= 9);

    return 0;
}