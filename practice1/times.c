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
  int **perm;
  int i;
  clock_t start, end;

  if (!metodo || !ptime || n_perms <= 0 || N <= 0)
    return ERR;

  start = clock();
  if (start == (clock_t)-1)
    return ERR;

  perm = generate_permutations(n_perms, N);
  if (perm == NULL)
    return ERR;

  start = clock();

  for (i = 0; i < n_perms; i++)
  {
    metodo(perm[i], 0, N - 1);
  }

  end = clock();

  seconds = (double)(end - start) / CLOCKS_PER_SEC; /*Tiempo total en segundos*/
  seconds /= n_perms;                               /*Tiempo promedio por permutacion*/

  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = seconds;

  return OK;
}
/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file, int num_min, int num_max, int incr, int n_perms)
{
  int j = 0, n_times;
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

  for (int N = num_min; N <= num_max; N += incr)
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
  if (!file || !ptime || n_times <= 0)
    return ERR;

  f = fopen(file, "w");

  if (!f)
    return ERR;

  for (int i = 0; i < n_times; i++)
  {
    fprintf(f, "N:%d | N_elems:%d | Time:%.6f | Average:%.3f | Min:%d | Max:%d\n", ptime[i].N, ptime[i].n_elems, ptime[i].time, ptime[i].average_ob, ptime[i].min_ob, ptime[i].max_ob);
  }

  fclose(f);

  return OK;
}
