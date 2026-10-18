/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "times.h"
#include "sorting.h"
#include "permutations.h"

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime)
{
  double seconds;
  int **perm = NULL;
  int i, ob;
  long total_ob = 0;
  int min_ob = 0, max_ob = 0;
  clock_t start, end;

  if (!metodo || !ptime || n_perms <= 0 || N <= 0)
    return ERR;


  perm = generate_permutations(n_perms, N);
  if (perm == NULL)
    return ERR;


  start = clock();
  if (start == (clock_t)-1) {
    free_permutations(perm, n_perms);
    return ERR;
  }


  for (i = 0; i < n_perms; i++)
  {
    ob = metodo(perm[i], 0, N - 1);
    if (ob == ERR) {
      free_permutations(perm, n_perms);
      return ERR;
    }

    total_ob += ob;

    if (i == 0 || ob < min_ob) min_ob = ob;
    if (i == 0 || ob > max_ob) max_ob = ob;
  }

  end = clock();


  free_permutations(perm, n_perms);


  seconds = (end - start) / CLOCKS_PER_SEC;
  seconds /= n_perms;

  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = seconds;
  ptime->average_ob = total_ob / n_perms;
  ptime->min_ob = min_ob;
  ptime->max_ob = max_ob;

  return OK;
}
/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file, int num_min, int num_max, int incr, int n_perms)
{
  int j = 0, n_times, N;
  PTIME_AA ptime;

  if (!method || !file || num_min < 1 || num_max < num_min || incr <= 0 || n_perms <= 0)
  {
    return ERR;
  }

  n_times = ((num_max - num_min) / incr) + 1;

  ptime = calloc(n_times, sizeof(TIME_AA));
  if (!ptime)
  {
    return ERR;
  }

  for ( N = num_min; N <= num_max; N += incr)
  {
    if (average_sorting_time(method, n_perms, N, &ptime[j]) == ERR)
    {
      free(ptime);
      return ERR;
    }
    j++;
  }

  if (save_time_table(file, ptime, n_times) == ERR)
  {
    free(ptime);
    return ERR;
  }

  free(ptime);

  return OK;
}
/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char *file, PTIME_AA ptime, int n_times)
{
  FILE *f = NULL;
  int i;
  if (!file || !ptime || n_times <= 0)
    return ERR;

  f = fopen(file, "w");

  if (!f)
    return ERR;

  for ( i = 0; i < n_times; i++)
  {
    fprintf(f, "N:%d | N_elems:%d | Time:%.6f | Average:%.3f | Min:%d | Max:%d\n",
        ptime[i].N, ptime[i].n_elems, ptime[i].time, ptime[i].average_ob, ptime[i].min_ob, ptime[i].max_ob);
  }

  fclose(f);

  return OK;
}


void free_permutations(int **perm, int n_perms)
{
  int i;
  if (perm == NULL) return;

  for (i = 0; i < n_perms; i++) {
    if (perm[i] != NULL) {
      free(perm[i]);
    }
  }
  free(perm);
}