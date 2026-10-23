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


int MergeSort(int* array, int ip, int iu){
  int im, count = 0;

  if(ip > iu) return ERR;

  if(ip == iu) return 1; /* tabla con un elemento */
    
  im = (ip + iu) / 2;   /* Al ser im un int (sin decimales), se guarda el valor del suelo de la division por defecto */
  count += MergeSort(array, ip, im);
  count += MergeSort(array, im+1, iu);
  
  count += merge(array, ip, iu, im);
  return count;
}


int merge(int* array, int ip, int iu, int im) {
    int* array_aux = NULL;
    int i = ip, j = im + 1, k = 0;
    int count = 0;
    int n;

    n = iu - ip + 1;
    array_aux = (int *)malloc(n * sizeof(int));
    if (array_aux == NULL) return ERR;

    while (i <= im && j <= iu) {
        count++; /* Contador de comparaciones */
        if (array[i] < array[j]) {
            array_aux[k] = array[i];
            i++;
        } else {
            array_aux[k] = array[j];
            j++;
        }
        k++;
    }

    if (i > im) { /* copiar resto de tabla derecha */
        while (j <= iu) {
            array_aux[k] = array[j];
            j++;
            k++;
        }
    } else if (j > iu) { /* copiar resto de tabla izquierda */
        while (i <= im) {
            array_aux[k] = array[i];
            i++;
            k++;
        }
    }

    /* Copiar de vuelta ajustando el índice de array_aux */
    k = 0;
    for (n = ip; n <= iu; n++) {
        array[n] = array_aux[k];
        k++;
    }

    free(array_aux);
    return count;
}


/*
int partition(int* array, int ip, int iu, int* pos, pfunc_pivot pivot)
{
  int count=0;
  
  

  return count;
}
int QuickShort_min (int* array, int ip, int iu)
{
  int * pivote
  
  pivot_min(array, ip, iu, pivote);

  k=array[pivote];

  t[]
}

int partition(int* array, int ip, int iu, int* pos, pfunc_pivot pivot)
int pivot_min(int* array, int ip, int iu, int* pos)



ind Partir(tabla T, ind P, ind U)
M=Medio(T,P,U);
k=T[M];
swap(T[P],T[M]);
M=P;
para i de P+1 a U:
si T[i]<k:
M++;
swap(T[i],T[M]);
swap(T[P],T[M]);
devolver M;
*/
