#include <iostream>
#include <math.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


#include "game.h"

Graphics::Graphics(int n_squares)
{
    this->n_squares = n_squares;  
}

Graphics::~Graphics()
{
    free(lines);
}

void Graphics::initGrid()
{
    //Draw Grid

    lines = (sf::Vertex*)malloc((n_squares*4)*sizeof(sf::Vertex));

    for (int i = 0, j = 0; i < n_squares; i++, j = j + 4)
    {
        lines[j + 0] = {sf::Vertex(sf::Vector2f(i*square_dim + 1, 0 + 120), sf::Color(0, 0, 0, 255))};
        lines[j + 1] = {sf::Vertex(sf::Vector2f(i*square_dim + 1, n_squares*square_dim + 120), sf::Color(0, 0, 0, 255))};
        lines[j + 2] = {sf::Vertex(sf::Vector2f(0 , i*square_dim + 1 + 120), sf::Color(0, 0, 0, 255))};
        lines[j + 3] = {sf::Vertex(sf::Vector2f(n_squares*square_dim, i*square_dim + 1 + 120), sf::Color(0, 0, 0, 255))};
    }
}

void Graphics::drawGrid(sf::RenderWindow& window)
{
    window.draw(lines, n_squares*4, sf::Lines);
}

void Graphics::newGameButton(sf::RenderWindow& window)
{
    // define a 120x50 rectangle
    sf::RectangleShape rectangle(sf::Vector2f(/*120.f*/ (float)(0.15*n_squares*square_dim), 50.f));
    rectangle.setFillColor(sf::Color(255, 255, 255));
    rectangle.setPosition(/*650*/ (float)(0.8125*n_squares*square_dim), 40.f);
    window.draw(rectangle);

    sf::Vertex borders[] = 
    {
        sf::Vertex(sf::Vector2f(/*650*/ 0.8125*n_squares*square_dim, 40), sf::Color(0, 0, 0, 255)),
        sf::Vertex(sf::Vector2f(/*770*/ 0.9625*n_squares*square_dim, 40), sf::Color(0, 0, 0, 255)),
        sf::Vertex(sf::Vector2f(/*650*/ 0.8125*n_squares*square_dim, 90), sf::Color(0, 0, 0, 255)),
        sf::Vertex(sf::Vector2f(/*770*/ 0.9625*n_squares*square_dim, 90), sf::Color(0, 0, 0, 255)),
        sf::Vertex(sf::Vector2f(/*650*/ 0.8125*n_squares*square_dim, 40), sf::Color(0, 0, 0, 255)),
        sf::Vertex(sf::Vector2f(/*650*/ 0.8125*n_squares*square_dim, 90), sf::Color(0, 0, 0, 255)),
        sf::Vertex(sf::Vector2f(/*770*/ 0.9625*n_squares*square_dim, 40), sf::Color(0, 0, 0, 255)),
        sf::Vertex(sf::Vector2f(/*770*/ 0.9625*n_squares*square_dim, 90), sf::Color(0, 0, 0, 255)),
    };
    window.draw(borders, 8, sf::Lines);
}

void Graphics::loadfont()
{
    // Load from a font file on disk
    if (!font.loadFromFile("./res/fonts/ARCADECLASSIC.TTF"))
    {
        std::cout << "Couldn't load font" << std::endl;
        exit(-1);
    }
    setNewGameText();
    setLoseWinText();
}

void Graphics::setNewGameText()
{
    new_game_str.setFont(font);
    new_game_str.setString("New");
    new_game_str.setCharacterSize(25);
    new_game_str.setPosition(/*655*/ (0.86)*n_squares*square_dim, 35);
    new_game_str.setFillColor(sf::Color(74, 167, 255));

    new_game_str1.setFont(font);
    new_game_str1.setString("Game");
    new_game_str1.setCharacterSize(25);
    new_game_str1.setPosition(/*655*/ (0.8125+(0.07/2))*n_squares*square_dim, 60);
    new_game_str1.setFillColor(sf::Color(74, 167, 255));
}

