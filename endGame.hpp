class EndGame
{
    public:
        
        gameObject goodEndBackground;
        gameObject badEndBackground;

        void load()
        {
            goodEndBackground.setSize(1280, 720);
            goodEndBackground.setPosition(0, 0);

            badEndBackground.setSize(1280, 720);
            badEndBackground.setPosition(0, 0);
 
        }

        void setTextures(sf::Texture* goodBackTexture, sf::Texture* badBackTexture)
        {
            goodEndBackground.setTexture(goodBackTexture);
            badEndBackground.setTexture(badBackTexture);

        }

        void checkEnd(sf::RenderWindow* window, int* brs, int* peresd, Menu* menu, int* time, Records* records)
        {
            if(*brs < 30 and *peresd > 0)
                return;
            
            records -> initTime(*time);
            if (*brs >= 30)
            {
              records -> commitChanges();
              records -> initText();
            }
            
            bool isEndGame = true;
            sf::Event endEvent;

            while(isEndGame)
            {
                window->clear();
                if(*brs >= 30)
                {
                    goodEndBackground.draw(window);
                    records -> draw(window);
                }
                if(*peresd <= 0)
                    badEndBackground.draw(window);
                window->display();

                while (window->pollEvent(endEvent))
                {
                    if (endEvent.type == sf::Event::Closed) 
                        window->close();
                    if (endEvent.type == sf::Event::KeyPressed)
                    {
                        if (endEvent.key.code == sf::Keyboard::Escape)
                        {
                            menu->run(window);
                            isEndGame = false;
                        }            
                    }  
                }      
            }
        }
};
