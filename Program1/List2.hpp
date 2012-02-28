#define List_DEFINE(arg)\
  \
typedef arg* arg##Ptr;\
\
typedef struct Node_##arg##_{\
  Node_##arg##_* next;\
  Node_##arg##_* prev;\
  arg elem;\
} Node_##arg;\
\
typedef struct List_##arg##_Iterator_{\
  Node_##arg* node;\
  arg (*deref)(List_##arg##_Iterator_*);\
  void (*inc)(List_##arg##_Iterator_*);\
  void (*dec)(List_##arg##_Iterator_*);\
} List_##arg##_Iterator;\
\
typedef struct List_##arg##_{\
  Node_##arg head;\
  char type[sizeof("List_" #arg)];\
  int size;\
  bool (*compare)(const arg &p1, const arg &p2);\
  List_##arg##_Iterator (*push_front)(List_##arg##_* , arg);\
  List_##arg##_Iterator (*push_back)(List_##arg##_* , arg);\
  void (*sort)(List_##arg##_*);\
  void (*erase)(List_##arg##_* , List_##arg##_Iterator);\
  List_##arg##_Iterator (*begin)(List_##arg##_* );\
  List_##arg##_Iterator (*end)(List_##arg##_* );\
  void (*delet)(List_##arg##_*);\
}List_##arg;\
\
Node_##arg* Node_##arg##_new(arg elem)\
{\
  Node_##arg *n = (Node_##arg*) malloc (sizeof(Node_##arg));\
  n->next = NULL;\
  n->prev = NULL;\
  n->elem = elem;\
  return n;\
}\
arg Iterator_##arg##_deref(List_##arg##_Iterator_* it)\
{\
  Node_##arg* p = it->node;\
  return p->elem;\
}\
bool List_##arg##_Iterator_equal(List_##arg##_Iterator it1, List_##arg##_Iterator it2)\
{\
  if(it1.node == it2.node)\
    return true;\
  else\
    return false;\
}\
\
\
void List_##arg##_it_inc(List_##arg##_Iterator* it) {\
    it->node = it->node->next;\
}\
void List_##arg##_it_dec(List_##arg##_Iterator* it) {\
  it->node = it->node->prev;\
}\
\
List_##arg##_Iterator List_##arg##_it_ctor(Node_##arg* node)\
{\
  List_##arg##_Iterator it;\
  it.node = node;\
  it.deref = *Iterator_##arg##_deref;\
  it.inc = List_##arg##_it_inc;\
  it.dec = List_##arg##_it_dec;\
  return it;\
}\
void insert_before(Node_##arg* pos, Node_##arg* n)\
{\
  n->next = pos;\
  n->prev = pos->prev;\
  pos->prev->next = n;\
  pos->prev = n;\
}\
List_##arg##_Iterator push_front(List_##arg* list, arg elem)\
{\
  Node_##arg *n = Node_##arg##_new(elem);\
  insert_before(list->head.next, n);\
  List_##arg##_Iterator it = List_##arg##_it_ctor(list->head.next);\
  list->size = list->size + 1;\
  return it;\
}\
List_##arg##_Iterator push_back(List_##arg* list, arg elem)\
{\
  Node_##arg *n = Node_##arg##_new(elem);\
  insert_before(&list->head, n);\
  List_##arg##_Iterator it = List_##arg##_it_ctor(list->head.prev);\
  list->size = list->size + 1;\
  return it;\
}\
\
Node_##arg* node_sort(Node_##arg* list, bool (*compare)(const arg &p1, const arg &p2))\
{\
  int listSize=1,numMerges,leftSize,rightSize;\
    Node_##arg *tail,*left,*right,*next;\
    if (!list || !list->next) return list;\
    do {\
            numMerges=0,left=list;tail=list=0;\
            while (left) {\
                        numMerges++,right=left,leftSize=0,rightSize=listSize;\
                        while (right && leftSize<listSize) leftSize++,right=right->next;\
                        while (leftSize>0 || (rightSize>0 && right)) {\
                                        if (!leftSize)                  {\
                                                          next=right;\
                                                          right=right->next;\
                                                          rightSize--;\
                                                        }\
                                        else if (!rightSize || !right)\
                                        {\
                                                          next=left;\
                                                          left=left->next;\
                                                          leftSize--;\
                                                        }\
                                        else if (compare(left->elem,right->elem))\
                                        {\
                                                          next=left;\
                                                          left=left->next;\
                                                          leftSize--;\
                                                        }\
                                        else\
                                        {\
                                                          next=right;\
                                                          right=right->next;\
                                                          rightSize--;\
                                                        }\
                                        if (tail)\
                                          tail->next=next;\
                                        else list=next;\
                                        next->prev=tail;\
                                        tail=next;\
                                    }\
                        left=right;\
                    }\
            tail->next=0,listSize<<=1;\
        } while (numMerges>1);\
    return list;\
}\
\
void sort(List_##arg* list)\
{\
  list->head.prev->next = NULL;\
  Node_##arg* reattach = node_sort(list->head.next, list->compare);\
  reattach->prev = &list->head;\
  while(reattach->next != NULL)\
  {\
      reattach = reattach->next;\
    }\
  reattach->next = &list->head;\
  list->head.prev = reattach;\
}\
\
void erase(List_##arg##_* list, List_##arg##_Iterator it)\
{\
  Node_##arg *n = it.node;\
  n->next->prev = n->prev;\
  n->prev->next = n->next;\
  list->size = list->size - 1;\
  free(n);\
}\
void List_##arg##_delet(List_##arg* list)\
{\
  if(list->size == 0)\
  {\
      /*free(&list->head);*/\
      free(list);\
    }\
  else\
  {\
      List_##arg##_Iterator it = list->begin(list);\
      list->erase(list, it);\
      List_##arg##_delet(list);\
    }\
}\
\
List_##arg##_Iterator List_##arg##_begin(List_##arg* list) {\
    return List_##arg##_it_ctor(list->head.next);\
}\
List_##arg##_Iterator List_##arg##_end(List_##arg* list) {\
    return List_##arg##_it_ctor(&list->head);\
}\
List_##arg* List_##arg##_new(bool (*compare)(const arg &p1, const arg &p2))\
{\
  List_##arg *List = (List_##arg*)malloc(sizeof(List_##arg));\
  List->head.next = &List->head;\
  List->head.prev = &List->head;\
  List->compare = compare;\
  List->size = 0;\
  strcpy(List->type, "List_" #arg);\
  List->push_front = push_front;\
  List->push_back = push_back;\
  List->sort = sort;\
  List->erase = erase;\
  List->begin = List_##arg##_begin;\
  List->end = List_##arg##_end;\
  List->delet = List_##arg##_delet;\
  return List;\
}

