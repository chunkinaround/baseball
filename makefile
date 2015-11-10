OBJS =baseball.o
C_FLAGS =-Wall 
C_FILES =baseball.c
LIBS =-lncurses

all:
	gcc $(C_FILES) $(C_FLAGS) $(LIBS) -o $(OBJS)

clean:
	rm -f $(OBJS)
