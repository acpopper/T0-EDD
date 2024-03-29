#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "World.h"


/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    return false;
  }

  return true;
}

int main(int argc, char **argv)
{
  /* Si los parámetros del programa son inválidos */
  if (!check_arguments(argc, argv))
  {
    /* Salimos del programa indicando que no terminó correctamente */
    return 1;
  }

  /* Abrimos el archivo de input */
  FILE *input_file = fopen(argv[1], "r");
  /* Abrimos el archivo de output */
  FILE *output_file = fopen(argv[2], "w");

  char command[32];
  
  /* Leemos la cantidad de países */
  int n_countries;
  fscanf(input_file, "%d", &n_countries);

  /* [Por implementar] Generamos nuestro mundo */
  World* new_world =world_init(n_countries);

  /* Leemos la cantidad de regiones de cada país */
  int n_regions;
  for (int cty = 0; cty < n_countries; cty++)
  {
    fscanf(input_file, "%d", &n_regions);
    
    /* [Por implementar] Poblamos el país con regiones */
    create_region(new_world, cty, n_regions);
  }

  /* Número de eventos/líneas */
  int n_lines;
  fscanf(input_file, "%d", &n_lines);

  /* Declaramos variables para guardar: 
    - Id de país.
    - Id de región. 
    - Profundidad.
    - Id de contacto para las rutas
    - Número de contactos.
  */
  int country_id;
  int region_id;
  int depth;
  int contact_id;
  int n_contacts;
  int profundidad;

  // while (n_lines)
  for(int i=0; i<n_lines;i++)
  {
    /* Disminuimos en 1 el número de líneas por leer */
    // n_lines--;
    // printf("LINEA %i\n", i);
    /* Leemos la instrucción */
    fscanf(input_file, "%s", command);

    /* Obtenemos país, región, y profundidad */
    fscanf(input_file, "%d", &country_id);
    fscanf(input_file, "%d", &region_id);
    
    // printf("Command: %s\n", command);

    /* POSITIVE */
    if (string_equals(command, "ADD_CONTACTS"))
    {
      fscanf(input_file, "%d", &depth);
      int route[depth];
      route[0]=0;
      // printf("ADD_CONTACTS %d %d %d ", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      for (int r = 0; r < depth; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route[r] = contact_id;
      }
      
      /* Obtenemos el numero de contactos */
      fscanf(input_file, "%d", &n_contacts);
      // printf("%d\n", n_contacts);
      
      add_contacts(new_world, country_id, region_id, depth, route, n_contacts);
    } 
    else if (string_equals(command, "POSITIVE"))
    {

      fscanf(input_file, "%d", &depth);
      // printf("POSITIVE %d %d %d ", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      int route[depth];
      route[0]=0;
      for (int r = 0; r < depth; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route[r] = contact_id;
      }
      // printf("\n");
      positive(new_world, country_id, region_id, route, depth, 0);
    } 
    else if (string_equals(command, "NEGATIVE"))
    {
      
      fscanf(input_file, "%d", &depth);
      // printf("NEGATIVE %d %d %d ", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      int route[depth];
      route[0]=0;
      for (int r = 0; r < depth; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route[r] = contact_id;
      }
      // printf("\n");
      Persona* persona = search(new_world, country_id, region_id, depth, route);
      // printf("Dir neg %p\n", persona);
      persona_reassign(persona); //si se modifica el arbol, problema esta en el print
      
      
    } 
    else if (string_equals(command, "RECOVERED"))
    {
      
      fscanf(input_file, "%d", &depth);
      // printf("RECOVERED %d %d %d ", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      int route[depth];
      route[0]=0;
      for (int r = 0; r < depth; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route[r]=contact_id;
      }
      // printf("\n");

      /* [Por implementar] */
      recovered(new_world, country_id, region_id, route, depth);

    } 
    else if (string_equals(command, "CORRECT"))
    {
      fscanf(input_file, "%d", &depth);
      // printf("RECOVERED %d %d %d ", country_id, region_id, depth);
      /* Obtenemos la primera ruta desde el archivo*/
      int route[depth];
      route[0]=0;
      for (int r = 0; r < depth; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        route[r]=contact_id;
      }
      /* Obtenemos la segunda ruta desde el archivo*/
      fscanf(input_file, "%d", &profundidad);
      // printf("%d ", depth);
      int ruta[profundidad];
      ruta[0]=0;
      for (int r = 0; r < profundidad; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        // printf("%d ", contact_id);
        ruta[r]=contact_id;
      }
      // printf("\n");

      /* [Por implementar] */
      
      correct(new_world, country_id, region_id, route, ruta, depth, profundidad);
    
    } 
    else if (string_equals(command, "INFORM"))
    {
      
      fprintf(output_file, "INFORM %d %d\n", country_id, region_id);
      /* [Por implementar] */
      inform(new_world, country_id, region_id, output_file);
    } 

    else if (string_equals(command, "STATISTICS"))
    {
      fprintf(output_file, "STATISTICS %d %d\n", country_id, region_id);
      /* [Por implementar] */
      statistics(new_world, country_id, region_id, output_file);

    }

  }

  /*  [Por implementar] Liberamos nuestra estructura */
  // destroy_world(new_world);

  fclose(input_file);
  fclose(output_file);
  return 0;
}