void Graphics::setLoseWinText()
{
    lose_game_str.setFont(font);
    lose_game_str.setString("LOST");
    lose_game_str.setCharacterSize(50);
    lose_game_str.setPosition(/*655*/ 0.45*n_squares*square_dim, 30);
    lose_game_str.setFillColor(sf::Color(255, 255, 255));

    win_game_str.setFont(font);
    win_game_str.setString("WON");
    win_game_str.setCharacterSize(50);
    win_game_str.setPosition(/*655*/ 0.45*n_squares*square_dim, 30);
    win_game_str.setFillColor(sf::Color(255, 255, 255));
}

void Graphics::drawLoseText(sf::RenderWindow& window)
{
    window.draw(lose_game_str);
}

void Graphics::drawWinText(sf::RenderWindow& window)
{
    window.draw(win_game_str);
}

void Graphics::drawNewGameText(sf::RenderWindow& window)
{ 
    window.draw(new_game_str);
    window.draw(new_game_str1);
}

void Graphics::loadSprites()
{
    char buffer[100];

    for (int i = 0; i < 12; i++)
    {
        sprintf(buffer, "./res/texture/MINESWEEPER%d.png", i);

        if (!pic_arr[i].loadFromFile(buffer))
        {
            std::cout << "Couldn't load images" << std::endl;
            exit(-1);
        }
        sprite_arr[i].setTexture(pic_arr[i]);

        //Resizing the sprites to fit the squares
        sprite_arr[i].setScale(sf::Vector2f(0.18f, 0.18f));
    }
}

void Graphics::drawInitTiles(sf::RenderWindow& window)
{
    int i,j;

    for (i = 0; i < this->n_squares; i++)
    {
        for(j = 0; j < this->n_squares ; j++)
        {
            drawUnrevealedSprites(window, i, j);
        }
    }
}

void Graphics::drawUnrevealedSprites(sf::RenderWindow& window, int x, int y)
{
    sprite_arr[TILE_UNREVEALED].setPosition(sf::Vector2f(1+(square_dim)*x, 1 + (square_dim)*y + 120));
    window.draw(sprite_arr[TILE_UNREVEALED]);
}

void Graphics::drawNumber(sf::RenderWindow& window, int x, int y, int tile)
{
    sprite_arr[tile].setPosition(sf::Vector2f(1 + x*square_dim, 1 + y*square_dim + 120));
    window.draw(sprite_arr[tile]);
}

void Graphics::drawMines(sf::RenderWindow& window, int x, int y)
{
    sprite_arr[TILE_MINE].setPosition(sf::Vector2f(1 + x*square_dim, 1 + y*square_dim + 120));
    window.draw(sprite_arr[TILE_MINE]);
}

void Graphics::drawFlags(sf::RenderWindow& window, int x, int y)
{
    sprite_arr[TILE_FLAG].setPosition(sf::Vector2f(1 + x*square_dim, 1 + y*square_dim + 120));
    window.draw(sprite_arr[TILE_FLAG]);
}

int Graphics::newGameMouse(sf::RenderWindow& window)
{
    sf::Vector2i position = sf::Mouse::getPosition(window);

    if(position.x >= 0.8125*n_squares*square_dim && position.x <= 0.9625*n_squares*square_dim && position.y >= 40 && position.y <= 90)
        return 1;
    else
        return 0;
}

Game::Game(int n_squares)
{
    this->dimension = n_squares;

    //Alocar a memoria para todas celulas
    board.resize(this->dimension, std::vector<Cell>(n_squares, Cell(false, false)));

    //Gerar posiçao aleatoria para as minas
    this->randomMines();
}

