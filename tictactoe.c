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

int i, j;
struct counter myCounter;
int playerTurn = 0;
_Bool gameOver = 0;
_Bool winCondition = 0;
int streak = 0;

struct counter chooseCounterPosition() {
    // Asks user where on the board they would like to place a counter
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
    // Places chosen counter on the board
    if (playerTurn == 1) {
        board[myCounter.row][myCounter.column] = 1;
    }

    else if (playerTurn == 2) {
        board[myCounter.row][myCounter.column] = 2;
    }
}

void printBoard(playerTurn) {
    // Prints the current state of the board and the current players turn
    for (i=0; i < 3; i++){
        for(j=0; j<3; j++){
            printf("%i ", board[i][j]);
        }
        printf("\n");
    }

    printf("Player %i's turn!\n", playerTurn);
}

_Bool checkGameOver() {
    // Checks whether all possible moves have been made
    for (i=0; i < 3; i++){
        for(j=0; j<3; j++){
            if (board[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

_Bool checkWinCondition(playerTurn, i, j, streak) {
    // Checks whether a player has 3 counters in a row
    // Currently uses a recursive (unoptimized) version. Add in memoization to make it a dynamic programming approach
    if (i > 2 || j > 2) {
        if (streak == 3) {
            return 1;
        }
        else {
            return 0;
        }
    }

    else if (board[i][j] == playerTurn) {
        return (checkWinCondition(playerTurn, i + 1, j, streak + 1) || checkWinCondition(playerTurn, i , j + 1, streak + 1) || checkWinCondition(playerTurn, i + 1, j + 1, streak + 1));
    }

    else {
        return (checkWinCondition(playerTurn, i + 1, j, 0) || checkWinCondition(playerTurn, i , j + 1, 0) || checkWinCondition(playerTurn, i + 1, j + 1, 0));
    }

}

int main() {
    while (!gameOver && !winCondition) {

        if (playerTurn == 1) {
            playerTurn = 2;
        }

        else {
            playerTurn = 1;
        }

        printBoard(playerTurn);
        myCounter = chooseCounterPosition();
        placeCounter(playerTurn, myCounter);

        gameOver = checkGameOver();
        winCondition = checkWinCondition(playerTurn, 0, 0, 0);

    }

    if (winCondition) {
        printf("Player %i wins!\n", playerTurn);
    }
    printf("Game Over!\n");

    return 0;
}