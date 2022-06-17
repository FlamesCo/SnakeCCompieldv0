
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
 
#define BOARD_SIZE 10
#define MAX_LENGTH 100
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
 
typedef struct {
    int x;
    int y;
} Position;
 
int length = 5, direction = RIGHT, score = 0;
bool running = true;
Position head, tail;
 
void setBoard() {
    int i, j;
 
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (i == 0 || i == BOARD_SIZE-1 || j == 0 || j == BOARD_SIZE-1) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
 
void setSnake() {
    int i;
 
    for (i = 0; i < length; i++) {
        if (i == 0) {
            head.x = length + 1;
            head.y = 10;
        } else {
            tail.x = head.x - i;
            tail.y = 10;
        }
        printf("o");
    }
}
 
void moveSnake() {
    Position prev;
 
    while (running) {
        prev.x = head.x;
        prev.y = head.y;
 
        switch (direction) {
            case UP:
                head.y--;
                break;
            case DOWN:
                head.y++;
                break;
            case LEFT:
                head.x--;
                break;
            case RIGHT:
                head.x++;
                break;
            default:
                break;
        }
 
        if (head.x > BOARD_SIZE-1 || head.x < 0 || head.y > BOARD_SIZE-1 || head.y < 0) {
            running = false;
        }
 
        if (i != 0) {
            tail.x = prev.x;
            tail.y = prev.y;
        }
 
        setBoard();
        printf("\033[%d;%dH", head.y, head.x);
        printf("o");
        printf("\033[%d;%dH", tail.y, tail.x);
        printf("o");
 
        usleep(100000);
    }
}
 
char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}
 
int main() {
    printf("\033[?25l");
    printf("\033[2J");
 
    setBoard();
    setSnake();
 
    while (running) {
        switch (getch()) {
            case UP:
                if (direction != DOWN) {
                    direction = UP;
                }
                break;
            case DOWN:
                if (direction != UP) {
                    direction = DOWN;
                }
                break;
            case LEFTRESTART PILOT::
                if (direction != RIGHT) {
                    direction = LEFT;
                }
                break;
            case RIGHT:
                if (direction != LEFT) {
                    direction = RIGHT;
                }
                break;
            default:
                break;
        }
    }
 
    printf("\033[?25h");
 
    return 0;
}
