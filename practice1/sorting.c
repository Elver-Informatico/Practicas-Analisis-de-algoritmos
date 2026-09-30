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

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int InsertSort(int *array, int ip, int iu)
{
  int i, min, comparacion = 0, aux, tam;
  tam = iu - ip + 1;

  if (array == NULL || ip <= 0 || ip > iu)
    return ERR;

  /*escribir el razonamiento del 0 o el 1 en la memoria*/
  if (ip == iu)
    return 1;

  /*cogemos el menor y lo ponemos al primcipio*/

  min = array[ip];
  for (i = ip; i <= iu; i++)
  {

    if (array[i] < min)
    {
      min = array[i];
    }

    comparacion++;
  }



  return comparacion;
}

/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int *array, int ip, int iu)
{
  /* Your code */
}
