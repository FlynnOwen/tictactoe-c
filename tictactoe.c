#include <stdio.h>
struct counter
{
    int row;
    int column;
};

int board[3][3] = {
    {0, 0, 0},
    {0, 0 ,0},
    {0 ,0 ,0}
};

struct counter myCounter;
int playerTurn = 1;
int i, j;
_Bool gameOver = 0;

struct counter chooseCounterPosition() {
    int row = -1;
    int column = -1;

    while (row < 1 || row > 3) {
        printf("Input a row to place counter:\n");
        scanf("%d", &row);

        if (row < 1 || row > 3) {
            printf("row must be 1 <= row <= 3!\n");
        }
    }

    while (column < 1 || column > 3) {
        printf("Input a column to place counter:\n");
        scanf("%d", &column);

        if (column < 1 || column > 3) {
            printf("column must be 1 <= column <= 3!\n");
        }
    }

    if (board[row - 1][column - 1] != 0){
        printf("row %i, column %i is taken by player %i!\n", row, column, board[row - 1][column - 1]);
        return chooseCounterPosition();
    }

    struct counter myCounter = {row - 1, column - 1};

    return myCounter;
}

void placeCounter(int playerTurn, struct counter myCounter) {
    if (playerTurn == 1) {
        board[myCounter.row][myCounter.column] = 1;
    }

    else if (playerTurn == 2) {
        board[myCounter.row][myCounter.column] = 2;
    }
}

void printBoard(playerTurn) {
    for (i=0; i < 3; i++){
        for(j=0; j<3; j++){
            printf("%i ", board[i][j]);
        }
        printf("\n");
    }

    printf("Player %i's turn!\n", playerTurn);
}

_Bool checkGameOver() {
    for (i=0; i < 3; i++){
        for(j=0; j<3; j++){
            if (board[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    while (!gameOver){
        printBoard(playerTurn);
        myCounter = chooseCounterPosition();
        placeCounter(playerTurn, myCounter);

        if (playerTurn == 1) {
            playerTurn = 2;
        }

        else {
            playerTurn = 1;
        }

        gameOver = checkGameOver();
    }

    printf("Game Over!\n");

    return 0;
}