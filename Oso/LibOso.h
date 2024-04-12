void identificacion_alumno();

void letras_aleatorias(char tablero[5][5]);
void immprimir_tablero(char tablero[5][5]);
char escoger_letra();
bool ingresar_jugada(char tablero[5][5], int fil, char col, char let);
void aumentar_puntaje(char tablero[5][5],int f, int c, int &out_puntaje);
bool mas_punto_bot(char tablero[5][5],int &p_bot);
void imprimir_puntaje_jugador(int p_1, int p_2);
void imprimir_puntaje_bot(int p_1, int p_2);

void jugador_vs_jugador(char tablero[5][5], int turno, char jugador, int p_1, int p_2);
void bot_vs_jugador(char tablero[5][5], int turno, char jugador, int p_bot, int p_2);