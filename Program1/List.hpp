typedef struct Link_ {
  Link_ *next, *prev;
} Link;

typedef struct Node_{
	Link link;
  Person *person;

} Node;

typedef struct List_PersonPtr_Iterator_{
	Link *link;
  Person* (*deref)(List_PersonPtr_Iterator_ *it);
  void (*inc)(List_PersonPtr_Iterator_ *it);
  void (*dec)(List_PersonPtr_Iterator_ *it);
} List_PersonPtr_Iterator;

typedef Person* PersonPtr;

typedef struct List_PersonPtr_{
	Node *head;
  Link *tail;
  const char *type;

  bool (*PersonPtr_less)(const PersonPtr &p1, const PersonPtr &p2);
  List_PersonPtr_Iterator (*push_front)(List_PersonPtr_ *list, Person *person);
  List_PersonPtr_Iterator (*push_back)(List_PersonPtr_ *list, Person *person);

  void (*sort)(List_PersonPtr_ *it);
  void (*erase)(List_PersonPtr_ *list, List_PersonPtr_Iterator it);
  List_PersonPtr_Iterator (*begin)(List_PersonPtr_ *list);
  List_PersonPtr_Iterator (*end)(List_PersonPtr_ *list);
  void (*delet)(List_PersonPtr_ *list);

}List_PersonPtr;


List_PersonPtr_Iterator push_front(List_PersonPtr_ *list, Person *person)
{
  Node *n = (Node*) malloc (sizeof(Node));
  n->person = person;
  if(list->head == NULL)
  {
    n->link.next = n->link.prev = &n->link;
  }
  List_PersonPtr_Iterator it;
  return it;
}
List_PersonPtr_Iterator push_back(List_PersonPtr_ *list, Person *person)
{
  List_PersonPtr_Iterator it;
  return it;
}
void sort(List_PersonPtr_ *it)
{

}
void erase(List_PersonPtr_ *list, List_PersonPtr_Iterator it)
{

}
void it_inc (List_PersonPtr_Iterator_ *it)
{

}
void it_dec (List_PersonPtr_Iterator_ *it)
{

}

List_PersonPtr_Iterator List_PersonPtr_it_ctor(Link *link)
{
 // List_PersonPtr_Iterator *it = (List_PersonPtr_Iterator*) malloc( sizeof(List_PersonPtr_Iterator));
  List_PersonPtr_Iterator it;
  it.inc = it_inc;
  it.dec = it_dec;
  return it;
}
bool List_PersonPtr_Iterator_equal (List_PersonPtr_Iterator it1, List_PersonPtr_Iterator it2)
{
  return true;
}
void List_PersonPtr_delet(List_PersonPtr *list)
{

}
List_PersonPtr_Iterator List_PersonPtr_begin(List_PersonPtr *list) {
    return List_PersonPtr_it_ctor(list->head->link.next);
}
List_PersonPtr_Iterator List_PersonPtr_end(List_PersonPtr *list) {
    return List_PersonPtr_it_ctor(&list->head->link);
}
void List_PersonPtr_it_inc(List_PersonPtr_Iterator *it) {
    it->link = it->link->next;
}
List_PersonPtr* List_PersonPtr_new(bool (*PersonPtr_less)(const PersonPtr &p1, const PersonPtr &p2))
{
  List_PersonPtr *List = (List_PersonPtr*)malloc(sizeof(List_PersonPtr));
  List->type = "List_PersonPtr";
  List->head = NULL;
  List->PersonPtr_less = PersonPtr_less;
  List->push_front = push_front;
  List->push_back = push_back;
  List->sort = sort;
  List->erase = erase;
  List->begin = List_PersonPtr_begin;
  List->end = List_PersonPtr_end;
  List->delet = List_PersonPtr_delet;
  return List;
}
