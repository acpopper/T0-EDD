#include <stdio.h>
#include <stdlib.h>
#include "World.h"

World* world_init(int n_countries)
{
  World* world = malloc(sizeof(World));

  *world = (World) {
    .n_countries = n_countries,
    .n_regions_countries = calloc(n_countries, sizeof(int)),
    .countries = calloc(n_countries, sizeof(Persona*)), 
    .people_count = calloc(n_countries, sizeof(int*)) 
  };
  return world;
}

void create_region(World* world, int idx, int amount){ //listo
    world->n_regions_countries[idx] = amount; 
    world->people_count[idx] = calloc(amount, sizeof(int));
    for(int i=0; i<amount;i++){
      world->people_count[idx][i]=1;
    }
    world->countries[idx] = calloc(amount, sizeof(Persona));
    for(int i=0; i<amount;i++){
      world->countries[idx][i] = (Persona){.id=0, .state=2}; //Ojo que aca estamos creando una persona, no un puntero
    }
}
// works
Persona* search(World* world, int country_idx, int region_idx, int depth, int* route){
  Persona* person = malloc(sizeof(Persona*));
  person = &(world->countries[country_idx][region_idx]);
  // printf("person dir %p\n", person);

  for(int idx=0; idx<depth;idx++){
    // printf("cont = %i\n", idx);
    // printf("Persona encontrada: %i:%i\n", search_contact(aux, route[idx])->id,search_contact(aux, route[idx])->state);
    person = search_contact(person, route[idx]);
    
  }
  
  return(person);
}

Persona add_contact(Persona *person, int new_id){
  int state;
  if(person->state == 2){
    state = 1;
  }
  else{
    state = 0;
  }
  
  persona_append(person, new_id, state);
  return *person;
}
void add_contacts(World* world, int country_idx, int region_idx, int depth, int* route, int n_contacts){
  Persona* person = malloc(sizeof(Persona*));
  person = search(world, country_idx, region_idx, depth, route);
  // printf("persona: %i\n", person->id);
  for(int i=0; i<n_contacts; i++){
    int new_id = world->people_count[country_idx][region_idx];
    
    *person = add_contact(person, new_id);
    
    // printf("contacto de persona %i añadido. Persona %i\n", (*person).id, new_id);
    world->people_count[country_idx][region_idx]+=1;
  }
  // printf("Head %i\n", (*person).head->id);
  // printf("Tail %i\n", (*person).tail->id);
  // persona_print(person,0);
}

void inform(World* world, int country_idx, int region_idx, FILE *output){ 
  
  Persona* first = &world->countries[country_idx][region_idx];
  persona_print(first, 0, output);

}

void recovered(World* world, int country_id, int region_id, int* route, int depth){
  Persona* persona = search(world, country_id, region_id, depth, route);
  persona->state = 3;
}

void positive(World* world, int country_id, int region_id, int* route, int depth, int caso){
  Persona* persona = search(world, country_id, region_id, depth, route);
  persona->state = 2;
  Persona* current = persona->head;
  while(current){
    if(!caso){
      current->state=1;
      current=current->next;
    } else{
        if (current->state==0){
          current->state=1;
        }
        current=current->next;
    }
  }
}

void statistics(World* world, int country_id, int region_id, FILE *output){
  Persona* first = &world->countries[country_id][region_id];
  int final = true_tail(first);
  // printf("world tail %i\n", final);
  int* cuenta = calloc(4, sizeof(int));
  // printf("World cuenta: %i, %i, %i, %i\n", cuenta[0], cuenta[1], cuenta[2], cuenta[3]);
  persona_statistics(first, output, cuenta, final);
}


