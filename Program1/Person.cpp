#include "Person.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

bool type_check_under(const char* type)
{
  if(type == "under")
    return true;
  else if (type == "student")
    return true;
  else if (type == "person")
    return true;
  return false;
}
Student* Person_downcast_Student(Person* person)
{

}
Under* Person_downcast_Under(Person* person)
{

}
Under* Student_downcast_Under(Student* student)
{

}
Grad* Person_downcast_Grad(Person* person)
{

}
Professor* Person_downcast_Professor(Person* person)
{

}
Grad* Student_downcast_Grad(Student* student)
{

}
void professor_work(Person *person)
{
  //printf("%s studies %s");

}

void student_work(Person *person)
{
  //printf("%s studies %s");

}
Under* Under_new(char * name, char gender, char * major, int year)
{
  Under *under = (Under*) malloc(sizeof (Under));
  under->student.person.name = name;
  under->student.person.gender = gender;
  under->student.person.work = &student_work;
  under->student.major = major;
  under->year = year;

  return under;
}

Grad* Grad_new(char * name, char gender, char * major, char * degree)
{
  Grad *grad = (Grad*) malloc (sizeof (Grad));
  grad->student.person.name = name;
  grad->student.person.gender = gender;
  grad->student.person.work = &student_work;
  grad->student.major = major;
  grad->degree = degree;

  return grad;
}
Professor* Professor_new(char * name, char gender, char * office)
{
  Professor *professor = (Professor*) malloc (sizeof (Professor));
  professor->person.name = name;
  professor->person.gender = gender;
  professor->person.work = &professor_work;
  professor->office = office;
  return professor;
}

