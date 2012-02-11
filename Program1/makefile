Fig4_1OJECT = YOUR_B_NUMBER
SRC_FILES = \
List.hpp \
Person.cpp \
Person.hpp \
Makefile \
README

a.out:
	g++ -g -Wall List.hpp Person.cpp Person.hpp test.cpp

#Removes all objects and executables.
clean:
		rm -f  *.out *.o  core *.core *~

#This target makes a archive containing all the project source files,
#suitable for submission.
submit:	$(SRC_FILES)
		tar cvfz $(PROJECT).tar.gz $(SRC_FILES)
