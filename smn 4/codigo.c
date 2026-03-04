/*
 * ============================================================
 *  Análise Comparativa: ShellSort vs HeapSort
 *  Avaliação Individual - Estruturas de Dados
 * ============================================================
 *
 * QUESTÃO 1 - Complexidade
 * ---------------------------------------------------------------
 * HeapSort tem complexidade O(n log n) garantida em TODOS os casos
 * (melhor, médio e pior) porque:
 *   1. A construção do heap (heapify) percorre n/2 nós internos,
 *      cada ajuste desce no máximo log n níveis → O(n log n).
 *   2. A fase de extração remove n elementos; cada remoção chama
 *      heapify (sift-down) que custa O(log n) → O(n log n).
 *   3. O comportamento NÃO depende da distribuição inicial dos dados.
 *
 * ShellSort NÃO tem complexidade previsível porque:
 *   - Depende da sequência de gaps (incrementos) escolhida.
 *   - Com gaps de Shell (N/2, N/4, ..., 1): O(n²) no pior caso.
 *   - Com gaps de Hibbard: O(n^1.5) no pior caso.
 *   - Com gaps de Ciura: ~O(n^1.25) na prática, mas sem prova formal.
 *   - Não existe sequência de gaps com O(n log n) provado no pior caso.
 *
 * ---------------------------------------------------------------
 * QUESTÃO 2 - Construção do Max-Heap para [30, 12, 45, 6, 18, 3]
 * ---------------------------------------------------------------
 * Vetor original: [30, 12, 45, 6, 18, 3]
 * Índices (0-based): 0=30, 1=12, 2=45, 3=6, 4=18, 5=3
 *
 * Árvore inicial:
 *           30
 *          /  \
 *        12    45
 *       / \   /
 *      6  18 3
 *
 * heapify a partir do último nó interno (índice 2, valor 45):
 *   filhos: índice 5 (3) e sem índice 6 → 45 > 3, sem troca.
 *
 * heapify índice 1 (valor 12):
 *   filhos: índice 3 (6) e índice 4 (18) → maior filho = 18
 *   12 < 18 → troca: [30, 18, 45, 6, 12, 3]
 *
 * heapify índice 0 (valor 30):
 *   filhos: índice 1 (18) e índice 2 (45) → maior filho = 45
 *   30 < 45 → troca: [45, 18, 30, 6, 12, 3]
 *   Descer 30 para índice 2:
 *     filhos: índice 5 (3) → 30 > 3, sem troca.
 *
 * MAX-HEAP FINAL: [45, 18, 30, 6, 12, 3]
 *
 *           45
 *          /  \
 *        18    30
 *       / \   /
 *      6  12 3
 *
 * a) Max-Heap: [45, 18, 30, 6, 12, 3]
 *
 * b) Após a 1ª extração da raiz (45):
 *    - Troca raiz (45) com último elemento (3): [3, 18, 30, 6, 12, 45]
 *    - Reduz heap para tamanho 5, o 45 está na posição correta.
 *    - Sift-down na raiz (3), heap de tamanho 5:
 *      filhos: 18 e 30 → maior = 30 → troca: [30, 18, 3, 6, 12]
 *      Descer 3 (índice 2): filhos = índice 5 (fora), sem troca.
 *    Vetor após 1ª extração: [30, 18, 3, 6, 12 | 45]
 *    (45 está ordenado ao final; heap ativo = [30, 18, 3, 6, 12])
 *
 * ---------------------------------------------------------------
 * QUESTÃO 3 - Análise das afirmativas
 * ---------------------------------------------------------------
 * I  – ShellSort é estável. → FALSO
 *      ShellSort realiza trocas com gaps grandes, podendo reordenar
 *      elementos iguais. Não é estável.
 *
 * II – HeapSort utiliza estrutura baseada em árvore binária completa.
 *      → VERDADEIRO
 *      O heap é representado como array mas corresponde a uma árvore
 *      binária completa (todos os níveis preenchidos exceto o último,
 *      que é preenchido da esquerda para direita).
 *
 * III– HeapSort depende da sequência de gaps. → FALSO
 *      Quem depende de gaps é o ShellSort. HeapSort usa a propriedade
 *      heap e não tem conceito de gaps.
 *
 * IV – ShellSort é uma melhoria do Insertion Sort. → VERDADEIRO
 *      ShellSort foi proposto por Donald Shell (1959) como extensão
 *      do Insertion Sort: ao usar gaps maiores no início, move
 *      elementos distantes rapidamente, reduzindo o custo do
 *      Insertion Sort final (gap=1).
 *
 * Gabarito: A) Apenas II e IV ✓
 *
 * ---------------------------------------------------------------
 * QUESTÃO 4 - Sistema com milhões de registros
 * ---------------------------------------------------------------
 * Algoritmo indicado: HeapSort
 *
 * Justificativa:
 *   - Complexidade garantida O(n log n) em TODOS os casos.
 *     Em produção, não se pode aceitar degradação para O(n²).
 *   - Uso de memória O(1) extra (in-place), crucial com milhões
 *     de registros (evita alocações extras como no MergeSort).
 *   - Previsibilidade: o tempo de resposta é consistente,
 *     independente da ordem inicial dos dados.
 *   - ShellSort poderia ser mais rápido na prática em certos casos,
 *     mas sem garantia formal de O(n log n) no pior caso,
 *     tornando-o inadequado para sistemas críticos de alta escala.
 *
 * ---------------------------------------------------------------
 * QUESTÃO 5 - Heap em algoritmos de grafos
 * ---------------------------------------------------------------
 * O Heap (min-heap) é utilizado como Fila de Prioridade em grafos:
 *
 * Exemplo: Algoritmo de Dijkstra (menor caminho em grafos ponderados)
 *   - Mantém uma min-heap com pares (distância, vértice).
 *   - A cada iteração, extrai o vértice com menor distância acumulada
 *     em O(log n) em vez de O(n) com busca linear.
 *   - Ao relaxar arestas, insere/atualiza entradas na heap.
 *   - Complexidade total com heap binário: O((V + E) log V),
 *     onde V = vértices e E = arestas.
 *   - Sem heap (busca linear): O(V²) — ineficiente para grafos esparsos.
 *
 * Outros exemplos: algoritmo de Prim (MST), algoritmo A* (busca heurística).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================
 *  UTILITÁRIOS
 * ============================================================ */

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void printArray(const char *label, int arr[], int n) {
    printf("%s [", label);
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

/* ============================================================
 *  SHELLSORT
 *  Complexidade: depende da sequência de gaps.
 *  Sequência de Ciura usada: {701,301,132,57,23,10,4,1}
 * ============================================================ */

void shellSort(int arr[], int n) {
    /* Sequência de gaps de Ciura (2001) — melhor conhecida na prática */
    int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    int numGaps = 8;

    for (int g = 0; g < numGaps; g++) {
        int gap = gaps[g];
        if (gap >= n) continue;

        /* Insertion sort com gap */
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

/* ============================================================
 *  HEAPSORT
 *  Complexidade: O(n log n) garantido em todos os casos.
 * ============================================================ */

/* Mantém a propriedade de max-heap a partir do índice i */
void siftDown(int arr[], int i, int heapSize) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    if (left  < heapSize && arr[left]  > arr[largest]) largest = left;
    if (right < heapSize && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        siftDown(arr, largest, heapSize);
    }
}

/* Constrói o max-heap a partir de um vetor arbitrário */
void buildMaxHeap(int arr[], int n) {
    /* Começa do último nó interno */
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(arr, i, n);
    }
}

void heapSort(int arr[], int n) {
    buildMaxHeap(arr, n);

    for (int end = n - 1; end > 0; end--) {
        /* Maior elemento (raiz) vai para a posição correta */
        swap(&arr[0], &arr[end]);
        /* Restaura heap para os elementos restantes */
        siftDown(arr, 0, end);
    }
}

void demonstrarQuestao2() {
    printf("============================================================\n");
    printf("  QUESTÃO 2 — Construção do Max-Heap\n");
    printf("============================================================\n");

    int v[] = {30, 12, 45, 6, 18, 3};
    int n = 6;

    printArray("Vetor original:  ", v, n);

    /* Construir max-heap */
    buildMaxHeap(v, n);
    printArray("a) Max-Heap:     ", v, n);
    printf("   (esperado)    [45, 18, 30, 6, 12, 3]\n\n");

    /* Primeira extração da raiz */
    swap(&v[0], &v[n - 1]);   /* raiz vai para o fim */
    siftDown(v, 0, n - 1);    /* restaura heap de tamanho n-1 */

    printf("b) Após 1ª extração:\n");
    printf("   Heap ativo    [");
    for (int i = 0; i < n - 1; i++) {
        printf("%d", v[i]);
        if (i < n - 2) printf(", ");
    }
    printf("] | Ordenado: [%d]\n", v[n - 1]);
    printf("   (esperado)    [30, 18, 3, 6, 12] | [45]\n\n");
}

int isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1]) return 0;
    return 1;
}

