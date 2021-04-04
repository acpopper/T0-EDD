#include <stdio.h>
#include <stdlib.h>

typedef struct persona {
  int id;
  int state;
  struct persona* parent;
  struct persona* head;
  struct persona* tail;
  struct persona* prev;
  struct persona* next;
} Persona;

Persona* persona_init(int id, int state)
{
  // Pedimos memoria para la lista
  Persona* persona = malloc(sizeof(Persona));

  // Inicializamos la lista directamente
  *persona = (Persona) {
    .id = id,
    .state = state,
    .parent = NULL,
    .head = NULL,
    .tail = NULL,
    .prev = NULL,
    .next = NULL,
  };

  return persona;
}

void persona_print(Persona* persona,int n)
{
  printf("%*s %i:%i\n", n, "", persona->id, persona->state);
  Persona* current = persona->head;
  while (current){
    persona_print(current, n+3);
    current = current->next;
  }
  
}

void persona_append(Persona* persona, int id, int state)
{
 
  Persona *new_persona = persona_init(id, state);
  new_persona->parent = persona;
  
  if (!persona->head) {
      persona->head = new_persona;
  }
  else {
      new_persona->prev = persona->tail;
      persona->tail->next = new_persona;
  }
  persona->tail = new_persona;
}

Persona* search_contact(Persona* persona, int id){
        Persona* current = persona->head;
        while(current){
          if(current->id==id){
            // printf("Persona: %i:%i\n", current->id, current->state); //Uncomment for print
            return current;
          }   
            current = current->next;
        }
        return NULL;
}


//Testeamos el codigo
// int main(int argc, char** argv)
// {
  // // Creamos una persona
  // Persona* persona = persona_init(0, 0);

  // // Agregamos algunos valores
  // persona_append(persona, 1, 1);
  // persona_append(persona, 2, 2);
  // persona_append(persona, 3, 3);
  // persona_append(persona->tail, 4, 4);
  // persona_append(persona->tail, 5, 5);
  // persona_append(persona->head, 6, 6);

  // // Imprimos la lista
  // persona_print(persona, 0);

  // search_contact(persona->tail, 5);


//   return 0;
// }