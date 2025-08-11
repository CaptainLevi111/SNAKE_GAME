# SNAKE_GAME
Game Overview
A classic Snake game implementation for Windows console with smooth movement and score tracking.

Features
Smooth snake movement with adjustable speed (increases with score)

Score system (10 points per fruit)

Screen wrapping - snake can go through walls

Self-collision detection - game ends if snake hits itself

Clean console display with borders

Keyboard controls (WASD or arrow keys)

Visual elements:

Snake head (O)

Snake body (o)

Fruit (F)

Requirements
Windows OS

C compiler (MSVC, MinGW, or compatible)

How to Run
Compile the program:
gcc snakegame.c -o snakegame.exe
Run the executable:
snakegame.exe
🎮 Controls
W or Up Arrow: Move Up

A or Left Arrow: Move Left

S or Down Arrow: Move Down

D or Right Arrow: Move Right

X: Exit Game

🎯 Game Rules
Control the snake to eat fruits (F)

Each fruit increases:

Your score by 10 points

Snake length by 1 segment

Game speed slightly

Avoid hitting your own tail

Game ends if snake collides with itself

Tips
The snake moves faster as your score increases

You can go through walls (screen wraps around)

Plan your moves to avoid trapping yourself

Try to collect fruits in sequence for better control

Display Information
Top border shows game title

Play area is bordered with # characters

Bottom shows current score

Game over message appears when you lose

Enjoy the game! 🎉
