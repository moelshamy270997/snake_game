#include <iostream>
#include <conio.h>
#include <math.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <iomanip> 
#include <sstream>
#include "Snake_Game.h"

using namespace std;

Snake_Game::Snake_Game()
{
    width = 30;
    height = 20;

    setWindow();
}

void Snake_Game::setGame()
{
    score = 0;
    snake_x = width / 2;
    snake_y = height / 2;
    tail_length = 0;
    game_over = false;
    dir = STOP;

    setFruit();
    getBestScore();
}

void Snake_Game::play()
{
    start:
        setGame();
        mainMinu();
        while (!game_over)
        {
            drawMap();
            getKey();
            move();

            Sleep(150);
        }
        saveBestScore();
        if (playAgain())
            goto start;
}

void Snake_Game::instructions()
{
    cout << "\nUse the 'w', 'W' or 'Upwards Arrow'         key to go UP."
         << "\nUse the 'a', 'A' or 'Downwards Arrow'       key to turn LEFT."
         << "\nUse the 's', 'S' or 'Rightwards Arrow'      key to go DOWN."
         << "\nUse the 'd', 'D' or 'Leftwards Arrow'       key to turn RIGHT."
         << "\n\nPress the 'q' or 'Q' key any time during the game to EXIT."
         << "\nDO NOT eat your own tail or you will obviously also LOSE!";
}

void Snake_Game::mainMinu()
{
    system("cls");
    cout << "Welcome to Snake Game!\n";
    instructions();
    cout << "\n\nBest Score: " << best_score << endl;
    cout << "Press any key to start..." << endl;
    _getch();
}

void Snake_Game::setWindow()
{
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, 200, 100, 800, 500, true);
}

void Snake_Game::setFruit()
{
    fruit_x = (rand() % (width - 2)) + 1;
    fruit_y = (rand() % (height - 2)) + 1;
}

void Snake_Game::drawMap()
{
    system("cls");

    for (int i = 0; i < width; i++)
        cout << '#';
    cout << endl;

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
                cout << '#';
            else if (i == snake_y && j == snake_x)
                cout << 'O';
            else if (i == fruit_y && j == fruit_x)
                cout << 'F';
            else
            {
                bool is_printed = false;
                for (int k = 0; k < tail_length; k++)
                    if (tail_x[k] == j && tail_y[k] == i)
                    {
                        cout << 'o';
                        is_printed = true;
                    }
                if (!is_printed)
                    cout << ' ';
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++)
        cout << '#';
    cout << endl;

    cout << "\nScore = " << score << endl;
}

void Snake_Game::getKey()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a': case 'A': case KEY_LEFT:
                if (dir != RIGHT) dir = LEFT;
                break;

            case 'd': case 'D': case KEY_RIGHT:
                if (dir != LEFT) dir = RIGHT;
                break;

            case 'w': case 'W': case KEY_UP:
                if (dir != DOWN) dir = UP;
                break;

            case 's': case 'S': case KEY_DOWN:
                if (dir != UP) dir = DOWN;
                break;

            case 'q': case 'Q':
                game_over = true;
                break;
        }
    }
}

void Snake_Game::move()
{
    int prev_x = tail_x[0];
    int prev_y = tail_y[0];

    tail_x[0] = snake_x;
    tail_y[0] = snake_y;

    for (int i = 1; i < tail_length; i++)
    {
        swap(tail_x[i], prev_x);
        swap(tail_y[i], prev_y);
    }

    switch (dir)
    {
        case LEFT:
            snake_x--;
            break;
        case RIGHT:
            snake_x++;
            break;
        case UP:
            snake_y--;
            break;
        case DOWN:
            snake_y++;
            break;
    }

    if (snake_x == width - 1) snake_x = 1;
    if (snake_x == 0) snake_x = width - 2;
    if (snake_y == height - 1) snake_y = 1;
    if (snake_y == 0) snake_y = height - 2;

    for (int i = 0; i < tail_length; i++)
        if (tail_x[i] == snake_x && tail_y[i] == snake_y)
            game_over = true;

    if (snake_x == fruit_x && snake_y == fruit_y)
    {
        score += 5;
        setFruit();
        tail_length++;
    }

}

bool Snake_Game::playAgain()
{
    system("cls");
    char ch;
    cout << "Your score is : " << score << endl;
    
    do
    {
        cout << "Do you want to play again 'Y' or 'N' ? : ";
        cin >> ch;
        if (ch == 'Y' || ch == 'y')
            return true;
        else if (ch == 'N' || ch == 'n')
            return false;

    } while (true);
}

void Snake_Game::saveBestScore()
{
    if (score > best_score)
    {
        ofstream file("best_score.txt");
        if (file)
        {
            file << score;
            file.close();
        }
    }
}

void Snake_Game::getBestScore()
{
    ifstream file("best_score.txt");
    if (file)
    {
        string str;
        getline(file, str);
        stringstream obj(str);
        obj >> best_score;
        file.close();
    }
    else
        best_score = 0;
}