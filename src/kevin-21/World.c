#include <stdio.h>
#include <stdlib.h>
#include "Persona.c"

typedef struct world {
  int n_countries;
  int* n_regions_countries;
  Persona** countries;
  int** people_count;  
} World;

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

World* create_region(World* world, int idx, int amount){ //listo
    world->n_regions_countries[idx] = amount; 
    world->people_count[idx] = calloc(amount, sizeof(int));
    for(int i=0; i<amount;i++){
      world->people_count[idx][i]=1;
    }
    world->countries[idx] = calloc(amount, sizeof(Persona));
    for(int i=0; i<amount;i++){
      world->countries[idx][i] = (Persona){.id=0, .state=2}; //Ojo que aca estamos creando una persona, no un puntero
    }
    return world;
}
// works
Persona* search(World* world, int country_idx, int region_idx, int depth, int* route){
  Persona person = world->countries[country_idx][region_idx];
  Persona* aux = &person;
  for(int idx=0; idx<depth;idx++){
    printf("cont = %i\n", idx);
    printf("Persona encontrada: %i:%i\n", search_contact(aux, route[idx])->id,search_contact(aux, route[idx])->state);
    aux = search_contact(aux, route[idx]);
    
  }
  return(aux);
}

int main(){
  World* NW = world_init(2);
  NW=create_region(NW, 0, 2);
  NW=create_region(NW, 1, 3);
  persona_append(&NW->countries[0][1],1,2);
  persona_append(&NW->countries[0][1],2,2);
  persona_append(NW->countries[0][1].head->next,3,2); //Ojo con esto se pasa de puntero a persona
  persona_print(&NW->countries[0][1],0);

  int ruta[2] = {2, 3};
  search(NW, 0, 1, 2, ruta);
  // printf("n_countries: %i\n", NW->n_countries);
  // printf("n_regions_countries: ");
  // for(int i = 0; i < NW->n_countries; i++) {
  //     printf("%d", NW->n_regions_countries[i]);
  //     printf(",");
  // }
  // printf("\npeople_count pais 0: \n");
  //   for(int j = 0; j<NW->n_regions_countries[0];j++){
  //     printf("People region %i: %i\n", j, NW->people_count[0][j]);
  //   }

  // printf("\npeople_count pais 1: \n");
  //   for(int j = 0; j<NW->n_regions_countries[1];j++){
  //     printf("People region %i: %i\n", j, NW->people_count[1][j]);
  //   }

  // printf("\nPaciente region 0: \n");
  //   for(int j = 0; j<NW->n_regions_countries[0];j++){
  //     printf("Paciente 0 region %i: %i:%i\n", j, NW->countries[0][j].id, NW->countries[0][j].state);
  //   }

  // printf("\nPaciente region 1: \n");
  //   for(int j = 0; j<NW->n_regions_countries[1];j++){
  //     printf("Paciente 0 region %i: %i:%i\n", j, NW->countries[1][j].id, NW->countries[1][j].state);
  //   }
  
  return 0;
}

