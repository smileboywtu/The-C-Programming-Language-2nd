OBJECTS=operation.h polish-calculate.c get-unget.c stack.c gettop.c variable.c
MAIN=polish-calculation
FLAGS=-Wall -g 

$(MAIN): $(OBJECTS)
	cc $(FLAGS) $^ -o $(MAIN) -lm

clean:
	rm $(MAIN)
