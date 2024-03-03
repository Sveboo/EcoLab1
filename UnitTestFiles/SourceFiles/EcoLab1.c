/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

/* функция для сравнения double */
int __cdecl compareDouble(const void *xPtr, const void *yPtr) {
    double x = *(double *)xPtr, y = *(double *)yPtr;
    return (x > y) - (y > x);
}

/* функция для сравнения float */
int __cdecl compareFloat(const void *xPtr, const void *yPtr) {
    float x = *(float *)xPtr, y = *(float *)yPtr;
    return (x > y) - (y > x);
}

int __cdecl compareInt(const void *xPtr, const void *yPtr) {
    int x = *(int *)xPtr, y = *(int *)yPtr;
    return (x > y) - (y > x);
}

/* функция для сравнения string */
int __cdecl compareString(const void *xPtr, const void *yPtr) {
    char *x = *(char **)xPtr, *y = *(char **)yPtr;
    return strcmp(x, y);
}

/* функци  для инициализации массивов */
void *initIntArr(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    int *arr = (int *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));
    for (i = 0; i < size; i++) {
        arr[i] = rand() % 10000 - 5001;
    }
    return arr;
}

void *initFloatArr(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    float *arr = (float *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(float));
    for (i = 0; i < size; i++) {
        arr[i] = ((float) (rand() % 10000 - 5001)) / ((float)(rand() % 1010 + 1)) ;
    }
    return arr;
}

void *initDoubleArr(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    double *arr = (double *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(double));
    for (i = 0; i < size; i++) {
        arr[i] = ((double) (rand() % 10000 - 5001)) / ((float)(rand() % 1010 + 1)) ;
    }
    return arr;
}

void *initStringArr(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i, j, str_size;
    char **arr = (char **) pIMem->pVTbl->Alloc(pIMem, size * sizeof(char *));
    for (i = 0; i < size; i++) {
        arr[i] = (char *) pIMem->pVTbl->Alloc(pIMem, 30 * sizeof(char));
        str_size = rand() % 15 + 5;
        for (j = 0; j < str_size; ++j) {
            arr[i][j] = (char) (rand() % ('z' - 'a' + 1) + 'a');
        }
        arr[i][str_size] = 0;
    }
    return arr;
}

/* функции удаления */

void deleteArray(IEcoMemoryAllocator1 *pIMem, void *arr_ptr, size_t size) {
    pIMem->pVTbl->Free(pIMem, arr_ptr);
}

void deleteStringArray(IEcoMemoryAllocator1 *pIMem, void *arr_ptr, size_t size) {
    size_t i;
    char **arr = (char **) arr_ptr;
    for (i = 0; i < size; ++i) {
        pIMem->pVTbl->Free(pIMem, arr[i]);
    }
    pIMem->pVTbl->Free(pIMem, arr_ptr);
}

/* функции тестирования */
void testSortString(IEcoLab1 *pIEcoLab1, FILE *file, size_t arrSize, IEcoMemoryAllocator1 *pIMem){
    clock_t begin, end;
    double insertRes, quickRes;
    size_t i;
    char** arr1 = (char **)initStringArr(pIMem,arrSize);

    char** srcArr = (char **) arr1;
    char** arr2 = pIMem->pVTbl->Alloc(pIMem, arrSize * sizeof(char*));
    for (i = 0; i < arrSize; i++) {
        arr2[i] = (char *) pIMem->pVTbl->Alloc(pIMem, 30 * sizeof(char));
        pIMem->pVTbl->Copy(pIMem, arr2[i], srcArr[i], 30);
    }

    begin = clock();
    pIEcoLab1 ->pVTbl ->qsort(pIEcoLab1, arr1, arrSize, sizeof(char *), compareString);

    end = clock();
    insertRes = (double)(end - begin);
    for (i = 0; i < arrSize - 1; i++){
        if (strcmp(*(char **)arr1, *(char **)(arr1 + sizeof(char))) > 0) {
            printf("String insertion sort doesn't work (size: %d).\n", arrSize);
            return;
        }
    }

    begin = clock();
    qsort(arr2, arrSize, sizeof(char*), compareString);
    end = clock();

    quickRes = (double )(end - begin);
    deleteStringArray(pIMem, arr1, arrSize);
    deleteStringArray(pIMem, arr2, arrSize);

    fprintf(file, "%s,%s,%d,%lf\n", "insert", "string", arrSize, insertRes);
    fprintf(file, "%s,%s,%d,%lf\n", "quick", "string", arrSize, quickRes);
}

