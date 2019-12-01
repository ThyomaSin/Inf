#include "List.h"

class DrawableObj
{
  public:
  bool isvisible = true;
  virtual void draw(void* pointer);  
};

class GrManager
{
  public:
    List list;
    void registrate(DrawableObj* dObj);
    void deletion(DrawableObj* dObj);
    void drawAll(void* pointer);
    void clear();
    //~GrManager();
};

void GrManager::registrate(DrawableObj* dObj)
{
  list.append((void*) dObj);
}

void DrawableObj::draw(void* pointer)
{
}

void GrManager::deletion(DrawableObj* dObj)
{
  list.remove((void*) dObj);
}

void GrManager::drawAll(void* pointer)
{ 
  (*(sf::RenderWindow*) pointer).clear();
  for (int j = 0; j < list.len(); j++)
    (*(DrawableObj*) (list.pull(j))).draw(pointer);
  (*(sf::RenderWindow*) pointer).display(); 
} 

