/*typedef struct Link_ {
  Link_ *next, *prev;
  int sent;
} Link;
*/
typedef struct Node_{
	Node_ *next, *prev;
  Person *person;

} Node;

typedef struct List_PersonPtr_Iterator_{
	Node *node;
  Person* (*deref)(List_PersonPtr_Iterator_ *it);
  void (*inc)(List_PersonPtr_Iterator_ *it);
  void (*dec)(List_PersonPtr_Iterator_ *it);
} List_PersonPtr_Iterator;

typedef Person* PersonPtr;

typedef struct List_PersonPtr_{
  Node *head;
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

Node* Node_new(Person *person)
{
  Node *n = (Node*) malloc (sizeof(Node));
  n->next = NULL;
  n->prev = NULL;
  n->person = person;
  return n;
}
Person* deref(List_PersonPtr_Iterator_ *it)
{
  Node *n = it->node;
  return n->person;
}
bool List_PersonPtr_Iterator_equal (List_PersonPtr_Iterator it1, List_PersonPtr_Iterator it2)
{
  if(it1.node == it2.node)
    return true;
  else
    return false;
}


void it_inc (List_PersonPtr_Iterator_ *it)
{
  it->node = it->node->next;
}
void it_dec (List_PersonPtr_Iterator_ *it)
{
  it->node = it->node->prev;
}

List_PersonPtr_Iterator List_PersonPtr_it_ctor(Node *node)
{
  List_PersonPtr_Iterator it;
  it.node = node;
  it.deref = deref;
  it.inc = it_inc;
  it.dec = it_dec;
  return it;
}
void insert_before(Node *pos, Node *n)
{
  n->next = pos;
  n->prev = pos->prev;
  pos->prev->next = n;
  pos->prev = n;
}
List_PersonPtr_Iterator push_front(List_PersonPtr_ *list, Person *person)
{
  Node *n = Node_new(person);
  insert_before(list->head->next, n);
  List_PersonPtr_Iterator it = List_PersonPtr_it_ctor(list->head->next);
  return it;
}
List_PersonPtr_Iterator push_back(List_PersonPtr_ *list, Person *person)
{
  Node *n = Node_new(person);
  insert_before(list->head, n);
  List_PersonPtr_Iterator it = List_PersonPtr_it_ctor(list->head->prev);
  return it;
}

Node* node_sort(Node * list, bool (*PersonPtr_less)(const PersonPtr &p1, const PersonPtr &p2))
{
  int listSize=1,numMerges,leftSize,rightSize;
    Node *tail,*left,*right,*next;
    if (!list || !list->next) return list;  // Trivial case

    do { // For each power of two<=list length
        numMerges=0,left=list;tail=list=0; // Start at the start

        while (left) { // Do this list_len/listSize times:
            numMerges++,right=left,leftSize=0,rightSize=listSize;
            // Cut list into two halves (but don't overrun)
            while (right && leftSize<listSize) leftSize++,right=right->next;
            // Run through the lists appending onto what we have so far.
            while (leftSize>0 || (rightSize>0 && right)) {
                // Left empty, take right OR Right empty, take left, OR compare.
                if (!leftSize)                  {
                  next=right;
                  right=right->next;
                  rightSize--;
                }
                else if (!rightSize || !right)
                {
                  next=left;
                  left=left->next;
                  leftSize--;
                }
                else if (PersonPtr_less(left->person,right->person))
                {
                  next=left;
                  left=left->next;
                  leftSize--;
                }
                else
                {
                  next=right;
                  right=right->next;
                  rightSize--;
                }
                // Update pointers to keep track of where we are:
                if (tail)
                  tail->next=next;
                else list=next;
                // Sort prev pointer
                next->prev=tail; // Optional.
                tail=next;
            }
            // Right is now AFTER the list we just sorted, so start the next sort there.
            left=right;
        }
        // Terminate the list, double the list-sort size.
        tail->next=0,listSize<<=1;
    } while (numMerges>1); // If we only did one merge, then we just sorted the whole list.
    return list;
}

void sort(List_PersonPtr *list)
{
  list->head->prev->next = NULL;
  Node *reattach = node_sort(list->head->next, list->PersonPtr_less);
  reattach->prev = list->head;
  while(reattach->next != NULL)
  {
    reattach = reattach->next;
  }
  reattach->next = list->head;
  list->head->prev = reattach;
}

void erase(List_PersonPtr_ *list, List_PersonPtr_Iterator it)
{
  Node *n = it.node;
  n->next->prev = n->prev;
  n->prev->next = n->next;
  free(n);
}

/*void List_PersonPtr_delet(List_PersonPtr *list)
{
  List_PersonPtr_Iterator it = list->begin(list);
  List_PersonPtr_Iterator it2 = list->end(list);
  it2.dec(&it2);
  while(!List_PersonPtr_Iterator_equal(it,it2))
  {
    it.inc(&it);
    list->erase(list,it);
  }
  free(list->begin(list).node);
  free(list->head);
  free(list);
}*/
void List_PersonPtr_delet(List_PersonPtr *list)
{
  //Check to see if the next node is also the sentinel node.
  if(list->head->next->person == NULL)
  {
    free(list->head);
    free(list);
  }
  else
  {
    List_PersonPtr_Iterator it = list->begin(list);
    list->erase(list, it);
    List_PersonPtr_delet(list);
  }
}

List_PersonPtr_Iterator List_PersonPtr_begin(List_PersonPtr *list) {
    return List_PersonPtr_it_ctor(list->head->next);
}
List_PersonPtr_Iterator List_PersonPtr_end(List_PersonPtr *list) {
    return List_PersonPtr_it_ctor(list->head);
}
void List_PersonPtr_it_inc(List_PersonPtr_Iterator *it) {
    it->node = it->node->next;
}
List_PersonPtr* List_PersonPtr_new(bool (*PersonPtr_less)(const PersonPtr &p1, const PersonPtr &p2))
{
  List_PersonPtr *List = (List_PersonPtr*)malloc(sizeof(List_PersonPtr));
  List->type = "List_PersonPtr";
  Node *sentinel = (Node*) malloc (sizeof(Node));
  sentinel->next = sentinel;
  sentinel->prev = sentinel;
  sentinel->person = NULL;
  List->head = sentinel;
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
