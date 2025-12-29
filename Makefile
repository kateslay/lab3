.PHONY: all clean run start
PROGRAM = lab 
FILES = main.c sortselec.c sortquick.c queue.c
all:
	gcc $(FILES) -o $(PROGRAM)
clean:
	rm -f $(PROGRAM)
run:
	./$(PROGRAM)
start:
	gcc $(FILES) -o $(PROGRAM) 
	./$(PROGRAM)
