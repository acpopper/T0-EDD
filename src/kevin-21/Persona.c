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
  fprintf(output, "%*s%i:%i\n", n, "", persona->id, persona->state);
  Persona* current = persona->head;
  
  while (current){
    persona_print(current, n+4, output);
    current = current->next;
  }
  
}

int true_tail(Persona* persona){
  Persona* current = persona;
  if(current->tail){
    // printf("current: %i\n", current->id);
    // printf("current tail: %i\n", current->tail->id);
    current=current->tail;
    true_tail(current);
  }
  return current->id;
}

void persona_statistics(Persona* persona, FILE *output, int* cuenta, int final)
{ 
  if(persona->state==0){
    cuenta[0]+=1;
    // printf("ceros %i\n", cuenta[0]);
  } else if(persona->state==1){
    cuenta[1]+=1;
    // printf("unos %i\n", cuenta[1]);
  } else if(persona->state==2){
    cuenta[2]+=1;
    // printf("doses %i\n", cuenta[2]);
  } else{
    cuenta[3]+=1;
    // printf("treses %i\n", cuenta[3]);
  }
  if(persona->head){
    Persona* current = persona->head;
  
  while (current)
 { // printf("current id %i state %i\n", current->id, current->state);
    persona_statistics(current, output, cuenta, final);
    current=current->next;
  }
  }
  
  if(persona->id==final){
    // printf("persona %i final %i\n", persona->id, final);
    fprintf(output, "0:%i\n", cuenta[0]);
    fprintf(output, "1:%i\n", cuenta[1]);
    fprintf(output, "2:%i\n", cuenta[2]);
    fprintf(output, "3:%i\n", cuenta[3]);
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
    persona->parent=NULL;
  }
  else if(persona->prev){
    // printf("prev %i current %in", persona->prev->id, persona->id);
    persona->parent->tail=persona->prev;
    persona->prev->next=NULL;
    persona->parent=NULL;
  }
  else if(persona->next){
    // printf("current %i next %i\n", persona->id, persona->next->id);
    persona->parent->head=persona->next;
    persona->next->prev=NULL;
    persona->parent=NULL;
    // persona->next=NULL;
  } else{
    persona->parent->head=NULL;
    persona->parent->tail=NULL;
    persona->parent=NULL;
  }
  }

// destructor de self e hijos
void persona_destroy(Persona *persona)
{ 
  if(persona->head){
    persona_destroy(persona->head);
  }
  if(persona->next){
    persona_destroy(persona->next);
  }
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