void Game::getMousecoor(sf::RenderWindow& window)
{   
    // get mouse position relative to the window
    sf::Vector2i position = sf::Mouse::getPosition(window);

    if (position.y >= 120)
    {
        //Normalize to the nr of squares
        nMouse.x = floor((position.x)/square_dim);
        nMouse.y = floor((position.y - 120)/square_dim);
        std::cout << nMouse.x << "," << nMouse.y << std::endl;
    }
}

void Game::randomMines()
{
    // O nr de minas é igual ao 
    // nr de celulas por lado

    int x,y, n_mines = 0;
    srand(time(NULL));
    
    while(n_mines < total_mines)
    {
        do
        {
            x = rand() % dimension;
            y = rand() % dimension;
        }
        while(board[x][y].isMine() == true);
        board[x][y].setMine();
        n_mines++;
    }
}

void Game::checkTile(sf::RenderWindow& window, Graphics* graphics)
{
    if (board[nMouse.x][nMouse.y].isFlagged() == false && game_end == false)
    {
        if (board[nMouse.x][nMouse.y].isMine() == true)
        {
            board[nMouse.x][nMouse.y].reveal();
            graphics->drawMines(window, nMouse.x, nMouse.y);
        }
        else
        {
            checkAround(window, graphics, nMouse.x, nMouse.y);
        }
    }
}

int Game::checkAround(sf::RenderWindow& window, Graphics* graphics, int x, int y)
{
    int count = 0;

    if (x < 0 || y < 0 || x > dimension-1 || y > dimension-1 || board[x][y].isRevealed() == true)
        return 0;

    //Canto superior esquerdo
    if(x == 0 && y == 0)
    {
        if (board[x][y+1].isMine() == true)
            count++;
        if (board[x+1][y+1].isMine() == true)
            count++;
        if (board[x+1][y].isMine() == true)
            count++;
    }

    //Canto inferior esquerdo
    if (x == 0 && y == dimension-1)
    {
        if (board[x][y-1].isMine() == true)
            count++;
        if (board[x+1][y-1].isMine() == true)
            count++;
        if (board[x+1][y].isMine() == true)
            count++;
    }

    //Canto superior direito
    if(x == dimension-1 && y == 0)
    {
        if (board[x-1][y].isMine() == true)
            count++;
        if (board[x-1][y+1].isMine() == true)
            count++;
        if (board[x][y+1].isMine() == true)
            count++;
    }

    //Canto inferior direito
    if(x == dimension-1 && y == dimension-1)
    {
        if (board[x][y-1].isMine() == true)
            count++;
        if (board[x-1][y-1].isMine() == true)
            count++;
        if (board[x-1][y].isMine() == true)
            count++;
    }

    //Está no meio
    if (x > 0 && y > 0 && x < dimension-1 && y < dimension-1)
    {
        if (board[x-1][y-1].isMine() == true)
            count++;
        if (board[x-1][y].isMine() == true)
            count++;
        if (board[x-1][y+1].isMine() == true)
            count++;
        if (board[x][y+1].isMine() == true)
            count++;
        if (board[x+1][y+1].isMine() == true)
            count++;
        if (board[x+1][y].isMine() == true)
            count++;
        if (board[x+1][y-1].isMine() == true)
            count++;
        if (board[x][y-1].isMine() == true)
            count++;
    }

    //Lado esquerdo
    else if (x == 0 && y > 0 && y < dimension-1)
    {
        if (board[x][y+1].isMine() == true)
            count++;
        if (board[x+1][y+1].isMine() == true)
            count++;
        if (board[x+1][y].isMine() == true)
            count++;
        if (board[x+1][y-1].isMine() == true)
            count++;
        if (board[x][y-1].isMine() == true)
            count++;
    }
    
    //Lado Direito
    else if (x == dimension-1 && y > 0 && y < dimension-1)
    {
        if (board[x][y+1].isMine() == true)
            count++;
        if (board[x-1][y-1].isMine() == true)
            count++;
        if (board[x-1][y].isMine() == true)
            count++;
        if (board[x-1][y+1].isMine() == true)
            count++;
        if (board[x][y-1].isMine() == true)
            count++;
    }

    //Topo
    else if (x > 0 && x < dimension-1 && y == 0)
    {
        if (board[x-1][y].isMine() == true)
            count++;
        if (board[x-1][y+1].isMine() == true)
            count++;
        if (board[x][y+1].isMine() == true)
            count++;
        if (board[x+1][y+1].isMine() == true)
            count++;
        if (board[x+1][y].isMine() == true)
            count++;
    }

    //Baixo
    else if (x > 0 && x < dimension-1 && y == dimension -1)
    {
        if (board[x-1][y].isMine() == true)
            count++;
        if (board[x-1][y-1].isMine() == true)
            count++;
        if (board[x][y-1].isMine() == true)
            count++;
        if (board[x+1][y-1].isMine() == true)
            count++;
        if (board[x+1][y].isMine() == true)
            count++;
    }

    board[x][y].reveal();

    if (count == 0)
    {
        checkAround(window, graphics, x-1, y-1);
        checkAround(window, graphics, x-1, y);
        checkAround(window, graphics, x, y-1);
        checkAround(window, graphics, x-1, y+1);
        checkAround(window, graphics, x+1, y);
        checkAround(window, graphics, x+1, y-1);
        checkAround(window, graphics, x, y + 1);
        checkAround(window, graphics, x+1, y+1);
        
    }
    graphics->drawNumber(window, x, y, count);
    return 0;
}

