#include "../inc/operasjoner.h"
#include "../inc/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*interpreter.c -
Referanser:
https://www.geeksforgeeks.org/c-switch-statement/ for struktur
https://www.youtube.com/watch?v=A3gTw1ZkeK0&t=452s

Bøker: 
"The C Programming Language (K&R) Kap 3 og 4"
https://craftinginterpreters.com/: Kap 4.5.2, 7.4
*/

void interpret(char **program) {
  // Lager stacken for interpreteren
  stack_t *stack = stack_create();

  // Program counter holder styr på token i programmet
  int pc = 0;

  // Løkken som går gjennom alle strengene(token)
  while (program[pc] != NULL) {
    char *token = program[pc];



    // Håndter positive og negative tall
    //Første tegnet '-' eller mellom 0 og 9, tolkes som tall
    if (token[0] == '-' || (token[0] >= '0' && token[0] <= '9')) {
      //Pusher det på stacken
      stack_push(stack, atoi(token), NULL);
    }

    // Om token begynner med '~', så blir det tolket som en streng
    else if (token[0] == '~') {
      // Hopper over '~'
      token++;

      // Finner slutten av strengen med å se etter '~'
      char *end = strchr(token, '~');

      // Når den finner '~', så blir den byttet til null karakter(Usynlig)
      if (end)
        *end = '\0';

      // Pusher strengen til stacken
      stack_push(stack, 0, token);

      //Går videre til neste token
      pc++;
      continue;
    }

  
    /* Inspirert av kapitel 4 fra C programming og https://craftinginterpreters.com/: Kap 4.5.2, 7.4  */
    // Håndterer operasjonene som starter med '.': 
    else if (token[0] == '.') {
      switch (token[1]) {
      // Addisjon
      case '+':
        stack_add(stack);
        break;

      // Subtraksjon
      case '-':
        stack_minus(stack);
        break;

      // Multiplikasjon
      case '*':
        stack_multi(stack);
        break;

      // Divisjon
      case '/':
        stack_divide(stack);
        break;

      //.mod, modulo
      case 'm':
        if (token[2] == 'o')
          stack_modulo(stack);
        break;

      // .=?, likhet sjekk
      case '=':
        if (token[2] == '?')
          stack_equal(stack);
        break;

      // .>?, greater than sjekk
      case '>':
        if (token[2] == '?')
          stack_greater(stack);
        break;

      //.dup sjekk
      case 'd':
        if (token[2] == 'u')
          stack_dup(stack);
        break;

      // .swap sjekk
      case 's':
        if (token[2] == 'w')
          stack_swap(stack);
        break;

      //.print sjekk
      case 'p':
        if (token[2] == 'r') {
          stack_print(stack);
        }
        break;

      //.newline sjekk
      //forenkle til bare n
      case 'n':
        if (token[2] == 'e' && token[3] == 'w')
          stack_newline();
        break;


      //Koden er hentet og inspirert av "https://unstop.com/blog/jump-statement-in-c?redirecting=true"
      //.cjump sjekk
      case 'c':
        if (token[2] == 'j') {
          // Antall hopp
          node_t *jump_node = stack_pop(stack);
          node_t *condition_node = stack_pop(stack);

          // Utfører hvis jump_condition ikke er 0, og hopper antall "jumps" gir
          if (condition_node->value != 0 ) {
            pc += jump_node->value;
            continue;
          }
          free(jump_node);
          free(condition_node);
          
          break;
        }
      }
    }
    // Øker for å gå videre til neste token
    pc++;
  }
  // Frigjør stacken
  stack_free(stack);
}
