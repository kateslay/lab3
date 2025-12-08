.PHONY: all clean run
PROGRAM = lab
FILES = main.c library.c
all:
	gcc $(FILES) -o $(PROGRAM)
clean:
	del $(PROGRAM)
run:
	./$(PROGRAM)