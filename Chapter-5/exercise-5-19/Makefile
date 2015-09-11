OBJECTS=main.c gettoken.c get-unget.c declaration.c
OBJECTS1=unmain.c undcl.c gettoken.c get-unget.c declaration.c
FLAGS=-Wall -g
MAIN=word-dcl
MAIN2=word-undcl

$(MAIN): $(OBJECTS)
	cc $(FLAGS) $^ -o $(MAIN)

$(MAIN2): $(OBJECTS1)
	cc $(FLAGS) $^ -o $(MAIN2)

clean:
	rm $(MAIN) $(MAIN2)
