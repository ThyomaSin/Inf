class DrawableObj
{
  public:
  bool isvisible = true;
  virtual void draw(void* pointer);  
};

class GrManager
{
  private:
    DrawableObj** obj = new DrawableObj*[100];
  public:
    int i = 0;
    int size = 100;
    void registrate(DrawableObj* dObj);
    void deletion(DrawableObj* dObj);
    void drawAll(void* pointer);
    void clear();
    ~GrManager();
};

GrManager::~GrManager()
{
  delete[] obj;
}

void GrManager::registrate(DrawableObj* dObj)
{
  if (i >= size)
  {
    DrawableObj** newobj = new DrawableObj*[size + 100];
    for (int j = 0; j < size; j++)
      newobj[j] = obj[j];
    obj = newobj;
    size += 100;
  }
  obj[i] = dObj;
  i++;
}

void DrawableObj::draw(void* pointer)
{
}

void GrManager::deletion(DrawableObj* dObj)
{
  int j = 0;
  while (obj[j] != dObj)
    j++;
  
  for(int k = j; k < i - 1; k++)
    this -> obj[k] = this -> obj[k+1];
  i--;
}

void GrManager::drawAll(void* pointer)
{ 
  (*(sf::RenderWindow*) pointer).clear();
  for (int j = 0; j < i; j++)
    obj[j] -> draw(pointer);
  (*(sf::RenderWindow*) pointer).display(); 
} 

