#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc/lexer_preprocessor.h"
#include "inc/interpreter.h"

char **program;


int main(int argc, char **argv) {

  if (argc < 2) {
    printf("no program supplied\n");
    return 0;
  }

  // program is an array of strings; the end of the program is signified by a
  // NULL pointer.
  program = load_program(argv[1]);

  // prints out the words in the program array; uncomment to get an idea of how
  // the program is stored in memory.
  //for (char **pc = program; *pc != NULL; pc++) {
  //printf("program[%i]: %s\n", (int) (pc - program), *pc);
   //}


  interpret(program);

  for(int i = 0; program[i] != NULL; i++){
   free(program[i]);
  }

  free(program);

  return 0;
}
