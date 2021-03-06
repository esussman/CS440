#ifndef PERSONISHERE

#define PERSONISHERE

typedef struct Person_
{
  char *name;
  char gender;
  void (*work)(Person_ * person);
  bool (*type_check)(const char* type);
  void (*delet)(Person_ * person);
} Person;

typedef struct Student_
{
  Person person;
  char *major;
  void (*graduate)(Student_ *student);
} Student;

typedef struct Under_
{
  Student student;
  int year;
} Under;

typedef struct Grad_
{
  Student student;
  char *degree;
} Grad;

typedef struct Professor_
{
  Person person;
  char *office;
  void (*research)(Professor_ *professor, const char * topic);
} Professor;

Under* Under_new(const char* name, char gender, const char* major, int year);
Grad* Grad_new(const char* name, char gender, const char* major, const char* degree);
Professor* Professor_new(const char* name, char gender, const char* office);
Student* Person_downcast_Student(Person* person);
Under* Person_downcast_Under(Person* person);
Under* Student_downcast_Under(Student* student);
Grad* Person_downcast_Grad(Person* person);
Professor* Person_downcast_Professor(Person* person);
Grad* Student_downcast_Grad(Student* student);

#endif
