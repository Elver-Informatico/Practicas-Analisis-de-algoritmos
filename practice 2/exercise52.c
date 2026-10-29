
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
    
    /* Nombres para los 3 archivos de resultados*/
    char nombre_qs_min[300] = "";
    char nombre_qs_mean[300] = "";
    char nombre_qs_median[300] = "";
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

    /* Crear los nombres de los 3 ficheros de salida */
    snprintf(nombre_qs_min, sizeof(nombre_qs_min), "qs_min_%s", nombre);
    snprintf(nombre_qs_mean, sizeof(nombre_qs_mean), "qs_mean_%s", nombre);
    snprintf(nombre_qs_median, sizeof(nombre_qs_median), "qs_median_%s", nombre);

    /* 1. Medir tiempos de QuickSort_min */
    printf("\nComputing times for QuickSort_min -> Saving to '%s'...\n", nombre_qs_min);
    ret = generate_sorting_times(QuickSort_min, nombre_qs_min, num_min, num_max, incr, n_perms);
    if (ret == ERR) {
        printf("Error in function generate_sorting_times for QuickSort_min\n");
        exit(-1);
    }

    /* 2. Medir tiempos de QuickSort_mean */
    printf("\nComputing times for QuickSort_mean -> Saving to '%s'...\n", nombre_qs_mean);
    ret = generate_sorting_times(QuickSort_mean, nombre_qs_mean, num_min, num_max, incr, n_perms);
    if (ret == ERR) {
        printf("Error in function generate_sorting_times for QuickSort_mean\n");
        exit(-1);
    }

    /* 3. Medir tiempos de QuickSort_median */
    printf("\nComputing times for QuickSort_median -> Saving to '%s'...\n", nombre_qs_median);
    ret = generate_sorting_times(QuickSort_median, nombre_qs_median, num_min, num_max, incr, n_perms);
    if (ret == ERR) {
        printf("Error in function generate_sorting_times for QuickSort_median\n");
        exit(-1);
    }

    printf("\nExecution completed successfully.\n");
    return 0;
}