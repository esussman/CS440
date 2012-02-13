typedef struct Person_
{
  char *name;
  char gender;
  void (*work)(Person_ * person);
  bool (*type_check)(const char* type);
  ~Person_();
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

Under* Under_new(char * name, char gender, char * major, int year);
Grad* Grad_new(char * name, char gender, char * major, char * degree);
Professor* Professor_new(char * name, char gender, char * office);
Student* Person_downcast_Student(Person* person);
Under* Person_downcast_Under(Person* person);
Under* Student_downcast_Under(Student* student);
Grad* Person_downcast_Grad(Person* person);
Professor* Person_downcast_Professor(Person* person);
Grad* Student_downcast_Grad(Student* student);

