#pragma once
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

Persona* persona_init(int id, int state);
void persona_print(Persona* persona,int n, FILE *output);
int true_tail(Persona* persona);
void persona_statistics(Persona* persona, FILE *output, int* cuenta, int final);
void persona_append(Persona* persona, int id, int state);
Persona* search_contact(Persona* persona, int id);
void persona_reassign(Persona *persona);
void persona_destroy(Persona *persona);