void testSortInt(IEcoLab1 *pIEcoLab1, FILE *file, size_t arrSize, IEcoMemoryAllocator1 *pIMem){
    clock_t begin, end;
    double insertRes, quickRes;
    size_t i;
    int* arr1 = initIntArr(pIMem,arrSize);

    int *arr2 = (int *) pIMem->pVTbl->Alloc(pIMem, arrSize * sizeof(int));
    pIMem->pVTbl->Copy(pIMem, arr2, arr1, arrSize * sizeof(int));

    begin = clock();
    pIEcoLab1 ->pVTbl ->qsort(pIEcoLab1, arr1, arrSize, sizeof(int), compareInt);
    end = clock();

    insertRes = (double)(end - begin);

    for (i = 0; i < arrSize - 1; i++){
        if (arr1[i] > arr1[i + 1]) {
            printf("Int insertion sort doesn't work (size: %d).\n", arrSize);
            return;
        }
    }

//    printf("Check 1\n");
    begin = clock();
    qsort(arr2, arrSize, sizeof(int), compareInt);
    end = clock();

    quickRes = (double )(end - begin);
    deleteArray(pIMem, arr1, arrSize);
    deleteArray(pIMem, arr2, arrSize);

    fprintf(file, "%s,%s,%d,%lf\n", "insert", "int", arrSize, insertRes);
    fprintf(file, "%s,%s,%d,%lf\n", "quick", "int", arrSize, quickRes);
}

void testSortFloat(IEcoLab1 *pIEcoLab1, FILE *file, size_t arrSize, IEcoMemoryAllocator1 *pIMem){
    clock_t begin, end;
    double insertRes, quickRes;
    size_t i;
    float* arr1 = initFloatArr(pIMem,arrSize);
    float *arr2 = (float *) pIMem->pVTbl->Alloc(pIMem, arrSize * sizeof(float));
    pIMem->pVTbl->Copy(pIMem, arr2, arr1, arrSize * sizeof(float));

    begin = clock();
    pIEcoLab1 ->pVTbl ->qsort(pIEcoLab1, arr1, arrSize, sizeof(float), compareFloat);
    end = clock();

    insertRes = (double)(end - begin);

    for (i = 0; i < arrSize - 1; i++){
        if (arr1[i] > arr1[i + 1]) {
            printf("Float insertion sort doesn't work (size: %d).\n", arrSize);
            return;
        }
    }


    begin = clock();
    qsort(arr2, arrSize, sizeof(float), compareFloat);
    end = clock();

    quickRes = (double )(end - begin);
    deleteArray(pIMem, arr1, arrSize);
    deleteArray(pIMem, arr2, arrSize);

    fprintf(file, "%s,%s,%d,%lf\n", "insert", "float", arrSize, insertRes);
    fprintf(file, "%s,%s,%d,%lf\n", "quick", "float", arrSize, quickRes);
}

void testSortDouble(IEcoLab1 *pIEcoLab1, FILE *file, size_t arrSize, IEcoMemoryAllocator1 *pIMem){
    clock_t begin, end;
    double insertRes, quickRes;
    size_t i;
    double* arr1 = initDoubleArr(pIMem,arrSize);

    double *arr2 = (double *) pIMem->pVTbl->Alloc(pIMem, arrSize * sizeof(double ));
    pIMem->pVTbl->Copy(pIMem, arr2, arr1, arrSize * sizeof(double ));

    begin = clock();
    pIEcoLab1 ->pVTbl ->qsort(pIEcoLab1, arr1, arrSize, sizeof(double), compareDouble);
    end = clock();

    insertRes = (double)(end - begin);

    for (i = 0; i < arrSize - 1; i++){
        if (arr1[i] > arr1[i + 1]) {
            printf("Double insertion sort doesn't work (size: %d).\n", arrSize);
            return;
        }
    }


    begin = clock();
    qsort(arr2, arrSize, sizeof(double), compareDouble);
    end = clock();

    quickRes = (double )(end - begin);
    deleteArray(pIMem, arr1, arrSize);
    deleteArray(pIMem, arr2, arrSize);

    fprintf(file, "%s,%s,%d,%lf\n", "insert", "double", arrSize, insertRes);
    fprintf(file, "%s,%s,%d,%lf\n", "quick", "double", arrSize, quickRes);
}
/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    size_t i, sizes[5] = {1000,  5000, 10000, 50000, 100000};

    /* Проверка и создание системного интрефейса */
    result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **) &pISys);
    if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
//#ifdef ECO_LIB
//    /* Регистрация статического компонента для работы со списком */
//    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
//    if (result != 0 ) {
//        /* Освобождение в случае ошибки */
//        goto Release;
//    }
//#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    FILE * resultFile;
    srand(time(0));
    fopen_s(&resultFile, "result.csv", "w");
    fprintf(resultFile, "sort,type,size,time\n");


    for (i = 0; i < 5; i++) {
        testSortString(pIEcoLab1, resultFile, sizes[i], pIMem);
        testSortInt(pIEcoLab1, resultFile, sizes[i], pIMem);
        testSortFloat(pIEcoLab1, resultFile, sizes[i], pIMem);
        testSortDouble(pIEcoLab1, resultFile, sizes[i], pIMem);
    }


    fclose(resultFile);

Release:
    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

