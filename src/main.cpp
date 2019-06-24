#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "game.h"

int main(int argc, char **argv)
{
    //Flag para desenhar as 
    //unrevealed_tiles so no inicio
    bool game_start = true;

    //Nr de tiles por lado 
    int n_squares = 20;

    sf::RenderWindow window(sf::VideoMode(n_squares*square_dim, n_squares*square_dim + 120), "Minesweeper", sf::Style::Default);
    window.setFramerateLimit(60);

    window.clear(sf::Color(147, 204, 255));

    Graphics graphics(n_squares);
    graphics.newGameButton(window);
    graphics.loadfont();
    graphics.initGrid();
    graphics.loadSprites();

    Game game(n_squares);
    game.printMines();  

    // Run program while window is opened
    while (window.isOpen())
    {
        sf::Event event;

        //Poll for events
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (graphics.newGameMouse(window))
                        {
                            window.clear(sf::Color(147, 204, 255));
                            graphics.newGameButton(window);
                            game.newGame();
                            game_start = true;
                        }
                        else 
                        {
                            game.getMousecoor(window);
                            game.checkTile(window, &graphics);
                        }
                    }
                    if(event.mouseButton.button == sf::Mouse::Right)
                    {
                        game.getMousecoor(window);
                        game.insertFlag(window, &graphics);
                    }
                    break;

                default:
                    break;
            }
        }
        graphics.drawNewGameText(window);
        graphics.drawGrid(window);

        if (game_start == true) 
        {
            graphics.drawInitTiles(window);
            game_start = false;
        }
        game.endGame(window, &graphics);
        window.display();     
    }
    return 0;
}