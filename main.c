#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>

#define MAX_COL 8 
#define MAX_ROW 8
#define RED   "\x1B[31m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

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
    UNDF = 9,
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
            int black_piece = board[i][j].piece.color == BLACK;

            if(black_piece) {
                switch (board[i][j].piece.type) {
                case NONE:
                    printf("|_ "); // empty space
                    break;
                case PAWN:
                    printf(RED "|P " RESET); // pawn
                    break;
                case BISHOP:
                    printf(RED "|B " RESET); // bishop
                    break;
                case KNIGHT:
                    printf(RED "|N " RESET); // knight
                    break;
                case ROOK:
                    printf(RED "|R " RESET); // rook
                    break;
                case QUEEN:
                    printf(RED "|Q " RESET); // queen
                    break;
                case KING:
                    printf(RED "|K " RESET); // king
                    break;
                default:
                    printf("|? "); // unknown piece
                }
            }
        else {
            switch (board[i][j].piece.type) {
                case NONE:
                    printf("|_ "); // empty space
                    break;
                case PAWN:
                    printf(YEL "|P " RESET); // pawn
                    break;
                case BISHOP:
                    printf(YEL "|B " RESET); // bishop
                    break;
                case KNIGHT:
                    printf(YEL "|N " RESET); // knight
                    break;
                case ROOK:
                    printf(YEL "|R " RESET); // rook
                    break;
                case QUEEN:
                    printf(YEL "|Q " RESET); // queen
                    break;
                case KING:
                    printf(YEL "|K " RESET); // king
                    break;
                default:
                    printf("|? "); // unknown piece
                }   
            }
        }
    printf("| %d\n", i+1); // print row label again
    }
    printf("\n   A  B  C  D  E  F  G  H\n"); // print column labels again
}

void printReverseBoard(chess_board board[][MAX_COL]) {
    printf("\n   A  B  C  D  E  F  G  H\n\n"); // print column labels
    for (int i = 0; i < MAX_ROW; i++) { 
        printf("%d ", i+1); // print row label
        for (int j = 0; j < MAX_COL; j++) {
            int black_piece = board[i][j].piece.color == BLACK;

            if(black_piece) {
                switch (board[i][j].piece.type) {
                case NONE:
                    printf("|_ "); // empty space
                    break;
                case PAWN:
                    printf(RED "|P " RESET); // pawn
                    break;
                case BISHOP:
                    printf(RED "|B " RESET); // bishop
                    break;
                case KNIGHT:
                    printf(RED "|N " RESET); // knight
                    break;
                case ROOK:
                    printf(RED "|R " RESET); // rook
                    break;
                case QUEEN:
                    printf(RED "|Q " RESET); // queen
                    break;
                case KING:
                    printf(RED "|K " RESET); // king
                    break;
                default:
                    printf("|? "); // unknown piece
                }
            }
        else {
            switch (board[i][j].piece.type) {
                case NONE:
                    printf("|_ "); // empty space
                    break;
                case PAWN:
                    printf(YEL "|P " RESET); // pawn
                    break;
                case BISHOP:
                    printf(YEL "|B " RESET); // bishop
                    break;
                case KNIGHT:
                    printf(YEL "|N " RESET); // knight
                    break;
                case ROOK:
                    printf(YEL "|R " RESET); // rook
                    break;
                case QUEEN:
                    printf(YEL "|Q " RESET); // queen
                    break;
                case KING:
                    printf(YEL "|K " RESET); // king
                    break;
                default:
                    printf("|? "); // unknown piece
                }   
            }
        }
    printf("| %d\n", i+1); // print row label again
    }
    printf("\n   A  B  C  D  E  F  G  H\n"); // print column labels again
}

void printCapturedPiece(chess_board board[][MAX_ROW], int row, int col) {
    char* type_str;

    switch(board[row][col].piece.type) {
        case PAWN:
            type_str = "Pawn";
            break;
        case ROOK:
            type_str = "Rook";
            break;
        case KNIGHT:
            type_str = "Knight";
            break;
        case BISHOP:
            type_str = "Bishop";
            break;
        case QUEEN:
            type_str = "Queen";
            break;
        case KING:
            type_str = "King";
            break;
        default:
            type_str = "Unknown piece type";
            break;
    }

    printf("\nYou capture a %s on coordinates: (%d,%d)\n", type_str, row, col);
}

