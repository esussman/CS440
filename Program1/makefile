Fig4_1OJECT = YOUR_B_NUMBER
SRC_FILES = \
List.hpp \
Person.cpp \
Person.hpp \
Makefile \
README

a.out: person.o test.o
	g++ -O -Wall -O person.o test.o

test.o: test.cpp List.hpp
	g++ -Wall -O -c test.cpp

person.o: Person.cpp Person.hpp
	g++ -Wall -O -c Person.cpp

#Removes all objects and executables.
clean:
		rm -f  *.out *.o  core *.core *~

#This target makes a archive containing all the project source files,
#suitable for submission.
submit:	$(SRC_FILES)
		tar cvfz $(PROJECT).tar.gz $(SRC_FILES)
