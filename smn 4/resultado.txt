/*
 * ============================================================
 *  Análise Comparativa: ShellSort vs HeapSort
 *  Avaliação Individual — Estruturas de Dados
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================
   FUNÇÕES AUXILIARES
   ============================================================ */

/* Troca os valores de dois ponteiros */
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Imprime um array com um rótulo */
void printArray(const char *label, int arr[], int n) {
    printf("%s [", label);
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

/* Copia o array src para dst */
void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

/* Retorna 1 se o array estiver ordenado, 0 caso contrário */
int isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1]) return 0;
    return 1;
}

/* ============================================================
   SHELLSORT
   Complexidade: depende da sequência de gaps.
   Sequência de Ciura (2001) usada: {701,301,132,57,23,10,4,1}
   ============================================================ */
void shellSort(int arr[], int n) {
    int gaps[]  = {701, 301, 132, 57, 23, 10, 4, 1};
    int numGaps = 8;

    for (int g = 0; g < numGaps; g++) {
        int gap = gaps[g];
        if (gap >= n) continue;

        /* Insertion sort com o gap atual */
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j    = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

/* ============================================================
   HEAPSORT
   Complexidade: O(n log n) garantido em todos os casos.
   ============================================================ */

/* Corrige a propriedade de max-heap a partir do índice i */
void siftDown(int arr[], int i, int heapSize) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left  < heapSize && arr[left]  > arr[largest]) largest = left;
    if (right < heapSize && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        siftDown(arr, largest, heapSize);
    }
}

/* Constrói um max-heap a partir de um vetor arbitrário */
void buildMaxHeap(int arr[], int n) {
    /* Começa do último nó interno e sobe até a raiz */
    for (int i = n / 2 - 1; i >= 0; i--)
        siftDown(arr, i, n);
}

void heapSort(int arr[], int n) {
    buildMaxHeap(arr, n);

    for (int end = n - 1; end > 0; end--) {
        /* Move o maior elemento (raiz) para a posição final */
        swap(&arr[0], &arr[end]);
        /* Restaura o heap para os elementos restantes */
        siftDown(arr, 0, end);
    }
}

/* ============================================================
   QUESTÃO 2 — Construção do Max-Heap
   ============================================================ */
void demonstrarQuestao2() {
    printf("============================================================\n");
    printf("  QUESTAO 2 — Construcao do Max-Heap\n");
    printf("============================================================\n");

    int v[] = {30, 12, 45, 6, 18, 3};
    int n   = 6;

    printArray("Vetor original:  ", v, n);

    buildMaxHeap(v, n);
    printArray("a) Max-Heap:     ", v, n);
    printf("   (esperado)    [45, 18, 30, 6, 12, 3]\n\n");

    /* Primeira extração da raiz */
    swap(&v[0], &v[n - 1]);
    siftDown(v, 0, n - 1);

    printf("b) Apos 1a extracao:\n   Heap ativo    [");
    for (int i = 0; i < n - 1; i++) {
        printf("%d", v[i]);
        if (i < n - 2) printf(", ");
    }
    printf("] | Ordenado: [%d]\n", v[n - 1]);
    printf("   (esperado)    [30, 18, 3, 6, 12] | [45]\n\n");
}

/* ============================================================
   TESTE DE CORRETUDE
   ============================================================ */
void testCorrectness() {
    printf("============================================================\n");
    printf("  TESTE DE CORRETUDE\n");
    printf("============================================================\n");

    int tests[][8] = {
        {5, 3, 8, 1, 9, 2, 7, 4},  /* aleatório     */
        {1, 2, 3, 4, 5, 6, 7, 8},  /* já ordenado   */
        {8, 7, 6, 5, 4, 3, 2, 1},  /* ordem inversa */
        {1, 1, 1, 1, 1, 1, 1, 1},  /* todos iguais  */
    };
    const char *names[] = {
        "Aleatorio      ",
        "Ja ordenado    ",
        "Ordem inversa  ",
        "Todos iguais   "
    };
    int numTests = 4;

    for (int t = 0; t < numTests; t++) {
        int a[8], b[8];
        copyArray(tests[t], a, 8);
        copyArray(tests[t], b, 8);

        shellSort(a, 8);
        heapSort(b, 8);

        printf("%-20s | ShellSort: %s | HeapSort: %s\n",
               names[t],
               isSorted(a, 8) ? "OK v" : "ERRO x",
               isSorted(b, 8) ? "OK v" : "ERRO x");
    }
    printf("\n");
}

/* ============================================================
   BENCHMARK — Comparação de desempenho
   ============================================================ */
void benchmark() {
    printf("============================================================\n");
    printf("  BENCHMARK — Comparacao de desempenho\n");
    printf("============================================================\n");

    int sizes[]   = {1000, 10000, 100000};
    int numSizes  = 3;

    for (int s = 0; s < numSizes; s++) {
        int n        = sizes[s];
        int *original = (int *)malloc(n * sizeof(int));
        int *arr      = (int *)malloc(n * sizeof(int));

        /* Gera vetor aleatório com semente fixa para reprodutibilidade */
        srand(42);
        for (int i = 0; i < n; i++) original[i] = rand() % (n * 10);

        printf("n = %7d | ", n);

        /* ShellSort */
        copyArray(original, arr, n);
        clock_t start = clock();
        shellSort(arr, n);
        clock_t end   = clock();
        double timeShell = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
        printf("ShellSort: %8.3f ms | ", timeShell);

        /* HeapSort */
        copyArray(original, arr, n);
        start = clock();
        heapSort(arr, n);
        end   = clock();
        double timeHeap = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
        printf("HeapSort: %8.3f ms\n", timeHeap);

        free(original);
        free(arr);
    }

    printf("\n");
    printf("Obs: ShellSort costuma ser mais rapido para entradas aleatorias,\n");
    printf("     mas HeapSort garante O(n log n) em TODOS os casos.\n\n");
}

/* ============================================================
   FUNÇÃO PRINCIPAL
   ============================================================ */
int main(void) {
    printf("============================================================\n");
    printf("  Analise Comparativa: ShellSort vs HeapSort\n");
    printf("  Avaliacao Individual — Estruturas de Dados\n");
    printf("============================================================\n\n");

    demonstrarQuestao2();
    testCorrectness();
    benchmark();

    printf("============================================================\n");
    printf("  RESUMO DAS RESPOSTAS TEORICAS\n");
    printf("============================================================\n");
    printf("Q1: HeapSort = O(n log n) garantido (heap deterministica).\n");
    printf("    ShellSort = complexidade varia conforme sequencia de gaps.\n\n");
    printf("Q2: a) Max-Heap: [45, 18, 30, 6, 12, 3]\n");
    printf("    b) Apos 1a extracao: heap=[30,18,3,6,12], ordenado=[45]\n\n");
    printf("Q3: Gabarito: A) Apenas II e IV\n");
    printf("    II=VERDADEIRO (arvore binaria completa), IV=VERDADEIRO\n");
    printf("    I=FALSO (ShellSort nao e estavel)\n");
    printf("    III=FALSO (gaps sao do ShellSort, nao do HeapSort)\n\n");
    printf("Q4: HeapSort e mais indicado para milhoes de registros:\n");
    printf("    O(n log n) garantido + O(1) memoria extra (in-place).\n\n");
    printf("Q5: Heap como fila de prioridade (min-heap) no Dijkstra:\n");
    printf("    extrai vertice de menor distancia em O(log V),\n");
    printf("    reduzindo complexidade total para O((V+E) log V).\n");
    printf("============================================================\n");

    return 0;
}