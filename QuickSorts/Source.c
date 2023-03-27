#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TESTS_COUNT 10
//#define PRINT_ARRAYS


#define QUICK_SORT(T, NAME)			    \
void NAME##Swap_m(T* a, T* b){		            \
        T c = *a;                                   \
        *a = *b;                                    \
        *b = c;                                     \
}                                                   \
void NAME(T* arr, int len, int (*comp)(T, T)) {     \
    if (len <= 1) {                                 \
        return;                                     \
    }                                               \
    int p = rand() % len;                           \
    T k = arr[p];                                   \
    NAME##Swap_m(arr, arr + p);                     \
    int i = 0;                                      \
    for (int j = 1; j < len; j++) {                 \
        if (comp(arr[j], k) < 0) {                  \
            i++;                                    \
            NAME##Swap_m(arr + i, arr + j);         \
        }                                           \
    }                                               \
    NAME##Swap_m(arr, arr + i);                     \
    NAME(arr, i, comp);                             \
    NAME(arr + i + 1, len - i - 1, comp);           \
}

void nullCheck(void* ptr) {
    if (ptr == NULL) {
        printf("Out of memory!");
        exit(0);
    }
}

void printArr(int* arr, int len) {
    printf("[");
    for (int i = 0; i < len - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[len - 1]);
}

void printStrArr(char** arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%s\n", arr[i]);
    }
}
void coutingSort(char** A, int N, int ind, char** buffer) {
    int K = 256;
    int* C = (int*)calloc(K, sizeof(int));
    nullCheck(C);
    for (int i = 0; i < N; i++) {
        C[A[i][ind]]++;
    }
    for (int i = 1; i < K; i++) {
        C[i] += C[i - 1];
    }
    for (int i = N - 1; i >= 0; i--) {
        buffer[--C[A[i][ind]]] = A[i];
    }
    free(C);
    for (int i = 0; i < N; i++) {
        A[i] = buffer[i];
    }
}

void radixSort(char** arr, int count, int len) {
    char** buffer = (char**)malloc(count * sizeof(char*));
    nullCheck(buffer);
    for (int i = len - 1; i >= 0; i--) {
        coutingSort(arr, count, i, buffer);
    }
    free(buffer);
}

QUICK_SORT(int, quickSort_int)
QUICK_SORT(char*, quickSort_str)

int intComp(int a, int b) {
    return a - b;
}

inline void swap(int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void sortColors(int* nums, int numsSize) {
    int l = 0;
    int h = numsSize - 1;
    for (int i = 0; i <= h; i++) {
        if (nums[i] == 0) {
            swap(nums + i, nums + l++);
        }
        else if (nums[i] == 2) {
            swap(nums + i--, nums + h--);
        }
    }
}
int main() {
    unsigned int seed = 100;
    int strLen = 10;
    int N = 8;

    srand(seed);
    for (int testNumber = 0; testNumber < TESTS_COUNT; testNumber++) {
        char** arr1 = (char**)malloc(N * sizeof(char*));
        nullCheck(arr1);
        char** arr2 = (char**)malloc(N * sizeof(char*));
        nullCheck(arr2);
        for (int i = 0; i < N; i++) {
            char* ptr = (char*)malloc((strLen + 1) * sizeof(char));
            nullCheck(ptr);
            for (int j = 0; j < strLen; j++) {
                ptr[j] = rand() % 26 + 65;
            }
            ptr[strLen] = '\0';
            arr1[i] = ptr;
            arr2[i] = ptr;
        }
        quickSort_str(arr1, N, strcmp);
        radixSort(arr2, N, strLen);

#ifdef PRINT_ARRAYS
        printStrArr(arr1, N);
        printf("\n");
        printStrArr(arr2, N);
#endif


        int flag = 0;
        for (int i = 0; i < N; i++) {
            if (arr1[i] != arr2[i]) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            printf("Test failed\n");
        }
        else {
            printf("Test passed\n");
        }

        for (int i = 0; i < N; i++) {
            free(arr1[i]);
        }
        free(arr1);
        free(arr2);
    }
}