void Game::insertFlag(sf::RenderWindow& window, Graphics* graphics)
{
    if (board[nMouse.x][nMouse.y].isRevealed() == 0)
    {
        if (board[nMouse.x][nMouse.y].isFlagged() == 0)
        {
            board[nMouse.x][nMouse.y].setFlag();
            graphics->drawFlags(window, nMouse.x, nMouse.y);
        }
        else
        {
            board[nMouse.x][nMouse.y].deFlag();
            graphics->drawUnrevealedSprites(window, nMouse.x, nMouse.y);
        } 
    }
}

void Game::revealAllMines(sf::RenderWindow& window, Graphics* graphics)
{
    int i, j;

    for (i = 0; i < dimension; i++)
    {
        for(j = 0; j < dimension; j++)
        {
            if (board[i][j].isMine() == true)
            {
                graphics->drawMines(window, i, j);
            }
        }
    }
}

void Game::endGame(sf::RenderWindow& window, Graphics* graphics)
{
    int check = checkLose();

    if (check == 1)
    {
        gameEnd();
        revealAllMines(window, graphics);
        graphics->drawLoseText(window);
    }
    else if (check == 2)
    {
        gameEnd();
        revealAllMines(window, graphics);
        graphics->drawWinText(window);
    }
}

int Game::checkLose()
{
    int i, j, count = 0;
    
    for (i = 0; i < dimension; i++)
    {
        for(j = 0; j < dimension; j++)
        {
            if (board[i][j].isMine() == true)
            {    
                if (board[i][j].isRevealed() == true)
                    return 1;
            }
            else
            {
                if (board[i][j].isRevealed() == true)
                    count++;
            }
            
        }
    }

    if (count == dimension*dimension - total_mines)
        return 2;
    else
        return 0;
}

void Game::printMines()
{
    int i, j;

    for (i = 0; i < dimension; i++)
    {
        for(j = 0; j < dimension; j++)
        {
            if (board[i][j].isMine() == true)
            {
                std::cout << "Mine at " << i << " " << j << std::endl; 
            }
        }
    }
}

void Game::newGame()
{
    int i, j;

    for (i = 0; i < dimension; i++)
    {
        for(j = 0; j < dimension; j++)
        {
            board[i][j].unreveal();
            board[i][j].deMine();
            board[i][j].deFlag();
        }
    }
    randomMines();
    resetGame();
}