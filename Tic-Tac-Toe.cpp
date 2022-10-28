#include <iostream>
#include <conio.h> // Console Input-Output. -getch()-
#include <windows.h>
#include <locale.h>
#include <fcntl.h>

using namespace std;

#define Key_Up 72
#define Key_Down 80
#define Key_Left 75
#define Key_Right 77
#define Key_Enter 13
#define Key_Esc 27
#define _GRID 3
//**********************************************//
//      Por: Perez Porcel Juan Cruz             //
//      DNI: 41.185.616                         //
//      Para: Estructura de Datos y Algoritmos. //
//      hecho en Visual Studio 2022 (C++).      //
//**********************************************//
void InGame();
int checkWinner(string board[_GRID][_GRID], int availableMoves);
void Instructions();

int main()
{
    setlocale(LC_ALL, "spanish");

    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.FontWeight = FW_NORMAL;
    fontex.dwFontSize.X = 42;
    fontex.dwFontSize.Y = 42;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);

    char option;


    do {
        system("CLS");

        cout << "¿Desea jugar al Ta-Te-Ti? Y/n: ";
        SetConsoleTextAttribute(hOut, 14);
        cin >> option;

        option = toupper(option);

        switch (option) {
        case 'Y':
            SetConsoleTextAttribute(hOut, 7);
            InGame();
            break;
        case 'N':
            SetConsoleTextAttribute(hOut, 7);
            exit(0);
            break;
        default:
            system("CLS");
            SetConsoleTextAttribute(hOut, 12);
            cout << "Letra inválida, intentelo de nuevo.\n" << endl;
            SetConsoleTextAttribute(hOut, 7);
            system("pause");
            break;
        }
    } while (true);

    return 0;
}

void InGame() {
    int y = 1;
    int x = 1;
    int input;
    int currentPlayer = 1;
    int winner = 3;
    int movements = 9;

    const string player[2] = { {"X"}, {"O"} };

    string board[_GRID][_GRID] = { {"#", "#", "#"},
                                  { "#", "#", "#" },
                                  { "#", "#", "#" } };

    bool inGame = false;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


    while (!inGame) {
        system("CLS");
        Instructions();

        cout << "Es el turno del jugador ";
        SetConsoleTextAttribute(h, currentPlayer + 9);
        cout << currentPlayer;
        SetConsoleTextAttribute(h, 7);
        cout << ".\n" << endl;

#pragma region Bucle (Dibuja el tablero)

        for (int r = 0; r < _GRID; r++) {
            for (int c = 0; c < _GRID; c++) {

                c <= 0 ? printf("") : c >= _GRID ? printf("") : printf("|");

                if (r == y && c == x) {

                    if (board[r][c] == "#") {
                        SetConsoleTextAttribute(h, 7);
                        cout << "[";
                        SetConsoleTextAttribute(h, 14);

                        cout << player[currentPlayer - 1];
                        SetConsoleTextAttribute(h, 7);
                        cout << "]";
                    }
                    else {
                        SetConsoleTextAttribute(h, 12);
                        cout << "[" << board[r][c] << "]";
                        SetConsoleTextAttribute(h, 7);
                    }

                }
                else {
                    if (board[r][c] == "X") {
                        SetConsoleTextAttribute(h, 10);
                    }
                    else if (board[r][c] == "O") {
                        SetConsoleTextAttribute(h, 11);
                    }

                    cout << " " << board[r][c] << " ";
                    SetConsoleTextAttribute(h, 7);

                }
            }
            cout << endl;
        }
#pragma endregion

#pragma region Input

        input = _getch();

        if (input == Key_Up) {
            if (y > 0) {
                y--;
            }
        }
        else if (input == Key_Down) {
            if (y < 2) {
                y++;
            }
        }
        else if (input == Key_Right) {
            if (x < 2) {
                x++;
            }
        }
        else if (input == Key_Left) {
            if (x > 0) {
                x--;
            }
        }


        if (input == Key_Enter) {
            if (board[y][x] == "#") {

                board[y][x] = player[currentPlayer - 1];
                currentPlayer == 1 ? currentPlayer = 2 : currentPlayer = 1;
                y = 1;
                x = 1;

                movements--;
            }
        }
        else if (input == Key_Esc) {
            inGame = !inGame;
        }

#pragma endregion

#pragma region Condición de partida (win, lose, draw)

        winner = checkWinner(board, movements);

        if (winner == 0) {
            SetConsoleTextAttribute(h, 7);
            cout << "\nNo quedan movimientos disponibles, ";
            SetConsoleTextAttribute(h, 13);
            cout << "EMPATE";
            SetConsoleTextAttribute(h, 7);
            cout << "." << endl;

            inGame = !inGame;

        }
        else if (winner == 1) {

            SetConsoleTextAttribute(h, 7);
            cout << "\nEl ganador es el Player ";
            SetConsoleTextAttribute(h, 10);
            cout << "1";
            SetConsoleTextAttribute(h, 7);
            cout << "." << endl;

            inGame = !inGame;


        }
        else if (winner == 2) {

            SetConsoleTextAttribute(h, 7);
            cout << "\nEl ganador es el Player ";
            SetConsoleTextAttribute(h, 11);
            cout << "2";
            SetConsoleTextAttribute(h, 7);
            cout << "." << endl;

            inGame = !inGame;
        }
#pragma endregion
    }
    system("pause");

    main();
}

int checkWinner(string board[_GRID][_GRID], int availableMoves)
{
    int winner = 3;
    int moves = availableMoves;

    // cualquiera de las filas es igual
    for (int i = 0; i <= 2; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == "X")
        {
            winner = 1;
            return winner;
        }
    }
    for (int i = 0; i <= 2; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == "O")
        {
            winner = 2;
            return winner;
        }
    }

    // cualquiera de las columnas es igual
    for (int i = 0; i <= 2; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == "X")
        {
            winner = 1;
            return winner;
        }
    }
    for (int i = 0; i <= 2; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == "O")
        {
            winner = 2;
            return winner;
        }
    }

    // la primera diagonal es igual
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == "X")
    {
        winner = 1;
        return winner;
    }
    else if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == "O")
    {
        winner = 2;
        return winner;
    }

    // la segunda diagonal es igual
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == "X")
    {
        winner = 1;
        return winner;
    }
    else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == "O")
    {
        winner = 2;
        return winner;
    }
    if (moves == 0) {
        winner = 0;
        return winner;
    }

    return winner;
}

void Instructions() {

    printf("%c[4mControles:%c\n\n[0m", 27, 27);
    printf("       Arriba: %c\n", 24);
    printf("       Abajo: %c\n", 25);
    printf("       Derecha: %c\n", 26);
    printf("       Izquierda: <-\n"); //La flecha a la izquierda no funciona ni en Unicode, ni en Ascii. Ya que el 27 es el ESC en ascii.
    printf("       Poner: Enter %c\n\n", 31);
}