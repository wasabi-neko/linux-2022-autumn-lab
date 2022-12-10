CC = gcc
CFLAGS = -Wall -O1
SRCS = my_syscall.c get_layout.c
OBJS = my_syscall.o get_layout.o
MAIN = main.c
EXE = main.out

all: $(EXE)

run: all
	./$(EXE)

clean:
	-rm *.o
	-rm $(EXE)


$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(MAIN) -o $(EXE) $(OBJS)

$(OBJS):
	$(CC) $(CFLAGS) -c $(SRCS)