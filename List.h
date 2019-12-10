class Node
{
  public:
  void* obj;
  Node* next = NULL;
  Node(void* object, Node* next);
};

class List
{
  public:
  Node* head = NULL;
  void pushFront(void* obj);
  void* popFront();
  void append(void* obj);
  //void remove((void*) obj);
  int& operator[](int j);
  int len();
  void remove(void* object);
};  


Node::Node(void* object, Node* NEXT)
{
  this -> obj = object;
  this -> next = NEXT;
}
 
void List::pushFront(void* add)
{
  Node* newObj = Node(add, head);
  head = newObj;
}

void* List::popFront()
{
  if (head == NULL)
    return (void*) NULL;
  Node* pointer = head;
  head = head -> next;
  return pointer -> obj;
}

void List::append(void* object)
{
  Node* newNode = Node(object, NULL);
  Node* current = head;
  
  if (!current)
  {
    head = newNode;
    return;
  }

  while (current -> next != NULL)
    current = current -> next;
 
  current -> next = newNode;
}

int& List::operator[](int i)
{
  Node* current = head;
  int j = 0;
  while (i != j)
  {
    if (!current)
      return NULL;
    current = current -> next;
    j++;
  }
  return current -> obj;
}

int List::len()
{
  int i = 0;
  Node* current = head;
  if (!current)
      return i;
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

  while ((current -> next != NULL) and (current -> next -> obj != object))
  {
    current = current -> next;
  }
  if (current -> next -> next != NULL)
    current -> next = current -> next -> next;
  else current -> next = NULL;
}










 
