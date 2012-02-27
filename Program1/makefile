Fig4_1OJECT = YOUR_B_NUMBER
SRC_FILES = \
List.hpp \
Person.cpp \
Person.hpp \
Makefile \
README

a.out: person.o test.o
	g++ -g -Wall person.o test.o

test.o: test.cpp list.hpp
	g++ -Wall -g -c test.cpp

person.o: Person.cpp Person.hpp
	g++ -Wall -g -c Person.cpp

#Removes all objects and executables.
clean:
		rm -f  *.out *.o  core *.core *~

#This target makes a archive containing all the project source files,
#suitable for submission.
submit:	$(SRC_FILES)
		tar cvfz $(PROJECT).tar.gz $(SRC_FILES)
