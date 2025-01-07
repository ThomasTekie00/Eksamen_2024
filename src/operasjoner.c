#include "../inc/operasjoner.h"
#include "../inc/stack.h"
#include <stdio.h>
#include <stdlib.h>

/*Referanser:
https://craftinginterpreters.com/: 7.3.1 (Detecting Runtime)
https://www.youtube.com/watch?v=P5YWUXrPEyw&t=507s

Inspirert av: 
https://www.geeksforgeeks.org/prefix-postfix-conversion/?ref=shm
https://craftinginterpreters.com/: 7.3.1 (Detecting Runtime)*/

// Addisjon
void stack_add(stack_t *stack) 
{
  // Andre element, hele noden nr 2 på stacken
  node_t *element_b = stack_pop(stack);

  // Øverste element, hele noden nr 1 på stack
  node_t *element_a = stack_pop(stack);
  // Resultat til begge: Henter verdiene som er i nodene og plusser
  int result = element_a->value + element_b->value;

  // Pusher resultat til stacken
  stack_push(stack, result, NULL);
  // Frigjør begge nodene siden vi er ferdig med de
  free(element_a);
  free(element_b);
}

// Subtraksjon
void stack_minus(stack_t *stack) 
{
  // Andre element, hele noden nr 2 på stacken
  node_t *element_b = stack_pop(stack);
  // Øverste element, hele noden nr 1 på stacken
  node_t *element_a = stack_pop(stack);
  // Resultat til begge: Henter verdiene som er i nodene og subtraherer
  int result = element_a->value - element_b->value;
  // Pusher resultat til stacken
  stack_push(stack, result, NULL);
  // Frigjør begge nodene siden vi er ferdig med de
  free(element_a);
  free(element_b);
}
// Multiplikasjon
void stack_multi(stack_t *stack) 
{
  // Andre element i stacken, hele noden
  node_t *element_b = stack_pop(stack);
  // Øverste element i stacken, hele noden
  node_t *element_a = stack_pop(stack);
  // Resultat til begge: Henter verdiene som er i nodene og multipliserer
  int result = element_a->value * element_b->value;
  // Pusher resultat til stacken
  stack_push(stack, result, NULL);
  // Frigjør begge nodene siden vi er ferdig med de
  free(element_a);
  free(element_b);
}

// Divisjon
void stack_divide(stack_t *stack) 
{
  // Øverste element i stacken, hele noden
  node_t *element_a = stack_pop(stack);
  // Sjekker om noden er lik 0, dersom den er det så kommer error, og den
  // frigjøres
  if (element_a->value == 0) {
    printf("Dividing by 0\n");
    // Avslutter programmet
    exit(1);
  }
  // Andre element i stacken, hele noden
  node_t *element_b = stack_pop(stack);
  // Resultat til begge: Henter verdiene som er i nodene og deler
  int result = element_b->value / element_a->value;

  // Pusher resultat til stacken
  stack_push(stack, result, NULL);

  free(element_a);
  free(element_b);
}

// Modulo
void stack_modulo(stack_t *stack) 
{
  // Andre element i stacken, hele noden
  node_t *element_b = stack_pop(stack);

  // Sjekker verdien som pointeren peker på
  if (element_b->value == 0) {
    printf("Error: Modulo by zero\n");
    exit(1);
  }
  // Øverste element i stacken, hele noden
  node_t *element_a = stack_pop(stack);

  // Resultat til begge: Henter verdiene som er i nodene og finner rest
  int result = element_a->value % element_b->value;

  // Pusher resultat til stacken
  stack_push(stack, result, NULL);

  free(element_a);
  free(element_b);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Likhet
void stack_equal(stack_t *stack) 
{
  // Andre element i stacken, hele noden
  node_t *element_b = stack_pop(stack);
  // Øverste element i stacken, hele noden
  node_t *element_a = stack_pop(stack);

  // Sammenligner verdiene fra begge nodene, pusher 1 dersom a og b er like
  if (element_a->value == element_b->value) {
    stack_push(stack, 1, NULL);

  } else

  { // Pusher 0, dersom de ikke er like
    stack_push(stack, 0, NULL);
  }

  free(element_a);
  free(element_b);
}

// Større enn
void stack_greater(stack_t *stack) 
{
  // Andre element i stacken, hele noden
  node_t *element_b = stack_pop(stack);
  // Øverste element i stacken, hele noden
  node_t *element_a = stack_pop(stack);

  // Sammenligner verdiene fra nodene, og pusher 1 dersom a er større enn b
  if (element_a->value > element_b->value) {
    // Pusher resultat til stacken
    stack_push(stack, 1, NULL);

  } else

  {
    // Pusher 0, dersom a ikke er større enn b
    stack_push(stack, 0, NULL);
  }
  free(element_a);
  free(element_b);
}

//.dup: Lager en kopi av øverste node + verdien
void stack_dup(stack_t *stack) 
{
  // Øverste node skal kopieres, dersom det ikke er noe der, så avsluttes
  // programmet
  if (stack->head == NULL)
    exit(1);

  // Kopiere den og popper den
  node_t *top_node = stack_pop(stack);
  // Deretter pushes begge tilbake på stacken
  stack_push(stack, top_node->value, NULL);
  stack_push(stack, top_node->value, NULL);

  free(top_node);
}

//.swap: Bytter plass på de to øverste verdiene
void stack_swap(stack_t *stack) 
{

  // Popper de to øverste på stacken.
  node_t *element_a = stack_pop(stack);
  node_t *element_b = stack_pop(stack);

  // Siden det er en "Last in First out" stack, så kommer de inn i motsatt
  // rekkefølge: fra 1 2 -> 2 1
  // Pusher til stacken
  stack_push(stack, element_a->value, NULL);
  stack_push(stack, element_b->value, NULL);

  free(element_a);
  free(element_b);
}

// Språkets printf: .print
void stack_print(stack_t *stack) 
{
  if (stack->head == NULL)
    exit(1);

  // Øverste poppes, dersom det er en streng, så blir det markert som streng til
  // string
  node_t *top_node = stack_pop(stack);
  if (top_node->is_string) {
    printf("%s", top_node->string);
    free(top_node->string);

  } else {
    // Om det er et tall, så legges den i value
    printf("%d", top_node->value);
  }

  free(top_node);
}

// Språkets "\n" -> linjebytte
void stack_newline() 
{ 
  printf("\n"); 
}