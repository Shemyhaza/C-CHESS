#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_COL 8 
#define MAX_ROW 8

enum Type {

    NONE = 0,
    PAWN = 1,
    BISHOP = 2,
    KNIGHT = 3,
    ROOK = 4,
    QUEEN = 5,
    KING = 6,
};

enum Color {

    WHITE = 0,
    BLACK = 1,
};

typedef struct Piece {

    enum Type type;
    enum Color color;
}chess_piece;

typedef struct Board {

    chess_piece piece;
}chess_board;

void printBoard(chess_board board[][MAX_ROW]) {

    for (int i = 0; i < MAX_COL; i++) {
        for (int j = 0; j < MAX_ROW; j++) {
            switch (board[i][j].piece.type) {
                case NONE:
                    printf(" . ");
                    break;
                case PAWN:
                    printf(" P ");
                    break;
                case BISHOP:
                    printf(" B ");
                    break;
                case KNIGHT:
                    printf(" N ");
                    break;
                case ROOK:
                    printf(" R ");
                    break;
                case QUEEN:
                    printf(" Q ");
                    break;
                case KING:
                    printf(" K ");
                    break;
                default:
                    printf(" ? ");
            }
        }
        printf("\n");
    }
}

void pawnMoves();
void rookMoves();
void bishopMoves();
void knightMoves();
void queenMoves();
void kingMoves();


void pieceMoves(chess_board board[][MAX_ROW],int col, int row) {

    // TODO zmienic kolejnosc tak, zeby A1 wybieralo kolumne A i szlo rzedem do gory, a nie na odwrot

    switch (board[col][row].piece.type) {
        case NONE:
            printf("You clicked on empty space (%d,%d)\n", col, row);
            break;
        case PAWN:
            printf("Picked pawn on position (%d,%d)\n", col, row);
            //pawnMoves();
            break;
        case BISHOP:
            printf("Picked bishop on position (%d,%d)\n", col, row);
            //bishopMoves();
            break;
        case KNIGHT:
            printf("Picked knight on position (%d,%d)\n", col, row);
            //knightMoves();
            break;
        case ROOK:
            printf("Picked rook on position (%d,%d)\n", col, row);
            //rookMoves();
            break;
        case QUEEN:
            printf("Picked queen on position (%d,%d)\n", col, row);
            //queenMoves();
            break;
        case KING:
            printf("Picked king on position (%d,%d)\n", col, row);
            //kingMoves();
            break;
        default:
            break;
    }
}

int main()
{

    int currentTurn = 0;
    char cord_COL;
    int cord_ROW;

    // 8x8 board structure
    chess_board initialBoard[MAX_COL][MAX_ROW] = {
        { {ROOK, WHITE},   {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE},  {KING, WHITE},   {BISHOP, WHITE}, {KNIGHT, WHITE}, {ROOK, WHITE} },
        { {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE} },
        { {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE}  },
        { {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE}  },
        { {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE}  },
        { {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE},    {NONE, NONE}  },
        { {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK} },
        { {ROOK, BLACK},   {KNIGHT, BLACK}, {BISHOP, BLACK}, {QUEEN, BLACK},  {KING, BLACK},   {BISHOP, BLACK}, {KNIGHT, BLACK}, {ROOK, BLACK} }
    };

    printBoard(initialBoard);
    printf("Type coordinates of piece you pick: ");
    scanf("%c %d", &cord_COL, &cord_ROW);
    if ((int)cord_COL >= 65 && (int)cord_COL <= 72) {
        cord_COL -= 65;
    }
    else {
        cord_COL -= 97;
    }
    pieceMoves(initialBoard,(int)cord_COL,cord_ROW);
    // printf("\033[2J"); // clears the screen
}