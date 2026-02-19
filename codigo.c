#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparacoes;
int trocas;

void printArray(int arr[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* ---- INSERTION SORT ---- */

void insertionSort(int arr[], int n)
{
    int i, j, chave;

    for(i = 1; i < n; i++)
    {
        chave = arr[i];
        j = i - 1;

        while(j >= 0 && arr[j] > chave)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            comparacoes++;
            trocas++;
        }

        arr[j + 1] = chave;
    }
}

/* ---- QUICK SORT ---- */

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    trocas++;
}

int partition(int arr[], int baixo, int alto)
{
    int pivo, i, j;

    pivo = arr[alto];
    i = baixo - 1;

    for(j = baixo; j < alto; j++)
    {
        comparacoes++;
        if(arr[j] <= pivo)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[alto]);
    return i + 1;
}

void quickSort(int arr[], int baixo, int alto)
{
    int pi;

    if(baixo < alto)
    {
        pi = partition(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

/* ---- MERGE SORT ---- */

void merge(int arr[], int esq, int meio, int dir)
{
    int i, j, k;
    int tam1, tam2;
    int *L, *R;

    tam1 = meio - esq + 1;
    tam2 = dir - meio;

    L = (int*) malloc(tam1 * sizeof(int));
    R = (int*) malloc(tam2 * sizeof(int));

    for(i = 0; i < tam1; i++)
        L[i] = arr[esq + i];

    for(j = 0; j < tam2; j++)
        R[j] = arr[meio + 1 + j];

    i = 0;
    j = 0;
    k = esq;

    while(i < tam1 && j < tam2)
    {
        comparacoes++;
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        trocas++;
        k++;
    }

    while(i < tam1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < tam2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int esq, int dir)
{
    int meio;

    if(esq < dir)
    {
        meio = (esq + dir) / 2;
        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);
        merge(arr, esq, meio, dir);
    }
}

/* ---- MAIN ---- */

int main()
{
    int arr1[] = {64, 25, 12, 22, 11};
    int arr2[] = {64, 25, 12, 22, 11};
    int arr3[] = {64, 25, 12, 22, 11};
    int n = 5;
    clock_t inicio, fim;
    double tempo;

    printf("Array original: ");
    printArray(arr1, n);
    printf("\n");

    comparacoes = 0;
    trocas = 0;
    inicio = clock();
    insertionSort(arr1, n);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
    printf("InsertionSort:  ");
    printArray(arr1, n);
    printf("Tempo: %.4f ms  Comparacoes: %d  Trocas: %d\n\n", tempo, comparacoes, trocas);

    comparacoes = 0;
    trocas = 0;
    inicio = clock();
    quickSort(arr2, 0, n - 1);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
    printf("QuickSort:      ");
    printArray(arr2, n);
    printf("Tempo: %.4f ms  Comparacoes: %d  Trocas: %d\n\n", tempo, comparacoes, trocas);

    comparacoes = 0;
    trocas = 0;
    inicio = clock();
    mergeSort(arr3, 0, n - 1);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
    printf("MergeSort:      ");
    printArray(arr3, n);
    printf("Tempo: %.4f ms  Comparacoes: %d  Trocas: %d\n", tempo, comparacoes, trocas);

    return 0;
}
