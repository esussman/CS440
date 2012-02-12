typedef struct Person_
{
  char *name;
  char gender;
  bool (*type_check)(const char*);
} Person;

typedef struct Student_
{
  Person p;
  char *major;
} Student;

typedef struct Under_
{
  Student s;
  int year;
} Under;

typedef struct Grad_
{
  Student s;
  char *degree;
} Grad;

typedef struct Professor_
{
  Person p;
  char *office;
} Professor;

Under* Under_new(char * name, char gender, char * major, int year);