void correct(World* world, int country_id, int region_id, int* route, int* ruta, int depth, int profundidad){
  Persona* primera = search(world, country_id, region_id, depth, route);
  Persona* segunda = search(world, country_id, region_id, profundidad, ruta);
  // printf("P %i S %i\n", primera->id, segunda->id);
  Persona* aux = persona_init(0, 0);
  if(primera->head){
    Persona* current = primera->head;
    aux->head=current;
    while(current){
      current->parent=aux;
      aux->tail=current;
      current=current->next;
    }
    primera->head=NULL;
    primera->tail=NULL;
  } else{
    aux->head=NULL;
    aux->tail=NULL;
  }
  if(segunda->head){
    Persona* current = segunda->head;
    primera->head=current;
    while(current){
      current->parent=primera;
      primera->tail=current;
      current=current->next;
    }
  } else{
    primera->head=NULL;
    primera->tail=NULL;
  }
  segunda->head=NULL;
  segunda->tail=NULL;
  if(aux->head){
    Persona* current = aux->head;
    segunda->head=current;
    while(current){
      current->parent=segunda;
      segunda->tail=current;
      current=current->next;
    }
  } else{
    segunda->head=NULL;
    segunda->tail=NULL;
  }
  aux->head=NULL;
  aux->tail=NULL;
  if(primera->state==2){
    positive(world, country_id, region_id, route, depth, 1);
  }
  if(segunda->state==2){
    positive(world, country_id, region_id, ruta, profundidad, 1);
  }
  free(aux);
}


void destroy_world(World* world){
  for(int i=0; i<world->n_countries;i++){
    for(int j=0; j<world->n_regions_countries[i];j++){
      persona_destroy(&world->countries[i][j]);
    }
  }
  free(world);
}


// int main(){
//   World* NW = world_init(2);
//   create_region(NW, 0, 2);
//   create_region(NW, 1, 3);
//   // printf("Paises %i\n", NW->n_countries);
//   // for (int i = 0; i < NW->n_countries; i++)
//   // {
//   //   for (int j = 0; j < NW->n_regions_countries[i]; j++)
//   //   {
//   //      printf("Pais %i Region %i, %i:%i\n", i, j, NW->countries[i][j].id, NW->countries[i][j].state);
//   //   }
//   // } 
//   // printf("Finish\n");
//   // printf("id %i state %i direccion %p\n", NW->countries[0][0].id, NW->countries[0][0].state, &NW->countries[0][0]);
//   // NW->countries[0][0] = add_contact(NW->countries[0][0],1);
//   // NW->countries[0][0] = add_contact(NW->countries[0][0],2);
//   int array[1] = {0};
//   add_contacts(NW, 1, 1, 0, array, 3);
//   int ruta[1] = {2};
//   add_contacts(NW, 1, 1, 1, ruta, 2);
//   // printf("People count: %i\n", NW->people_count[0][0]); // La person_count esta bien...
//   inform(NW, 1, 1, 0);
//   // printf("head id: %i\n", NW->countries[0][0].head->id);
//   // printf("tail id: %i\n", NW->countries[0][0].tail->id);

//   // int ruta[2] = {2, 3};
//   // search(NW, 0, 1, 2, ruta);
//   // printf("n_countries: %i\n", NW->n_countries);
//   // printf("n_regions_countries: ");
//   // for(int i = 0; i < NW->n_countries; i++) {
//   //     printf("%d", NW->n_regions_countries[i]);
//   //     printf(",");
//   // }
//   // printf("\npeople_count pais 0: \n");
//   //   for(int j = 0; j<NW->n_regions_countries[0];j++){
//   //     printf("People region %i: %i\n", j, NW->people_count[0][j]);
//   //   }

//   // printf("\npeople_count pais 1: \n");
//   //   for(int j = 0; j<NW->n_regions_countries[1];j++){
//   //     printf("People region %i: %i\n", j, NW->people_count[1][j]);
//   //   }

//   // printf("\nPaciente region 0: \n");
//   //   for(int j = 0; j<NW->n_regions_countries[0];j++){
//   //     printf("Paciente 0 region %i: %i:%i\n", j, NW->countries[0][j].id, NW->countries[0][j].state);
//   //   }

//   // printf("\nPaciente region 1: \n");
//   //   for(int j = 0; j<NW->n_regions_countries[1];j++){
//   //     printf("Paciente 0 region %i: %i:%i\n", j, NW->countries[1][j].id, NW->countries[1][j].state);
//   //   }
  
//   return 0;
// }