void testCorrectness() {
    printf("============================================================\n");
    printf("  TESTE DE CORRETUDE\n");
    printf("============================================================\n");

    int tests[][8] = {
        {5, 3, 8, 1, 9, 2, 7, 4},
        {1, 2, 3, 4, 5, 6, 7, 8},   /* já ordenado */
        {8, 7, 6, 5, 4, 3, 2, 1},   /* ordem inversa */
        {1, 1, 1, 1, 1, 1, 1, 1},   /* todos iguais */
    };
    const char *names[] = {
        "Aleatório      ",
        "Já ordenado    ",
        "Ordem inversa  ",
        "Todos iguais   "
    };
    int sizes[] = {8, 8, 8, 8};
    int numTests = 4;

    for (int t = 0; t < numTests; t++) {
        int n = sizes[t];
        int a[8], b[8];
        copyArray(tests[t], a, n);
        copyArray(tests[t], b, n);

        shellSort(a, n);
        heapSort(b, n);

        printf("%-20s | ShellSort: %s | HeapSort: %s\n",
               names[t],
               isSorted(a, n) ? "OK ✓" : "ERRO ✗",
               isSorted(b, n) ? "OK ✓" : "ERRO ✗");
    }
    printf("\n");
}

void benchmark() {
    printf("============================================================\n");
    printf("  BENCHMARK — Comparação de desempenho\n");
    printf("============================================================\n");

    int sizes[] = {1000, 10000, 100000};
    int numSizes = 3;

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int *original = (int *)malloc(n * sizeof(int));
        int *arr      = (int *)malloc(n * sizeof(int));

        /* Gera vetor aleatório */
        srand(42);
        for (int i = 0; i < n; i++) original[i] = rand() % (n * 10);

        printf("n = %7d | ", n);

        /* ShellSort */
        copyArray(original, arr, n);
        clock_t start = clock();
        shellSort(arr, n);
        clock_t end = clock();
        double timeShell = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
        printf("ShellSort: %8.3f ms | ", timeShell);

        /* HeapSort */
        copyArray(original, arr, n);
        start = clock();
        heapSort(arr, n);
        end = clock();
        double timeHeap = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
        printf("HeapSort: %8.3f ms\n", timeHeap);

        free(original);
        free(arr);
    }
    printf("\n");
    printf("Observação: ShellSort costuma ser mais rápido na prática\n");
    printf("para entradas aleatórias, mas HeapSort garante O(n log n)\n");
    printf("em TODOS os casos, incluindo os piores cenários.\n\n");
}


