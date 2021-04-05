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

void persona_print(Persona* persona,int n, FILE *output)
{ 
  fprintf(output, "%*s %i:%i\n", n, "", persona->id, persona->state);
  Persona* current = persona->head;
  
  
  while (current){
    persona_print(current, n+4, output);
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
// reasignador
void persona_reassign(Persona *persona)
{  //printf("Dir reassign %p\n", persona);
  if(persona->prev && persona->next){
    // printf("prev %i current %i next %i\n", persona->prev->id, persona->id, persona->next->id);
    persona->prev->next=persona->next;
    persona->next->prev=persona->prev;
  }
  else if(persona->prev){
    // printf("prev %i current %in", persona->prev->id, persona->id);
    persona->parent->tail=persona->prev;
    persona->prev->next=NULL;
  }
  else{
    // printf("current %i next %i\n", persona->id, persona->next->id);
    persona->parent->head=persona->next;
    persona->next->prev=NULL;
    persona->parent=NULL;
    // persona->next=NULL;
  }
  }

// destructor de hijos
void persona_destroy(Persona *persona)
{ 
  // Si hay un nodo en la sig posicion, llamamos recursivamente a la funcion
  if (persona->head)
  {
    persona_destroy(persona->head);
  }
  else if(persona->next){
    persona_destroy(persona->next);
  }
  
  // Luego, liberamos la lista
  free(persona);
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