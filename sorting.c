/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"
#include <stdlib.h>

#define ERR -1
/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int InsertSort(int *array, int ip, int iu)
{
  int i, j, A, count = 0;

  if (array == NULL || ip < 0 || iu < ip) return ERR;

  for (i = ip + 1; i <= iu; i++) {
    A = array[i];
    j = i - 1;

    while (j >= ip) {
      count++; 
      if (array[j] > A) {
        array[j + 1] = array[j];
        j--;
      } else {
        break; 
      }
    }
    array[j + 1] = A;
  }

  return count;
}

/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int *array, int ip, int iu)
{
  int i, j, AUX, reset = 1, count = 0;

  if (array == NULL || ip < 0 || iu < ip) return ERR;

  while (1)
  {
    reset = 1;
    for (i = ip + 1; i <= iu; i++)
    {
      j = i - 1;
      count++; 

      if (array[i] < array[j])
      {
        AUX = array[i];
        array[i] = array[j];
        array[j] = AUX;
        reset = 0;
      }
    }

    if (reset == 1) break;
  }

  return count;
}

