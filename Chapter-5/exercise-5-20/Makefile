OBJECTS=main.c gettoken.c get-unget.c declaration.c
FLAGS=-Wall -g
MAIN=word-dcl

$(MAIN): $(OBJECTS)
	cc $(FLAGS) $^ -o $(MAIN)

clean:
	rm $(MAIN)
