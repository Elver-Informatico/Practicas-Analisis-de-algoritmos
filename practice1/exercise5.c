/***********************************************************/
/* Program: exercise5                                      */
/* Authors: Pablo, Raul                                    */
/* Group: 9                                                */
/*                                                         */
/* Program that writes in separate files the average times */
/* and operation counts of Insertion and Bubble sorting    */
/*                                                         */
/* Input: Command Line                                     */
/* -num_min: lowest number of table elements               */
/* -num_max: highest number of table elements              */
/* -incr: increment                                        */
/* -numP: number of permutations to average                */
/* -outputFile: Base output file name                      */
/* Output: -1 in case of error, 0 otherwise                */
/***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sorting.h"
#include "times.h"

int main(int argc, char** argv)
{
  int i, num_min = 0, num_max = 0, incr = 0, n_perms = 0;
  char nombre[256] = "";
  char nombre_insert[300] = "";
  char nombre_bubble[300] = "";
  short ret;

  srand((unsigned int)time(NULL));

  if (argc != 11) {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
    fprintf(stderr, "\t\t -numP <int> -outputFile <string> \n");
    fprintf(stderr, "Where:\n");
    fprintf(stderr, "-num_min: lowest number of table elements\n");
    fprintf(stderr, "-num_max: highest number of table elements\n");
    fprintf(stderr, "-incr: increment\n");
    fprintf(stderr, "-numP: number of permutations to average\n");
    fprintf(stderr, "-outputFile: Base output file name\n");
    exit(-1);
  }

  printf("Practice number 1, section 5\n");
  printf("Done by: Pablo, Raul\n");
  printf("Group: 9\n");
  
  /* Parse command line arguments */
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-num_min") == 0) {
      num_min = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-num_max") == 0) {
      num_max = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-incr") == 0) {
      incr = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      n_perms = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-outputFile") == 0) {
      strcpy(nombre, argv[++i]);
    } else {
      fprintf(stderr, "Wrong parameter %s\n", argv[i]);
      exit(-1);
    }
  }

  /* Crear los nombres para los dos ficheros distintos */
  snprintf(nombre_insert, sizeof(nombre_insert), "insert_%s", nombre);
  snprintf(nombre_bubble, sizeof(nombre_bubble), "bubble_%s", nombre);

  /* 1. Medir tiempos de InsertSort */
  printf("\n[1/2] Computing times for InsertSort -> Saving to '%s'...\n", nombre_insert);
  ret = generate_sorting_times(InsertSort, nombre_insert, num_min, num_max, incr, n_perms);
  if (ret == ERR) {
    printf("Error in function generate_sorting_times for InsertSort\n");
    exit(-1);
  }

  /* 2. Medir tiempos de BubbleSort */
  printf("[2/2] Computing times for BubbleSort -> Saving to '%s'...\n", nombre_bubble);
  ret = generate_sorting_times(BubbleSort, nombre_bubble, num_min, num_max, incr, n_perms);
  if (ret == ERR) {
    printf("Error in function generate_sorting_times for BubbleSort\n");
    exit(-1);
  }

  printf("\nExecution completed successfully.\n");
  return 0;
}