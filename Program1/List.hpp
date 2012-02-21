typedef struct Node_{
	Node_ *next;
	Node_ *prev; //maybe
} Node;

typedef struct Iterator_{
	Node *mynode;
} Iterator;

typedef struct List_{
	Node *head;
  Node *last;
}List;
