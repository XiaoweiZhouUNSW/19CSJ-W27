CC=gcc
CFLAGS=-Wall -Werror -gdwarf-2
OBJS = graph.o main.o queue.o set.o readData.o

travel : $(OBJS)
	$(CC) $(CFLAGS) -o search $(OBJS)

main.o : main.c
	$(CC)  main.c -c
graph.o : graph.c graph.h
	$(CC)  graph.c graph.h -c
queue.o:queue.c
	$(CC) queue.c -c

set.o: set.c
	$(CC)  set.c -c
readData.o:readData.c set.c queue.c graph.c
	$(CC) readData.c set.c queue.c graph.c -c

clean :
	rm -f travel $(OBJS) core *.dSYM
