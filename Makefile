# add your source files here:
SRC := src/interpreter.c src/lexer_preprocessor.c src/operasjoner.c src/stack.c

# add your header files here
INC := inc/interpreter.h inc/lexer_preprocessor.h inc/operasjoner.h inc/stack.h
# FLAGS := -g

8inf: 8inf.c $(SRC) $(INC)
	gcc $(FLAGS) -Iinc 8inf.c $(SRC) -o 8inf

clean:
	rm 8inf

.PHONY: clean
