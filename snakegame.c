#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>  // For _kbhit() and _getch()
#include <time.h>

#define HEIGHT 20
#define WIDTH 60

enum Direction {
    UP, 
    DOWN,
    LEFT,
    RIGHT,
    STOP
};

enum Direction dir;
int score;
int fruit_x, fruit_y;
int head_x, head_y;
int tail_length;
int tail_x[100];
int tail_y[100];

void setup();
void draw();
void input();
void game_play();
void clear_screen();
void set_cursor_position(int x, int y);
void hide_cursor();

HANDLE hConsole;

int main() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand((unsigned)time(NULL));
    setup();
    hide_cursor();
    
    while (1) {
        draw();
        input();
        game_play();
        int sleep_time = 300 / (score != 0 ? score / 10 + 1 : 1);
        Sleep(sleep_time);
    }
    
    return 0;
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch)
        {
        case 'a':
        case 'A':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 's':
        case 'S':
            if (dir != UP) dir = DOWN;
            break;
        case 'd':
        case 'D':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
        case 'W':
            if (dir != DOWN) dir = UP;
            break;
        case 'x':
        case 'X':
            exit(0);
            break;
        default:
            break;
        }
    }
}

void game_play() {
    // Update tail positions
    for (int i = tail_length - 1; i > 0; i--) {
        tail_x[i] = tail_x[i-1];
        tail_y[i] = tail_y[i-1];
    }
    if (tail_length > 0) {
        tail_x[0] = head_x;
        tail_y[0] = head_y;
    }

    // Move head
    switch (dir)
    {
    case UP:
        head_y--;
        break;
    case DOWN:
        head_y++;
        break;
    case LEFT:
        head_x--;
        break;
    case RIGHT:
        head_x++;
        break;
    case STOP:
        // do nothing
        break;
    }

    // Screen wrapping
    if (head_x < 0) {
        head_x = WIDTH - 1;
    } else if (head_x >= WIDTH) {
        head_x = 0;
    }

    if (head_y < 0) {
        head_y = HEIGHT - 1;
    } else if (head_y >= HEIGHT) {
        head_y = 0;
    }

    // Check if snake hit itself
    for (int i = 0; i < tail_length; i++) {
        if (tail_x[i] == head_x && tail_y[i] == head_y) {
            system("cls");
            printf("\nYou have hit your tail. GAME OVER !!!\n");
            printf("Final Score: %d\n", score);
            exit(0);
        }
    }

    // Check if snake ate fruit
    if (head_x == fruit_x && head_y == fruit_y) {
        score += 10;
        tail_length++;
        fruit_x = rand() % WIDTH;
        fruit_y = rand() % HEIGHT;
    }
}

void setup() {
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
    dir = STOP;
    score = 0;
    tail_length = 0;
}

void draw() {
    clear_screen();
    
    // Draw top border
    set_cursor_position(0, 0);
    printf("\t\tWelcome to The Snake Game!!!");
    set_cursor_position(0, 1);
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }

    // Draw game area
    for (int i = 0; i < HEIGHT; i++) {
        set_cursor_position(0, i + 2);
        printf("#");
        for (int j = 0; j < WIDTH; j++) {
            if (i == head_y && j == head_x) {
                printf("O");
            } else if (i == fruit_y && j == fruit_x) {
                printf("F");
            } else {
                int tail_found = 0;
                for (int k = 0; k < tail_length; k++) {
                    if (tail_x[k] == j && tail_y[k] == i) {
                        printf("o");
                        tail_found = 1;
                        break;
                    }
                }
                if (!tail_found) {
                    printf(" ");
                }
            }
        }
        printf("#");
    }

    // Draw bottom border
    set_cursor_position(0, HEIGHT + 2);
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    
    // Draw score
    set_cursor_position(0, HEIGHT + 3);
    printf("Score: %d\n", score);
}

void clear_screen() {
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    SetConsoleCursorPosition(hConsole, coord);
}

void set_cursor_position(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}