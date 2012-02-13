#include "Person.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

void delet_under(Person* person)
{
  Under *under = Person_downcast_Under(person);
  free(under->student.person.name);
  free(under->student.major);
  free(under);
}
void delet_grad(Person* person)
{
  Grad *grad = Person_downcast_Grad(person);
  free(grad->student.person.name);
  free(grad->student.major);
  free(grad->degree);
  free(grad);
}

void delet_professor(Person* person)
{
  Professor *professor = Person_downcast_Professor(person);
  free(professor->person.name);
  free(professor->office);
  free(professor);
}

void research(Professor *professor, const char * topic)
{
   // Must print "<name> does research in <topic>."
  printf("%s does research in %s\n", professor->person.name, topic);
}

void graduate_under(Student *student)
{
  Under *under = Student_downcast_Under(student);
  printf("%s graduates in %d years and finds a job in %s or goes to grad school.\n", under->student.person.name, under->year, under->student.major);
}
void graduate_grad(Student *student)
{
  Grad *grad = Student_downcast_Grad(student);
    printf("%s graduates with a %s and finds a job in %s.\n", grad->student.person.name, grad->degree, grad->student.major);
}


bool type_check_under(const char* type)
{
  if(strcmp(type, "under") == 0)
    return true;
  else if (strcmp(type, "student") == 0)
    return true;
  else if (strcmp(type , "person") == 0)
    return true;

  return false;
}
bool type_check_grad(const char* type)
{
  if(strcmp(type, "grad") == 0)
    return true;
  else if (strcmp(type,"student") == 0)
    return true;
  else if (strcmp(type,"person") == 0)
    return true;

  return false;
}
bool type_check_professor(const char* type)
{
  if(strcmp(type,"professor") == 0)
    return true;
  else if (strcmp(type,"person") == 0)
    return true;
  return false;
}
Student* Person_downcast_Student(Person* person)
{
  if(person->type_check("student"))
  {
    return (Student *)person;
  }
  return NULL;
}
Under* Person_downcast_Under(Person* person)
{
  if(person->type_check("under"))
  {
    return (Under *)person;
  }
  return NULL;
}
Under* Student_downcast_Under(Student* student)
{
  if(student->person.type_check("under"))
  {
    return (Under *)student;
  }
  return NULL;
}
Grad* Person_downcast_Grad(Person* person)
{
  if(person->type_check("grad"))
  {
    return (Grad *)person;
  }
  return NULL;
}
Professor* Person_downcast_Professor(Person* person)
{
  if(person->type_check("professor"))
  {
    return (Professor *)person;
  }
  return NULL;
}
Grad* Student_downcast_Grad(Student* student)
{
  if(student->person.type_check("grad"))
  {
    return (Grad *)student;
  }
  return NULL;
}
void professor_work(Person *person)
{
  printf("%s teaches.\n", person->name);
}

void student_work(Person *person)
{
  //<name> studies <major>
  Student *student = Person_downcast_Student(person);
  printf("%s studies %s\n", student->person.name, student->major);

}
Under* Under_new(char * name, char gender, char * major, int year)
{
  Under *under = (Under*) malloc(sizeof (Under));
  under->student.person.name = strdup(name);
  under->student.person.gender = gender;
  under->student.person.type_check = &type_check_under;
  under->student.person.work = &student_work;
  under->student.person.delet = &delet_under;
  under->student.graduate = &graduate_under;
  under->student.major = strdup(major);
  under->year = year;

  return under;
}

Grad* Grad_new(char * name, char gender, char * major, char * degree)
{
  Grad *grad = (Grad*) malloc (sizeof (Grad));
  grad->student.person.name = strdup(name);
  grad->student.person.gender = gender;
  grad->student.person.type_check = &type_check_grad;
  grad->student.person.work = &student_work;
  grad->student.person.delet = delet_grad;
  grad->student.major = strdup(major);
  grad->student.graduate = &graduate_grad;
  grad->degree = strdup(degree);

  return grad;
}
Professor* Professor_new(char * name, char gender, char * office)
{
  Professor *professor = (Professor*) malloc (sizeof (Professor));
  professor->person.name = strdup(name);
  professor->person.gender = gender;
  professor->person.type_check = &type_check_professor;
  professor->person.work = &professor_work;
  professor->person.delet = &delet_professor;
  professor->research = &research;
  professor->office = strdup(office);
  return professor;
}

