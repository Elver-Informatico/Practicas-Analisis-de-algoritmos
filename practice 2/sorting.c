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


int partition(int* array, int ip, int iu, int* pos, pfunc_pivot pivot)
{
int M,res,i, menor=ip,val_pivote, aux,count=0;

  res=pivot(array, ip, iu, &M);

  val_pivote= array[M];

  if(res==-1) return ERR;


  else

  /*ponemos el pivote si o si en el primer lugar*/

aux = array[ip];
array[ip]= array[M];
array[M]= aux;

/*comparamos y luego metemos el pivote en el siguiente del ultimo elemento que diga menor*/
    for(i=ip+1;i<=iu;i++)

    
    {
      count++;
      if(array[i]<val_pivote)
        { 
        menor++;
          
        aux= array[menor];
        array[menor]=array[i];
        array[i]= aux;
        }
    }

    aux=array[menor];
    array[menor] = array[ip];
    array[ip] =aux;

    *pos=menor;

return count+res;


}



int pivot_min(int* array, int ip, int iu, int* pos)
{
  if(!array||ip>iu) return -1;
  *pos = ip;


return 0;
}

int QuickSort_min (int* array, int ip, int iu)
{
  int M ,a,b,c;

/*caso base en el que solo hay ya un elemento o ninguno*/
    if(ip>=iu) return 0;

/*se hace la particion con el array indicado*/
a= partition(array, ip, iu,&M, pivot_min);

    if(a == -1) return ERR;


/*recursion y no hacen falta ifs ya que estan controlados los errores*/


b=QuickSort_min (array,ip, M-1);
c=QuickSort_min (array,M+1, iu);

return  a+b+c;

  
}



/*es exactamente la misma funicon lo que cambia es el puntero a funcion que se le manda a partition*/
int QuickSort_mean(int* array, int ip, int iu)
{
  int M ,a,b,c;

    if(ip>=iu) return 0;


a= partition(array, ip, iu,&M, pivot_mean);

    if(a == -1) return ERR;




b=QuickSort_mean (array,ip, M-1);
c=QuickSort_mean (array,M+1, iu);

return  a+b+c;

  
}

int pivot_mean(int* array, int ip, int iu, int* pos)
{
    if(!array||ip>iu) return -1;
    *pos = ip+(iu-ip)/2;


return 0;
}

int pivot_median(int* array, int ip, int iu, int* pos)
{
  int P,M,U;
    if(!array||ip>iu) return -1;

    
    /*calculamos la mediana de los extremos y el medio*/

    P=array[ip]; 
    M=array[ip+(iu-ip)/2];
    U=array[iu];


if ((P <= M && M <= U) || (U <= M && M <= P)) {
        *pos = ip+(iu-ip)/2;
        return 2; 
    }
    
    else if ((M <= P && P <= U) || (U <= P && P <= M)) {
        *pos = ip;
        return 4; 
    }

    else {
        *pos = iu;
        return 4; 
    }
  }


int QuickSort_median(int* array, int ip, int iu)
{
  int M ,a,b,c;


    if(ip>=iu) return 0;

a= partition(array, ip, iu,&M, pivot_median);

    if(a == -1) return ERR;




b=QuickSort_median(array,ip, M-1);
c=QuickSort_median(array,M+1, iu);

return  a+b+c;

  
}