class Node
{
  public:
  void* obj;
  Node* next = NULL;
};

class List
{
  public:
  Node* head = NULL;
  void pushFront(void* obj);
  void* popFront();
  void append(void* obj);
  //void remove((void*) obj);
  void* pull(int j);
  int len();
  void remove(void* object);
};  

void List::pushFront(void* add)
{
  Node* newObj = new Node;
  newObj -> obj = add;
  newObj -> next = head;
  head = newObj;
}

void* List::popFront()
{
  Node* pointer = head;
  head = head -> next;
  return pointer -> obj;
}

void List::append(void* object)
{
  Node* newNode = new Node;
  Node* current = head;
  newNode -> obj = object;
  if (current != NULL)
  {
    while (current -> next != NULL)
    {
      current = current -> next;
    }
    current -> next = newNode;
  }
  else head = newNode;
}

void* List::pull(int i)
{
  Node* current = head;
  int j = 0;
  while (i != j)
  {
    current = current -> next;
    j++;
  }
  return current -> obj;
}

int List::len()
{
  int i = 1;
  Node* current = head;
  while (current -> next != NULL)
  {
    current = current -> next;
    i++;
  }
  return i;
}

/*int List::getPos(void* obj)
{
  int i = 1;
  Node* current = head;
  while (current -> next != obj)
  {
    current = current -> next;
    i++;
  }
  i++;
  return i;
} */ 

void List::remove(void* object)
{
  Node* current = head;
  if (head -> obj == object)
  {
    this -> popFront();
    return;
  } 

  while ((current -> next -> obj != object) and (current -> next != NULL))
  {
    current = current -> next;
  }
  if (current -> next -> next != NULL)
    current -> next = current -> next -> next;
  else current -> next = NULL;
}










 
