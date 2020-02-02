CC = g++
CCFLAGS = -g -W -Wall

FLEX = flex
FLEX_OPTS = -PnxTas

BISON = bison
BISON_OPTS = -t -pnxTas

OBJS = Absyn.o Lexer.o Parser.o Printer.o

.PHONY: clean distclean

all: TestnxTas

clean:
	rm -f *.o TestnxTas nxTas.aux nxTas.log nxTas.pdf nxTas.dvi nxTas.ps nxTas

distclean: clean
	rm -f Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H Makefile nxTas.l nxTas.y nxTas.tex 

TestnxTas: ${OBJS} Test.o
	@echo "Linking TestnxTas..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o TestnxTas

Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: nxTas.l
	${FLEX} -oLexer.C nxTas.l

Parser.C: nxTas.y
	${BISON} nxTas.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.C

Test.o: Test.C Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.C

