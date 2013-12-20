PREFIX= ./

INCDIR = $(PREFIX)include/
SRCDIR = $(PREFIX)src/
TESTDIR = $(PREFIX)tests/
MODULEDIR = $(PREFIX)module/
MAINDIR = $(PREFIX)main/

#le compilateur
CC= gcc

#les flags de compilation
CFLAGS= -std=c99 -g -Wall -Werror -pg

#les flags du preprocesseur pour les modules et algo
CPFLAGS= -I $(INCDIR)

#les flags de l'editeur de liens 
LDFLAGS= -L -pg -g

#les librairies utilisees 
LDLIBS= -lm

#Le nom du fichier executable a generer
OUTFILE= vertexCoverExec
OUTFILE2= minisatExec
OUTFILE3 = testExec

#les fichiers objets a generer 
OBJS= graph.o list.o fileReader.o cover.o generation.o

#les dependances 
all: $(OUTFILE)
	rm -f $(INCDIR)*~ $(SRCDIR)*~ $(INCDIR)*~ $(TESTDIR)*~ ./*~ ./*.o

clean:
	rm -f $(INCDIR)*~ $(SRCDIR)*~ $(INCDIR)*~ $(TESTDIR)*~ ./*~ ./*.o

testGraph: graph_test
	rm -f $(INCDIR)*~ $(SRCDIR)*~ $(INCDIR)*~ $(TESTDIR)*~ ./*~ ./*.o

testList: list_test
	rm -f $(INCDIR)*~ $(SRCDIR)*~ $(INCDIR)*~ $(TESTDIR)*~ ./*~ ./*.o

testTime: time_test
	rm -f $(INCDIR)*~ $(SRCDIR)*~ $(INCDIR)*~ $(TESTDIR)*~ ./*~ ./*.o

minisatExec: minisat_exec
	rm -f $(INCDIR)*~ $(SRCDIR)*~ $(INCDIR)*~ $(TESTDIR)*~ ./*~ ./*.o


vertexCoverExec: $(OBJS) main.o
	$(CC) $(OBJS) main.o $(LDFLAGS) $(LDLIBS) -o $(OUTFILE)
graph_test: $(OBJS) graph_tester.o
	$(CC) $(OBJS) graph_tester.o $(LDFLAGS) $(LDLIBS) -o $(OUTFILE)
list_test: $(OBJS) list_tester.o
	$(CC) $(OBJS) list_tester.o $(LDFLAGS) $(LDLIBS) -o $(OUTFILE)
time_test: $(OBJS) timeTests.o
	$(CC) $(OBJS) timeTests.o $(LDFLAGS) $(LDLIBS) -o $(OUTFILE3)
minisat_exec: $(OBJS) minisat.o
	$(CC) $(OBJS) minisat.o $(LDFLAGS) $(LDLIBS) -o $(OUTFILE2)


main.o: $(SRCDIR)main.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $(SRCDIR)main.c
graph.o: $(SRCDIR)graph.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $(SRCDIR)graph.c
list.o: $(SRCDIR)list.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $(SRCDIR)list.c
fileReader.o: $(SRCDIR)fileReader.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $(SRCDIR)fileReader.c
cover.o: $(SRCDIR)cover.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $(SRCDIR)cover.c
generation.o: $(SRCDIR)generation.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $(SRCDIR)generation.c

graph_tester.o: $(TESTDIR)graph_tester.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $(TESTDIR)graph_tester.c
list_tester.o: $(TESTDIR)list_tester.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $(TESTDIR)list_tester.c
timeTests.o: $(TESTDIR)timeTests.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $(TESTDIR)timeTests.c
minisat.o: $(SRCDIR)minisat.c
	$(CC) $(CFLAGS) $(CPFLAGS) -c $(SRCDIR)minisat.c