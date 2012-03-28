.PHONY: all
all: parser_test gen

.PHONY: gen
gen:
	g++ -O -Wall -Wno-unused -o gen XmlGenerator.cpp gen.cpp

.PHONY: parser_test
# Use -O or -O5 for performance testing.  Don't compile with -DNDEBUG, because
# it will compile out the asserts that check for bad XML.
parser_test:
	g++ -g -Wall -Wno-unused -o parser_test parser_test.cpp Element.cpp Parser.cpp String.cpp Text.cpp Node.cpp

clean:
	rm -rf gen parser_test *.o
