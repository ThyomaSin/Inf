class Platform : public gameObject
{
  bool isExist = true;
  int brs = 0;
  int peresd = 0;
  void setPlatform(float x, float y, float vx, float vy, sf::Texture* texturePointer);
  //sf::Texture* getTextureByNumber(int typeNumber);
  Platform();
  void generate(sf::Texture* texturePointer);
};



void Platform::setPlatform(float x, float y, float vx, float vy, sf::Texture* texturePointer)
{
  this -> setPosition(x, y);
  this -> addSpeed(vx, vy);
  this -> setTexture(texturePointer);
}

Platform::Platform()
{
}

sf::Texture* getTextureByNumber(int typeNumber, sf::Texture* textures)
{
  if (typenumber < 5)
    return (&(textures[typeNumber]));
}

void Platform::generate(sf::Texture* texturePointer)
{
  srand(time(0) + rand());
  int y = rand() % 640;         //also need to add BRS and peresda
  int typeNumber = rand() % 5;
  this -> setPlatform(1300, y, -300, 0, getTextureByNumber(typeNumber, texturePointer))
}

bool checkGameObjectCollision(gameObject object1, gameObject object2)
{
  if ((object1.Q.x > object2.Q.x + object2.xSize) or (object1.Q.x + object1.xSize < object2.Q.x))
    return false;
  if ((object1.Q.y > object2.Q.y + object2.ySize) or (object1.Q.y + object1.ySize < object2.Q.y))
    return false;
  return true;
}

 
  