void pawnMoves(chess_board board[][MAX_ROW], int col, int row) {
    char mov_col;
    int mov_row;
    int all_good = 0;

    do {
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

        printf("\nmov_col = %d mov_row = %d\n", mov_col, mov_row);

        int illegal_column = mov_col != col;
        int attack_column = mov_col == col+1 || mov_col == col-1;
        int piece_blocked = board[mov_row][mov_col].piece.type != NONE;
        int black_piece = board[row][col].piece.color == BLACK;

        int enemy_white = board[mov_row][mov_col].piece.color == WHITE;
        int enemy_black = board[mov_row][mov_col].piece.color == BLACK;

        if (black_piece) {

            int illegal_row_b = mov_row + 2 < row;
            int illegal_row_second_b = mov_row + 1 < row;
            int first_turn_b = row == 6;
            int legal_move_b = (mov_row < row) && ((row - mov_row == 2) || (row - mov_row == 1));
            int attack_row = mov_row == row-1;
            int can_attack = attack_column && attack_row && enemy_white;

            // Illegal moves for 1st turn
            if ((illegal_column || illegal_row_b && first_turn_b || !legal_move_b || piece_blocked) && !can_attack) {
                printf("\nCan not make that move\n");
            }
            // Illegal moves after 1st turn
            else if ((illegal_column || illegal_row_second_b && !first_turn_b || !legal_move_b || piece_blocked) && !can_attack) {
                printf("\nCan not make that move\n");
            }
            // Capturing logic
            else if (illegal_column && can_attack) {
                printCapturedPiece(board, mov_row, mov_col);
                board[mov_row][mov_col].piece.type = PAWN;
                board[mov_row][mov_col].piece.color = BLACK;
                board[row][col].piece.type = NONE;
                board[row][col].piece.color = UNDF;
                sleep(2);
                all_good = 1;
            }
            else {
                board[mov_row][mov_col].piece.type = PAWN;
                board[mov_row][mov_col].piece.color = BLACK;
                board[row][col].piece.type = NONE;
                board[row][col].piece.color = UNDF;
                all_good = 1;
            }
        }
        else {

            int illegal_row = mov_row > row + 2;
            int illegal_row_second = mov_row > row + 1;
            int first_turn = row == 1;
            int legal_move = (mov_row > row) && ((mov_row - row == 2) || (mov_row - row == 1));
            int attack_row = mov_row == row+1;
            int can_attack = attack_column && attack_row && enemy_black;

            // Illegal moves for 1st turn
            if ((illegal_column || illegal_row && first_turn || !legal_move || piece_blocked) && !can_attack) {
                printf("\nCan not make that move\n");
            }
            // Illegal moves after 1st turn
            else if ((illegal_column || illegal_row_second && !first_turn || !legal_move || piece_blocked) && !can_attack) {
                printf("\nCan not make that move\n");
            }
            // Capturing logic
            else if (illegal_column && can_attack) {
                printCapturedPiece(board, mov_row, mov_col);
                board[mov_row][mov_col].piece.type = PAWN;
                board[mov_row][mov_col].piece.color = WHITE;
                board[row][col].piece.type = NONE;
                board[row][col].piece.color = UNDF;
                sleep(2);
                all_good = 1;
            }
            else {
                board[mov_row][mov_col].piece.type = PAWN;
                board[mov_row][mov_col].piece.color = WHITE;
                board[row][col].piece.type = NONE;
                board[row][col].piece.color = UNDF;
                all_good = 1;
            }  
        }
    }
    while (all_good != 1);
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
            pawnMoves(board, col, row);
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

void choosePiece(chess_board board[][MAX_COL],char *col, int *row, int *turn) {

    int isGood = 0;
    do {
        printf("\nType coordinates of piece you pick: ");
        fflush(stdin);
        scanf("%c %d", col, row);
        *row -= 1; // We need to distract -1 from row value to get proper position on board, as it is indexed from 0
        
        // Calculate char into int(ASCII), to get proper position
        int correct_letter_A = *col >= 'A' && *col <= 'H';
        int correct_letter_a = *col >= 'a' && *col <= 'h';

        if (correct_letter_A) {
            *col -= 'A';
        }
        else if (correct_letter_a) {
            *col -= 'a';
        }
        else if (!correct_letter_A || !correct_letter_a){
            printf("\nPicked wrong coordinates\n");
            continue;
        }

        int black_piece = board[*row][*col].piece.color == BLACK;
        int white_piece = board[*row][*col].piece.color == WHITE;
        int empty_space = board[*row][*col].piece.type == NONE;
        int black_turn = *turn == 1;
        int white_turn = *turn == 0;

        if ((white_turn  && black_piece) || (black_turn && white_piece)) {
            printf("\nYou cannot pick opponent's pieces\n");
        }
        else if (empty_space) {
            printf("\nYou picked empty space\n");
            continue;
        }
        else {
            printf("\nColor: %d  || 1 - black 0 - white\n",board[*row][*col].piece.color);
            isGood = 1;
        }
    }
    while (isGood != 1);
}

int main()
{

    int currentTurn; 
    char cord_COL;
    int cord_ROW;

    // 8x8 board structure
    chess_board initialBoard[MAX_ROW][MAX_COL] = {
        { {ROOK, WHITE},   {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE},  {KING, WHITE},   {BISHOP, WHITE}, {KNIGHT, WHITE}, {ROOK, WHITE} },
        { {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE},   {PAWN, WHITE} },
        { {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF}  },
        { {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF}  },
        { {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF}  },
        { {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF},    {NONE, UNDF}  },
        { {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK},   {PAWN, BLACK} },
        { {ROOK, BLACK},   {KNIGHT, BLACK}, {BISHOP, BLACK}, {QUEEN, BLACK},  {KING, BLACK},   {BISHOP, BLACK}, {KNIGHT, BLACK}, {ROOK, BLACK} }
    };

    printf("\nWelcome in my chess game!\n");
    while (1)
    {  
        currentTurn = 0; //WHITE
        printf("\e[1;1H\e[2J");
        printBoard(initialBoard);
        choosePiece(initialBoard, &cord_COL, &cord_ROW, &currentTurn);
        printf("\ncord_Col = %d  Cord_ROW = %d\n", cord_COL, cord_ROW);
        pieceMoves(initialBoard,(int)cord_COL,cord_ROW);
        printf("\e[1;1H\e[2J");

        currentTurn = 1; //BLACK
        printReverseBoard(initialBoard);
        choosePiece(initialBoard, &cord_COL, &cord_ROW, &currentTurn);
        printf("\ncord_Col = %d  Cord_ROW = %d\n", cord_COL, cord_ROW);
        pieceMoves(initialBoard,(int)cord_COL,cord_ROW);
    }
}
