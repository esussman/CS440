typedef struct Node_{
	Node_ *next;
	Node_ *prev; //maybe

  Person person;

} Node;

typedef struct List_PersonPtr_Iterator_{
	Node *mynode;
  Person* (*deref)(List_PersonPtr_Iterator_ *it);
  List_PersonPtr_Iterator_ (*inc)(List_PersonPtr_Iterator_ *it);
} List_PersonPtr_Iterator;

typedef Person *PersonPtr;

typedef struct List_PersonPtr_{
	Node *head;
  Node *last;
  char *type;

  bool (*PersonPtr_less)(const PersonPtr &p1, const PersonPtr &p2);
  List_PersonPtr_Iterator (*begin)(List_PersonPtr_ *list);
  List_PersonPtr_Iterator (*end)(List_PersonPtr_ *list);

}List_PersonPtr;

bool List_PersonPtr_Iterator_equal (List_PersonPtr_Iterator_ first_it, List_PersonPtr_Iterator_ second_it);
List_PersonPtr* List_PersonPtr_new(bool (*PersonPtr_less)(const PersonPtr &p1, const PersonPtr &p2));
