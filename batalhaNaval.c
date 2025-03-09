#include <stdio.h>
#include <string.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.
// Repositório oficial: https://github.com/Cursos-TI/desafio-batalha-naval-cristianojcruzzz

#define SIZE 10
#define WATER '~'
#define SHIP 'S'
#define AFFECTED 'x'
#define DEFAULT_SHIP_SIZE 2

void initBoard(char board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = WATER;
        }
    }
}

void showBoard(char board[SIZE][SIZE])
{
    /**
     * Gera a primeira linha `header`
     *   A B C D E F G H I J ... T
     * | ----------------------------
     */
    printf("     ");
    for (int c = 0; c < SIZE; c++)
    {
        // printf("%c ", 'A' + c);
        printf("%d ", c + 1);
    }
    printf("\n");

    printf("   | ");
    for (int c = 0; c < (SIZE * 2) - 1; c++)
    {
        printf("-");
    }
    printf("\n");

    /**
     * Gera as linhas do tabuleiro
     * 1 |
     * 2 |
     * 3 |
     * 4 |
     * E assim por diante
     */
    for (int i = 0; i < SIZE; i++)
    {
        printf("%2d | ", i + 1);
        for (int j = 0; j < SIZE; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void placeVerticalShip(char board[SIZE][SIZE], int row, int column, int size)
{
    for (int i = 0; i < size; i++)
    {
        board[row + i][column] = SHIP;
    }
}

void placeHorizontalShip(char board[SIZE][SIZE], int row, int column, int size)
{
    for (int c = 0; c < size; c++)
    {
        board[row][column + c] = SHIP;
    }
}

void placeDiagonalShip(char board[SIZE][SIZE], int row, int col, int size, const char *direction)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(direction, "right-down") == 0)
        {
            board[row + i][col + i] = SHIP;
        }

        if (strcmp(direction, "right-up") == 0)
        {
            board[row - i][col + i] = SHIP;
        }

        if (strcmp(direction, "left-down") == 0)
        {
            board[row + i][col - i] = SHIP;
        }

        if (strcmp(direction, "left-up") == 0)
        {
            board[row - i][col - i] = SHIP;
        }
    }
}

void applyOctahedron(char board[SIZE][SIZE], int row, int col)
{
    // a partir do meio, cria o octaedro
    board[row][col] = AFFECTED;

    // cria para a direita/esquerda
    board[row][col - 1] = AFFECTED;
    board[row][col + 1] = AFFECTED;

    // cria para baixo/cima
    board[row - 1][col] = AFFECTED;
    board[row + 1][col] = AFFECTED;
}

void applyCross(char board[SIZE][SIZE], int row, int col)
{
    // Define o ponto central
    board[row][col] = AFFECTED;

    // Expande para os lados
    for (int i = 1; i <= 2; i++)
    {
        board[row][col - i] = AFFECTED; // Esquerda
        board[row][col + i] = AFFECTED; // Direita
    }

    // Expande para cima e para baixo
    board[row - 1][col] = AFFECTED; // Cima
    board[row + 1][col] = AFFECTED; // Baixo
}

void applyCone(char board[SIZE][SIZE], int row, int col)
{
    // Define o ponto central
    board[row][col] = AFFECTED;

    // Expande para cima e para baixo
    board[row - 1][col] = AFFECTED; // Cima
    board[row + 1][col] = AFFECTED; // Baixo

    // cria para a direita/esquerda
    board[row][col - 1] = AFFECTED;
    board[row][col + 1] = AFFECTED;

    // cria para a direita/esquerda ultima linha
    for (int i = 1; i <= 2; i++)
    {
        board[row + 1][col - i] = AFFECTED; // Esquerda
        board[row + 1][col + i] = AFFECTED; // Direita
    }
}

int main()
{

    /**
     * Monta uma matrix 10 x 10
     */
    char tabuleiro[SIZE][SIZE];

    /**
     * Inicia o tabuleiro
     */
    initBoard(tabuleiro);

    // ---------------------------------------------------------------------
    // Nível Novato - Posicionamento dos Navios
    // Posiciona os navios na horizontal e vertical
    // ---------------------------------------------------------------------
    placeVerticalShip(tabuleiro, 0, 4, DEFAULT_SHIP_SIZE);
    placeHorizontalShip(tabuleiro, 7, 6, DEFAULT_SHIP_SIZE);

    // ---------------------------------------------------------------------
    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // ---------------------------------------------------------------------
    // placeDiagonalShip(tabuleiro, 7, 1, DEFAULT_SHIP_SIZE, "left-up");
    // placeDiagonalShip(tabuleiro, 4, 4, DEFAULT_SHIP_SIZE, "right-up");
    placeDiagonalShip(tabuleiro, 0, 8, DEFAULT_SHIP_SIZE, "left-down");
    placeDiagonalShip(tabuleiro, 4, 0, DEFAULT_SHIP_SIZE, "right-down");

    // ---------------------------------------------------------------------
    // Nível Mestre - Habilidades Especiais com Matrizes
    // Posiciona as habilidades especiais
    // ---------------------------------------------------------------------
    applyOctahedron(tabuleiro, 1, 1);
    applyCross(tabuleiro, 8, 2);
    applyCone(tabuleiro, 4, 7);

    /**
     * Mostra o tabuleiro atualizado
     */
    showBoard(tabuleiro);

    return 0;
}
