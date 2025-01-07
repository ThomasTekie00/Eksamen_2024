#ifndef STACK_H_
#define STACK_H_


//Node struktur som kan holde enten heltall eller strenger
typedef struct Node {
  //"bool", forteller hva som er hva: Tekst = 1, og tall = 0
  int is_string;
  //for heltall  
  int value;
  //for strenger       
  char *string;    

  //Peker for neste node
  struct Node *next;

} node_t;


//Selve stack "hodet"
typedef struct stack {
  //Peler til toppen(noden) av stacken
  node_t *head;

} stack_t;


//Lager en ny og tom stack
stack_t *stack_create();

//Legger(pusher) til en ny node på toppen
//Enten tall eller tekst
void stack_push(stack_t *stack, int value, const char *string);

// Fjerner elementet fra toppen av stacken, og gir ut det som var på toppen
node_t *stack_pop(stack_t *stack);

// Frigjører minne som brukes av stacken
void stack_free(stack_t *stack);
#endif
