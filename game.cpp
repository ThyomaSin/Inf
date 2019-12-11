#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

#include "vector.h" // own new lib with vectors and operations on them
#include "GraphicsManeger.h"
#include "Records.h"

const int SCREEN_Y = 720;
const int SCREEN_X = 1280;
const float DT = 0.05;
const float RESISTANCE_COEF = 0.1;

class gameObject: public DrawableObject
{
    public:
        
        sf::RectangleShape shape;

        sf::Texture texture;

        vector2f Q;
        vector2f V;

        int xSize;
        int ySize;

        bool isStrickingWithBorders = true;

        void setSize(int length, int width)
        {
            xSize = length;
            ySize = width;
            shape.setSize(sf::Vector2f(xSize, ySize));
        }

        void setTexture(sf::Texture* newTexture)
        {
            shape.setTexture(newTexture);
        }

        void setPosition(int x, int y)
        {
            Q.x = x;
            Q.y = y;
            shape.setPosition(Q.x, Q.y);
        }

        void draw(sf::RenderWindow* window)
        {
             window->draw(shape);
        }

        void move(float DT, int SCREEN_Y, int SCREEN_X)
        {
            if(isStrickingWithBorders)
            {
                if(Q.x <= 0 or Q.x >= SCREEN_X - xSize) //bounce from screen borders
                    V.x = -V.x;
                if(Q.y <= 0 or Q.y >= SCREEN_Y - ySize)
                    V.y = -V.y; 

                if(Q.x < 0)                         // dividing stucked object in border
                    Q.x += abs(Q.x) + 1;
                if(Q.x > SCREEN_X - xSize)
                    Q.x -= Q.x + xSize - SCREEN_X + 1;
                if(Q.y < 0)
                    Q.y += abs(Q.y) + 1;
                if(Q.y > SCREEN_Y - ySize)
                    Q.y -= Q.y + ySize - SCREEN_Y + 1;

            }

            this->Q.x += this->V.x * DT;
            this->Q.y += this->V.y * DT;
            shape.setPosition(Q.x, Q.y);
            
        }

        void addResistance(float resistanceCoef)
        {
            this->V.x = this->V.x - resistanceCoef * this->V.x;
            this->V.y = this->V.y - resistanceCoef * this->V.y;
        }

        void addSpeed(float horisontalSpeed, float vertivalSpeed)
        {
            V.x += horisontalSpeed;
            V.y += vertivalSpeed;
        }

        bool checkObjectCollision(gameObject object2)
        {
        if ((this->Q.x > object2.Q.x + object2.xSize) or (this->Q.x + this->xSize < object2.Q.x))
            return false;
        if ((this->Q.y > object2.Q.y + object2.ySize) or (this->Q.y + this->ySize < object2.Q.y))
            return false;
        return true;
        }
    
} ;

#include "menu.hpp"
#include "interface.hpp"
#include "background.hpp"
#include "platform.hpp"
#include "endGame.hpp"


main()
{
// Menu context
    Menu menu;
    sf::Texture menuBackTexture;
    sf::Texture button1Texture;
    sf::Texture button2Texture;
    sf::Texture button3Texture;
    sf::Texture logoTexture;
    menuBackTexture.loadFromFile("resources/menuBackground.png");
    button1Texture.loadFromFile("resources/button1.png");
    button2Texture.loadFromFile("resources/button2.png");
    button3Texture.loadFromFile("resources/button3.png");
    logoTexture.loadFromFile("resources/logo.png");

    menu.setTextures(&menuBackTexture, &button1Texture, &button2Texture, &button3Texture, &logoTexture);
//

// HUD context
    HUD hud;
    sf::Texture hudTexture;
    hudTexture.loadFromFile("resources/hud.png");

    sf::Font font; 
    font.loadFromFile("resources/arial.ttf");

    hud.load(&font);

    int BRS = 0;
    int PERESD = 3;

    hud.setBRS(BRS);
    hud.setPeresd(PERESD);
    hud.setTextures(&hudTexture);
//

// background context
    Background background;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("resources/background.png");
    backgroundTexture.setSmooth(true);

    background.load();
    background.setTexture(&backgroundTexture);
//

// plates and PlateManager context
    PlataformManager Plates;

    sf::Texture* PlateTextures = new sf::Texture[5];
    PlateTextures[0].loadFromFile("resources/BRS.png");
    PlateTextures[1].loadFromFile("resources/Znamka.png");
    PlateTextures[2].loadFromFile("resources/Ivanova.png");
    PlateTextures[3].loadFromFile("resources/Talis.png");
    PlateTextures[4].loadFromFile("resources/facker.png");
    for(int i = 0; i < 5; i++)
        PlateTextures[i].setSmooth(true);
//

// endGame context
    EndGame endGame;

    sf::Texture goodEndTexture;
    goodEndTexture.loadFromFile("resources/goodEnd.png");
    sf::Texture badEndTexture;
    badEndTexture.loadFromFile("resources/badEnd.png");

    endGame.load();
    endGame.setTextures(&goodEndTexture, &badEndTexture);
//


    int plateDelay = 1;
    int plateCounter = 0;

   
    //CONTEXT:
    sf::Event event;

    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "game");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("resources/texture.png"))
    {
        std::cout << "Loading texture erorr" << "\n";
    }


    playerTexture.setSmooth(true);
    backgroundTexture.setSmooth(true);

    gameObject player;
    player.setSize(50, 50);
    player.setTexture(&playerTexture);
    player.setPosition(300,400);
    int time = 0;
    Records records = Records(font, 25, sf::Color::Red);

    while (window.isOpen())
    {
        //PHISICS: 

        player.move(DT, SCREEN_Y, SCREEN_X);
        player.addResistance(RESISTANCE_COEF);
        background.move();
        Plates.move(DT, SCREEN_Y, SCREEN_X);

        Plates.workOnCollisionWithPlayer(&player ,&BRS ,&PERESD ,&hud);
        Plates.deletePlatesOutOfScreen();
        

        //EVEN HANDLER
        
        while (window.pollEvent(event))
		{
		    if (event.type == sf::Event::Closed) 
                  window.close();
        }
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                menu.run(&window);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                 player.addSpeed(0, -15);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player.addSpeed(0, 15);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player.addSpeed(-15, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player.addSpeed(15, 0);

        //LOGICS:

        if(plateDelay != 0)
            plateDelay = plateDelay - 1;
        if(plateDelay == 0)
        {
            Plates.addPlate(generateNewPlate(PlateTextures));
            plateCounter += 1;
            plateDelay = 50;
            time++;
        }

        endGame.checkEnd(&window, &BRS, &PERESD, &menu, &time, &records);


        //GRAPHICS:
        //manager.drawAll(&window);
        window.clear();
        background.draw(&window);
        Plates.draw(&window);
        player.draw(&window);
        hud.draw(&window);
        window.display();
    }

    delete[] PlateTextures;
}
