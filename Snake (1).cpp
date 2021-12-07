#include "Snake.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
using namespace std;

bool gameOver, lateGame, endGame;
const int width = 40; //map dimensions
const int height = 20;
int nTail, score;
enum eDirection { STOP, LEFT, RIGHT, UP, DOWN };
eDirection dir;
Snake tail[100], head;
Fruit fruit, fruit2, fruit3, fruit4, fruit5, fruit6, fruit7, fruit8, fruit9;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Setup() {
    gameOver = false;
    lateGame = false;
    endGame = false;
    dir = STOP;
    srand(time(NULL));
    head.x = width / 2; //to place the snake in the middle by dividing the width by 2
    head.y = height / 2;
    fruit.x = rand() % width;
    fruit.y = rand() % height;
    fruit2.x = rand() % width;
    fruit2.y = rand() % height;
    score = 0;
}

void Draw() {
    system("cls"); //clears the screen and produces a lot of flickering.
    for (int i = 0; i < width + 2; i++)
        cout << "_";
    cout << "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == head.y && j == head.x)
                printf("\x1B[32mO\033[0m");
            else if (i == fruit.y && j == fruit.x)
                printf("\x1B[31mQ\033[0m");
            else if (i == fruit2.y && j == fruit2.x)
                printf("\x1B[33mG\033[0m");
            else if (i == fruit3.y && j == fruit3.x)
                printf("\x1B[34mU\033[0m");
            else if (i == fruit4.y && j == fruit4.x)
                printf("\x1B[35mV\033[0m");
            else if (i == fruit5.y && j == fruit5.x)
                printf("\x1B[36mX\033[0m");
            else if (i == fruit6.y && j == fruit6.x)
                printf("\x1B[91mZ\033[0m");
            else if (i == fruit7.y && j == fruit7.x)
                printf("\x1B[93mA\033[0m");
            else if (i == fruit8.y && j == fruit8.x)
                printf("\x1B[94mB\033[0m");
            else if (i == fruit9.y && j == fruit9.x)
                printf("\x1B[96mC\033[0m");
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tail[k].x == j && tail[k].y == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << "\n";
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << "\n";
    cout << "Score: " << score << "\n";
    if (nTail > 5 && lateGame) {
        cout << "Oh, you're very good at getting the fruit, let's add some more!\n";
    }
    if (nTail > 20 && endGame) {
        cout << "Oh my- HOW ABOUT SOME MORE FRUIT? CAREFUL NOT TO EAT YOUR TAIL!\n";
    }
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tail[0].x;
    int prevY = tail[0].y;
    int prev2X, prev2Y;
    tail[0].x = head.x;
    tail[0].y = head.y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tail[i].x;
        prev2Y = tail[i].y;
        tail[i].x = prevX;
        tail[i].y = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        head.x--;
        break;
    case RIGHT:
        head.x++;
        break;
    case UP:
        head.y--;
        break;
    case DOWN:
        head.y++;
        break;
    default:
        break;
    }
    /* this is if the game should end when the snake touches the edges of the map
    if (x > width || x < 0 || y > height || y < 0) {
        gameOver = true;
    }*/
    if (head.x >= width) head.x = 0; else if (head.x < 0) head.x = width - 1;
    if (head.y >= height) head.y = 0; else if (head.y < 0) head.y = height - 1;
    for (int i = 0; i < nTail; i++) {
        if (tail[i].x == head.x && tail[i].y == head.y) {
            cout << "You ate your tail :(\n";
            gameOver = true;
        }
    }
    if (head.x == fruit.x && head.y == fruit.y) {
        score += 10;
        fruit.x = rand() % width;
        fruit.y = rand() % height;
        nTail++;
    }
    if (head.x == fruit2.x && head.y == fruit2.y) {
        score += 10;
        fruit2.x = rand() % width;
        fruit2.y = rand() % height;
        nTail++;
    }
    if (nTail > 5) {
        if (!lateGame) {
            fruit3.x = rand() % width;
            fruit3.y = rand() % height;
            fruit4.x = rand() % width;
            fruit4.y = rand() % height;
            fruit5.x = rand() % width;
            fruit5.y = rand() % height;
            fruit6.x = rand() % width;
            fruit6.y = rand() % height;
            lateGame = true;
        }
        if (nTail > 20) {
            if (!endGame) {
                fruit7.x = rand() % width;
                fruit7.y = rand() % height;
                fruit8.x = rand() % width;
                fruit8.y = rand() % height;
                fruit9.x = rand() % width;
                fruit9.y = rand() % height;
                endGame = true;
            }
            if (head.x == fruit7.x && head.y == fruit7.y) {
                score += 10;
                fruit7.x = rand() % width;
                fruit7.y = rand() % height;
                nTail++;
            }
            if (head.x == fruit8.x && head.y == fruit8.y) {
                score += 10;
                fruit8.x = rand() % width;
                fruit8.y = rand() % height;
                nTail++;
            }
            if (head.x == fruit9.x && head.y == fruit9.y) {
                score += 10;
                fruit9.x = rand() % width;
                fruit9.y = rand() % height;
                nTail++;
            }
        }
        if (head.x == fruit3.x && head.y == fruit3.y) {
            score += 10;
            fruit3.x = rand() % width;
            fruit3.y = rand() % height;
            nTail++;
        }
        if (head.x == fruit4.x && head.y == fruit4.y) {
            score += 10;
            fruit4.x = rand() % width;
            fruit4.y = rand() % height;
            nTail++;
        }
        if (head.x == fruit5.x && head.y == fruit5.y) {
            score += 10;
            fruit5.x = rand() % width;
            fruit5.y = rand() % height;
            nTail++;
        }
        if (head.x == fruit6.x && head.y == fruit6.y) {
            score += 10;
            fruit6.x = rand() % width;
            fruit6.y = rand() % height;
            nTail++;
        }
    }
}