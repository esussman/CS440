typedef Person* PersonPtr;

typedef struct Node_{
	Node_ *next;
  Node_ *prev;
  Person *person;
} Node;

typedef struct List_PersonPtr_Iterator_{
	Node *node;
  PersonPtr& (*deref)(List_PersonPtr_Iterator_*);
  void (*inc)(List_PersonPtr_Iterator_*);
  void (*dec)(List_PersonPtr_Iterator_*);
} List_PersonPtr_Iterator;

typedef struct List_PersonPtr_{
  Node head;
  char type[sizeof("List_PersonPtr")];
  int size;
  bool (*compare)(const PersonPtr &p1, const PersonPtr &p2);
  List_PersonPtr_Iterator (*push_front)(List_PersonPtr_* , Person*);
  List_PersonPtr_Iterator (*push_back)(List_PersonPtr_* , Person*);

  void (*sort)(List_PersonPtr_*);
  void (*erase)(List_PersonPtr_* , List_PersonPtr_Iterator);
  List_PersonPtr_Iterator (*begin)(List_PersonPtr_* );
  List_PersonPtr_Iterator (*end)(List_PersonPtr_* );
  void (*delet)(List_PersonPtr_*);

}List_PersonPtr;

Node* Node_new(Person* person)
{
  Node *n = (Node*) malloc (sizeof(Node));
  n->next = NULL;
  n->prev = NULL;
  n->person = person;
  return n;
}
Person* &Iterator_PersonPtr_deref(List_PersonPtr_Iterator_* it)
{
  Node *p = it->node;
  return p->person;
}
bool List_PersonPtr_Iterator_equal (List_PersonPtr_Iterator it1, List_PersonPtr_Iterator it2)
{
  if(it1.node == it2.node)
    return true;
  else
    return false;
}

void List_PersonPtr_it_inc(List_PersonPtr_Iterator* it) {
    it->node = it->node->next;
}
void List_PersonPtr_it_dec(List_PersonPtr_Iterator* it) {
  it->node = it->node->prev;
}

List_PersonPtr_Iterator List_PersonPtr_it_ctor(Node* node)
{
  List_PersonPtr_Iterator it;
  it.node = node;
  it.deref = *Iterator_PersonPtr_deref;
  it.inc = List_PersonPtr_it_inc;
  it.dec = List_PersonPtr_it_dec;
  return it;
}
void insert_before(Node* pos, Node* n)
{
  n->next = pos;
  n->prev = pos->prev;
  pos->prev->next = n;
  pos->prev = n;
}
List_PersonPtr_Iterator push_front(List_PersonPtr_* list, Person* person)
{
  Node *n = Node_new(person);
  insert_before(list->head.next, n);
  List_PersonPtr_Iterator it = List_PersonPtr_it_ctor(list->head.next);
  list->size = list->size + 1;
  return it;
}
List_PersonPtr_Iterator push_back(List_PersonPtr_* list, Person* person)
{
  Node *n = Node_new(person);
  insert_before(&list->head, n);
  List_PersonPtr_Iterator it = List_PersonPtr_it_ctor(list->head.prev);
  list->size = list->size + 1;
  return it;
}

List_PersonPtr_Iterator SortedMerge(List_PersonPtr *list, List_PersonPtr_Iterator begin, List_PersonPtr_Iterator slow, List_PersonPtr_Iterator end)
{
  List_PersonPtr_Iterator middle = slow;
  // A: begin, slow
  // B: slow, end
  while(!List_PersonPtr_Iterator_equal(begin, slow) && !List_PersonPtr_Iterator_equal(middle, end))
  {
    if(list->compare(begin.deref(&begin), middle.deref(&middle)))
    {
      begin.inc(&begin);
    }
    else
    {
      List_Person_Iterator temp = middle;
      middle.inc(&middle);
      temp.node->next = begin.node;
    }
  }
  return slow;
}
List_PersonPtr_Iterator node_sort(List_PersonPtr *list, List_PersonPtr_Iterator begin, List_PersonPtr_Iterator end)
{
  List_PersonPtr_Iterator it_inc = begin;
  it_inc.inc(&it_inc);

  List_PersonPtr_Iterator slow = begin;
  if(!List_PersonPtr_Iterator_equal(it_inc, end)) {
    List_PersonPtr_Iterator fast = begin;
    fast.inc(&fast);
    while(!List_PersonPtr_Iterator_equal(fast,end))
    {
      fast.inc(&fast);
      if(!List_PersonPtr_Iterator_equal(fast,end))
      {
        fast.inc(&fast);
        slow.inc(&slow);
      }
    }
    begin = node_sort(list, begin, slow);
    node_sort(list, slow, end);
  }

  return SortedMerge(list, begin, slow, end);
}

void sort(List_PersonPtr* list)
{
  List_PersonPtr_Iterator end = list->end(list);
  List_PersonPtr_Iterator head = node_sort(list, list->begin(list), end);
  list->head.next = head.node;
}

void erase(List_PersonPtr_* list, List_PersonPtr_Iterator it)
{
  Node *n = it.node;
  n->next->prev = n->prev;
  n->prev->next = n->next;
  list->size = list-> size - 1;
  free(n);
}
void List_PersonPtr_delet(List_PersonPtr* list)
{
  if(list->size == 0)
  {
    /*free(&list->head);*/
    free(list);
  }
  else
  {
    List_PersonPtr_Iterator it = list->begin(list);
    list->erase(list, it);
    List_PersonPtr_delet(list);
  }
}

List_PersonPtr_Iterator List_PersonPtr_begin(List_PersonPtr* list) {
    return List_PersonPtr_it_ctor(list->head.next);
}
List_PersonPtr_Iterator List_PersonPtr_end(List_PersonPtr* list) {
    return List_PersonPtr_it_ctor(&list->head);
}
List_PersonPtr* List_PersonPtr_new(bool (*compare)(const PersonPtr &p1, const PersonPtr &p2))
{
  List_PersonPtr *List = (List_PersonPtr*)malloc(sizeof(List_PersonPtr));
  List->head.next = &List->head;
  List->head.prev = &List->head;
  List->head.person = NULL;
  strcpy(List->type, "List_PersonPtr");
  List->compare = compare;
  List->size = 0;
  List->push_front = push_front;
  List->push_back = push_back;
  List->sort = sort;
  List->erase = erase;
  List->begin = List_PersonPtr_begin;
  List->end = List_PersonPtr_end;
  List->delet = List_PersonPtr_delet;
  return List;
}
