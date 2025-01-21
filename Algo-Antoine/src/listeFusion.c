#include "listesFusion.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Fonction pour merger deux liste triées
 * @param array1 liste triée numéro 1
 * @param size1 taille de la liste triée numéro 1
 * @param array2 liste triée numéro 2
 * @param size2 taille de la liste numéro 2
 * @param mergedArray liste triée qui va accueillir la fusion
 * @param mergedSize pointeur sur un entier qui va contenir la taille de la nouvelle liste
 */
void mergeSortedArrays(const int* array1, int size1, const int* array2, int size2, int** mergedArray,
int* mergedSize) {
    *mergedArray = (int*)malloc((size1 + size2) * sizeof(int));
    if (!mergedArray) {
        printf("Pb d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2) {
        (*mergedArray)[k++] = (array1[i] < array2[j]) ? array1[i++] : array2[j++];
    }
    while (i < size1) {
        (*mergedArray)[k++] = array1[i++];
    }

    while (j < size2) {
        (*mergedArray)[k++] = array2[j++];
    }

    *mergedSize = k;
}

/**
 * Test numéro 1 avec une petite liste
 */
void test1(void) {
    const int array1[] = {1, 3, 5, 7, 10, 12, 21};
    const int array2[] = {2, 4, 6, 8, 12, 14};
    int size1 = sizeof(array1) / sizeof(array1[0]);
    int size2 = sizeof(array2) / sizeof(array2[0]);

    int merged_size;
    int *mergedArray;
    mergeSortedArrays(array1, size1, array2, size2, &mergedArray, &merged_size);

    printf("Merged array: ");
    for (int i = 0; i < merged_size; i++) {
        printf("%d ", mergedArray[i]);
    }
    printf("\n");

    free(mergedArray);
}
