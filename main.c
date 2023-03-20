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
} chess_piece;

typedef struct Board {
    chess_piece piece;
} chess_board;

// Function to print the chess board
void printBoard(chess_board board[][MAX_COL]) {
    printf("\n   A  B  C  D  E  F  G  H\n\n"); // print column labels
    for (int i = MAX_ROW - 1; i >= 0; i--) { // iterate over rows in reverse order, to get it properly sorted
        printf("%d ", i+1); // print row label
        for (int j = 0; j < MAX_COL; j++) {
            switch (board[i][j].piece.type) {
                case NONE:
                    printf("|_ "); // empty space
                    break;
                case PAWN:
                    printf("|P "); // pawn
                    break;
                case BISHOP:
                    printf("|B "); // bishop
                    break;
                case KNIGHT:
                    printf("|N "); // knight
                    break;
                case ROOK:
                    printf("|R "); // rook
                    break;
                case QUEEN:
                    printf("|Q "); // queen
                    break;
                case KING:
                    printf("|K "); // king
                    break;
                default:
                    printf("|? "); // unknown piece
            }
        }
        printf("| %d\n", i+1); // print row label again
    }
    printf("\n   A  B  C  D  E  F  G  H\n"); // print column labels again
}


void pawnMoves(chess_board board[][MAX_ROW], int col, int row) {
    char mov_col;
    int mov_row;
    printf("\nType where you want to move: ");
    fflush(stdin);
    scanf("%c %d",&mov_col, &mov_row);

    if (mov_col >= 'A' && mov_col <= 'H') {
        mov_col -= 'A';
    }
    else {
        mov_col -= 'a';
    }
    mov_row -= 1;

    printf("mov_col = %d mov_row = %d", mov_col, mov_row);
    int illegal_column = mov_col != col;
    int illegal_row = mov_row > row + 2;
    int illegal_row_second = mov_row > row + 1;
    int first_turn = row == 1;
    if (illegal_column || illegal_row && first_turn) {
        printf("\nNie mozna wykonac ruchu\n");
    }
    else if (illegal_column || illegal_row_second && !first_turn) {
        printf("\nNie mozna wykonac ruchu\n");
    }
    else {
        board[mov_row][mov_col].piece.type = PAWN;
        board[row][col].piece.type = NONE;
    }

}

void rookMoves();

void bishopMoves();

void knightMoves();

void queenMoves();

void kingMoves();


// Function to handle piece moves
void pieceMoves(chess_board board[][MAX_COL], int col, int row) {
    int col_letter = col+65;
    int row_correct = row+1;
    switch (board[row][col].piece.type) {
        case NONE:
            printf("\nYou clicked on empty space (%c,%d)\n", col_letter, row_correct);
            break;
        case PAWN:
            printf("\nPicked pawn on position (%c,%d)\n", col_letter, row_correct);
            //pawnMoves();
            break;
        case BISHOP:
            printf("\nPicked bishop on position (%c,%d)\n", col_letter, row_correct);
            //bishopMoves();
            break;
        case KNIGHT:
            printf("\nPicked knight on position (%c,%d)\n", col_letter, row_correct);
            //knightMoves();
            break;
        case ROOK:
            printf("\nPicked rook on position (%c,%d)\n", col_letter, row_correct);
            //rookMoves();
            break;
        case QUEEN:
            printf("\nPicked queen on position (%c,%d)\n", col_letter, row_correct);
            //queenMoves();
            break;
        case KING:
            printf("\nPicked king on position (%c,%d)\n", col_letter, row_correct);
            //kingMoves();
            break;
        default:
            break;
    }
}

void choosePiece(char *col, int *row) {

    printf("\nType coordinates of piece you pick: ");
    fflush(stdin);
    scanf("%c %d", col, row);

    *row -= 1; // We need to distract -1 from row value to get proper position on board, as it is indexed from 0

    // Calculate char into int(ASCII), to get proper position
    if (*col >= 'A' && *col <= 'H') {
        *col -= 'A';
    }
    else {
        *col -= 'a';
    }
}

int main()
{

    int currentTurn = 0;
    char cord_COL;
    int cord_ROW;

    // 8x8 board structure
    chess_board initialBoard[MAX_ROW][MAX_COL] = {
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
    choosePiece(&cord_COL, &cord_ROW);
    printf("cord_Col = %d  Cord_ROW = %d", cord_COL, cord_ROW);
    pieceMoves(initialBoard,(int)cord_COL,cord_ROW);
    pawnMoves(initialBoard,(int)cord_COL,cord_ROW);
    printf("\e[1;1H\e[2J");
    printBoard(initialBoard);

    choosePiece(&cord_COL, &cord_ROW);
    printf("cord_Col = %d  Cord_ROW = %d", cord_COL, cord_ROW);
    pieceMoves(initialBoard,(int)cord_COL,cord_ROW);
    pawnMoves(initialBoard,(int)cord_COL,cord_ROW);
    printf("\e[1;1H\e[2J");
    printBoard(initialBoard);
}
