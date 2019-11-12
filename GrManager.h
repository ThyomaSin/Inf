class drawableObj
{
  public:
  bool isvisible = true;
  virtual void draw(void* pointer);  
};
/*
drawableObj::drawableObj()
{
}

drawableObj::~drawableObj()
{
}*/

class grManager
{
  private:
    drawableObj** obj = new drawableObj*[100];
  public:
    int i = 0;
    int size = 100;
    void registrate(drawableObj* dObj);
    void deletion(drawableObj* dObj);
    void drawAll(void* pointer);
    void clear();
    ~grManager();
};

grManager::~grManager()
{
  delete[] obj;
}

void grManager::registrate(drawableObj* dObj)
{
  if (i >= size)
  {
    drawableObj** newobj = new drawableObj*[size + 100];
    for (int j = 0; j < size; j++)
      newobj[j] = obj[j];
    obj = newobj;
    size += 100;
  }
  obj[i] = dObj;
  i++;
}

void grManager::deletion(drawableObj* dObj)
{
  int j = 0;
  while (obj[j] != dObj)
    j++;
  
  for(int k = j; k < i - 1; k++)
    this -> obj[k] = this -> obj[k+1];
  i--;
}

void grManager::drawAll(void* pointer)
{ 
  (*(sf::RenderWindow*) pointer).clear();
  for (int j = 0; j < i; j++)
    obj[j] -> draw(pointer);
  (*(sf::RenderWindow*) pointer).display(); 
} 