int main(void) {
    printf("============================================================\n");
    printf("  Análise Comparativa: ShellSort vs HeapSort\n");
    printf("  Avaliação Individual — Estruturas de Dados\n");
    printf("============================================================\n\n");

    demonstrarQuestao2();
    testCorrectness();
    benchmark();

    printf("============================================================\n");
    printf("  RESUMO DAS RESPOSTAS TEÓRICAS\n");
    printf("============================================================\n");
    printf("Q1: HeapSort = O(n log n) garantido (estrutura heap determinística).\n");
    printf("    ShellSort = complexidade varia conforme sequência de gaps.\n\n");
    printf("Q2: a) Max-Heap: [45, 18, 30, 6, 12, 3]\n");
    printf("    b) Após 1a extracao: heap=[30,18,3,6,12], ordenado=[45]\n\n");
    printf("Q3: Gabarito: A) Apenas II e IV\n");
    printf("    II=VERDADEIRO (árvore binária completa), IV=VERDADEIRO\n");
    printf("    I=FALSO (ShellSort não é estável)\n");
    printf("    III=FALSO (gaps são do ShellSort, não do HeapSort)\n\n");
    printf("Q4: HeapSort é mais indicado para milhões de registros:\n");
    printf("    O(n log n) garantido + O(1) memória extra (in-place).\n\n");
    printf("Q5: Heap como fila de prioridade (min-heap) no Dijkstra:\n");
    printf("    extrai vértice de menor distância em O(log V),\n");
    printf("    reduzindo complexidade total para O((V+E) log V).\n");
    printf("============================================================\n");

    return 0;
}