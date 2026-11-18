#include <stdio.h>
#include <stdlib.h>

#include "search.h"

PDICT init_dictionary(int size, char order){
    PDICT d = NULL;

    if(size <= 0 || (order != SORTED && order != NOT_SORTED)){
        return NULL;
    }

    d = (PDICT)calloc(1, sizeof(DICT));
    if(!d){
        return NULL;
    }

    d->table = (int *)calloc(size, sizeof(int));
    if(!d->table){
        free(d);
        return NULL;
    }

    d->size = size;
    d->order = order;

    return d;
}

void free_dictionary(PDICT pdict){
    int i;
    
    if(pdict){
        for(i=0; i < pdict->size; i++){
            if(pdict->table[i]){
                free(pdict->table);
            }
        }
        free(pdict);
    }

    return;
}

int insert_dictionary(PDICT pdict, int key){
    int A = key, j, U = pdict->n_data - 1, P = pdict->table[0];
    int OB = 0;

    if(pdict->order == SORTED){
        pdict->table[pdict->n_data] = key;
        pdict->n_data++;
        return 1;
    }else{
        A = pdict->table[U];
        j = U - 1;
        while(j >= P && pdict->table[j] > A){
            OB++;
            pdict->table[j + 1] = pdict->table[j];
            j--;
            pdict->table[j + 1] = A;
        }

        pdict->n_data++;
        return OB;
    }
}

int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys){
    int i, OB = 0;

    for(i=0; i < n_keys; i++){
        OB = insert_dictionary(pdict, keys[i]);
    }

    return OB;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method){
    int OB = 0;

    OB = method(pdict->table, 0, pdict->n_data - 1, key, ppos);

    if(OB == ERR){
        return ERR;
    }

    return OB;
}

int bin_search(int *table, int F, int L, int key, int *ppos){
    
    
    /*si T==NULL : return NULL;
    si info(T)==k : return T;
    si k<info(T) :
    return Buscar(k,izq(T));
    si k>info(T) :
    return Buscar(k,der(T));*/
}

int lin_search(int *table, int F, int L, int key, int *ppos){
    int i, OB = 0;

    if(F > L || !table || !ppos){
        return ERR;
    }

    if(F = L) {
        ppos = F;
        return 1;
    }

    for(i=F; i < L; i++){
        OB++;
        if(table[i] == key){
            ppos = i;
            return OB;
        }
        ppos = NOT_FOUND;
        return OB;
    }
    return ERR;
}

int lin_auto_search(int *table, int F, int L, int key, int *ppos){
    int i, j, OB = 0;
    int *temp = NULL;

    if(F > L || !table || !ppos){
        return ERR;
    }

    if(F = L) {
        ppos = F;
        return 1;
    }
    
    for(i=F; i < L; i++){
        if(table[i] == key){
            if(i > F){
                temp = table[i];
                for(j=i; j > F+1; j--){
                    OB++;
                    table[j] = table[j-1];
                }
                table[F] = temp;
            }
            ppos = F;
        }
    }

    ppos = NOT_FOUND;
}