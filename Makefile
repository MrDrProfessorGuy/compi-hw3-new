.PHONY: all clean

all: clean
	flex scanner.lex
	/usr/local/opt/bison/bin/bison -Wcounterexamples -d parser.ypp
clean:
	rm -f lex.yy.c
	rm -f parser.tab.*pp
	rm -f hw3
