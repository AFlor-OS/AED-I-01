EXECUTAVEL = main

all:
	@gcc *.c -o $(EXECUTAVEL)

run: all
	@./$(EXECUTAVEL)