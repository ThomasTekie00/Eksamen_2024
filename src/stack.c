#include "../inc/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Referanser:
https://craftinginterpreters.com/scanning.html for stack operasjoner
https://www.geeksforgeeks.org/implement-a-stack-using-singly-linked-list/
https://stackoverflow.com/questions/1919975/creating-a-stack-of-strings-in-c
*/

// Hele stacken inspirert av
// Arbeidskrav 4, Høsten 2024

// Lager en ny tom stack
stack_t *stack_create() {
    //Allokerer minne
  stack_t *new_stack = malloc(sizeof(stack_t));
    //Dersom det ikke er minne allokering feiler
  if (new_stack == NULL) {
    printf("Memory error for stack\n");
    //Avslutter programmet
    exit(1);
  }
  // Toppen settes til NULL siden den er tom
  new_stack->head = NULL;
  return new_stack;
}

void stack_push(stack_t *stack, int value, const char *string) {
  // Lager en ny node, og allokerer minne for den
  node_t *new_node = malloc(sizeof(node_t));

  if (new_node == NULL) {
    printf("Memory error");
    exit(1);
  }
  // tekst håndtering
  if (string) {
    // Kopierer teksten, slik at stacken har en egen versjon
    new_node->string = strdup(string);
    // Her blir den nye noden markert med 1 siden den inneholder en streng
    new_node->is_string = 1;

  } else { // Dersom det er et tall
    // Noden får inn verdien og lagrer den
    new_node->value = value;
    // Siden det er et tall, så blir string pointeren satt til NULL
    new_node->string = NULL;
    // Siden det er et tall, så blir den markert med 0, inneholder tall
    new_node->is_string = 0;
  }
  // Legger noden på toppen av stacken
  new_node->next = stack->head;
  // Den nye noden blir satt til den nye toppen(Hodet)
  stack->head = new_node;
}

node_t *stack_pop(stack_t *stack) 
{
  // Sjekker om stacken er tom
  if (stack->head == NULL) {
    printf("Stack is empty\n");
    exit(1);
  }

  // Holder på noden på toppen av stacken siden den skal returneres
  node_t *top_node = stack->head;

  // Nye toppen blir neste node, den som var under den som ble poppet
  stack->head = top_node->next;

  return top_node;
}

// Frigjører stacken og noden
void stack_free(stack_t *stack) 
{
  // Reseter dersom den er NULL
  if (stack == NULL) {
    return;
  }

  // Går gjennom stacken og frigjør noder
  while (stack->head) 
  {
    // Holder på noden som er på toppen, slik at head kan flyttes på uten å
    // miste verdien
    node_t *node_free = stack->head;

    // Nye head blir noden under, mens node_free peker på head
    stack->head = node_free->next;

    // Dersom noden inneholder tekst, så blir teksten frigjort først
    if (node_free->is_string) {
      free(node_free->string);
    }

    // Noden frigjøres trygt siden den ikke er i stacken
    free(node_free);
  }

  // Frigjør stacken
  free(stack);
}