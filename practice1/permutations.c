/**
*
* Descripcion: Implementation of function that generate permutations
*
* File: permutations.c
* Autores: Pablo y Raul
* Version: 1.1
* Fecha: 30-09-2026
*
*/


#include "permutations.h"
#include <stdlib.h>
/***************************************************/
/* Function: random_num Date: 23-9 */
/* Authors: Pablo */
/* */
/* Rutine that generates a random number */
/* between two given numbers */
/* */
/* Input: */
/* int inf: lower limit */
/* int sup: upper limit */
/* Output: */
/* int: random number */
/***************************************************/
int random_num(int inf, int sup)
{
  int x;

  if(inf < 0 || sup > RAND_MAX || inf > sup){
    return ERR;
  }

  x = rand() % (sup - inf + 1) + inf;
  return x;
}

/***************************************************/
/* Function: generate_perm Date: */
/* Authors: Raul */
/* */
/* Rutine that generates a random permutation */
/* */
/* Input: */
/* int n: number of elements in the permutation */
/* Output: */
/* int *: pointer to integer array */
/* that contains the permitation */
/* or NULL in case of error */
/***************************************************/
int* generate_perm(int n)
{
  int i, j, num;
  int *array=NULL;

  if(n <= 0){
    return NULL;
  }

  /*reservamos memoria para el array*/

  array = (int *)malloc(n * sizeof(int));

  if(array == NULL) return NULL;

  /*rellenamos el array con los numeros del 1 al N*/
  printf("check 1: \n");
  for (i = 0; i < n; i++) {
    printf("%d\n", i);
    array[i]= 1+i;

  }
  printf("check 2: \n");
  for (i = 0; i < n; i++) {
    /*generamos numeros aleatorios*/
    j = random_num(i, n - 1);
    printf("%d\n", j);

    if (j == ERR) {
      free(array); 
      return NULL;
    }

    /*reordenamos el array*/
    num = array[i];
    array[i] = array[j];
    array[j] = num;
  }

  printf("check 3: \n");
  for (i = 0; i < n; i++) {
    printf("%d\n", array[i]);
  }

  return array;
}

/***************************************************/
/* Function: generate_permutations Date: */
/* Authors: Pablo*/
/* */
/* Function that generates n_perms random */
/* permutations with N elements */
/* */
/* Input: */
/* int n_perms: Number of permutations */
/* int N: Number of elements in each permutation */
/* Output: */
/* int**: Array of pointers to integer that point */
/* to each of the permutations */
/* NULL en case of error */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int **matrix = NULL;
  int i;

  if (n_perms <= 0 || N <= 0){
    return NULL;
  }

  /*reservamos memoria para el array*/

  matrix = (int **)malloc(n_perms * sizeof(int*));

  if(matrix == NULL) return NULL; 

  for(i=0; i < n_perms; i++){
    matrix[i] = generate_perm(N);
    
    if (matrix[i] == NULL){ /* En caso de error, liberar memoria y return NULL*/
      for(i -= 1; i >= 0; i--){
        free(matrix[i]);
      }
      free(matrix);
      return NULL;
    }
  }

  return matrix;
}