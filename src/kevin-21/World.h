#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Persona.h"

typedef struct world {
  int n_countries;
  int* n_regions_countries;
  Persona** countries;
  int** people_count;  
} World;

World* world_init(int n_countries);
void create_region(World* world, int idx, int amount);
Persona* search(World* world, int country_idx, int region_idx, int depth, int* route);
Persona add_contact(Persona *person, int new_id);
void add_contacts(World* world, int country_idx, int region_idx, int depth, int* route, int n_contacts);
void inform(World* world, int country_idx, int region_idx, FILE *output);
void recovered(World* world, int country_id, int region_id, int* route, int depth);
void positive(World* world, int country_id, int region_id, int* route, int depth, int caso);
void statistics(World* world, int country_id, int region_id, FILE *output);
void correct(World* world, int country_id, int region_id, int* route, int* ruta, int depth, int profundidad);
void destroy_world(World* world);

