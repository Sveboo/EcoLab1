﻿/*
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
#include "IEcoCalculatorY.h"
#include "IEcoCalculatorX.h"

#include "IdEcoLab2.h"
#include <stdio.h>

int __cdecl compareInt(const void *xPtr, const void *yPtr) {
    int x = *(int *)xPtr, y = *(int *)yPtr;
    return (x > y) - (y > x);
}


/* функция  для инициализации массива Int*/
void *initIntArr(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    int *arr = (int *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));
    for (i = 0; i < size; i++) {
        arr[i] = rand() % 10000 - 5001;
    }
    return arr;
}

/* функция печати массива */
void printIntArray(void *array, size_t size) {
    int * arr = (int *) array;
    size_t i;
    for (i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
}

/* функция удаления массива*/
void deleteArray(IEcoMemoryAllocator1 *pIMem, void *arr_ptr, size_t size) {
    pIMem->pVTbl->Free(pIMem, arr_ptr);
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

    IEcoCalculatorY* pIY = 0;
    IEcoCalculatorX* pIX = 0;

    IEcoLab1* pIEcoLab2 = 0;

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

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result != 0 || pIY == 0) {
        goto Release;
    }

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result != 0 || pIX == 0) {
        goto Release;
    }

    size_t i, size;
    size = 2;
    // Значения для тестирования функций
    int16_t *testValues = (int16_t *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(int16_t));
    for (i = 0; i < size; i++) {
        testValues[i] = rand() % 100 - 15;
    }

    printf("Start components testing:\n");

    printf("Addition: %d + %d = %d\n Right answer: %d\n", testValues[0], testValues[1],
           pIX->pVTbl->Addition(pIX, testValues[0], testValues[1]), testValues[0] + testValues[1]);

    printf("Subtraction: %d - %d = %d\n Right answer: %d\n", testValues[0], testValues[1],
           pIX->pVTbl->Subtraction(pIX, testValues[0], testValues[1]), testValues[0] - testValues[1]);

    pIX->pVTbl->Release(pIX);

    printf("Multiplication: %d * %d = %d\n Right answer: %d\n", testValues[0], testValues[1],
           pIY->pVTbl->Multiplication(pIY, testValues[0], testValues[1]), testValues[0] * testValues[1]);

    printf("Division: %d / %d = %d\n Right answer: %d\n", testValues[0], testValues[1],
           pIY->pVTbl->Division(pIY, testValues[0], testValues[1]), testValues[0] / testValues[1]);

    pIX->pVTbl->Release(pIY);

    printf("\nStart checking interface properties with help QueryInterface:\n");

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result == 0) {
        pIX->pVTbl->Release(pIX);
        printf("Can get pointer to IX via IEcoLab1\n");
    }
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result == 0) {
        pIY->pVTbl->Release(pIY);
        printf("Can get pointer to IY via IEcoLab1\n");
    }
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoLab1, (void **) &pIEcoLab1);
    if (result == 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
        printf("Can get pointer to IEcoLab1 via IEcoLab1\n");
    }

    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result == 0) {
        pIX->pVTbl->Release(pIX);
        printf("Can get pointer to IX via IY\n");
    }
    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result == 0) {
        pIY->pVTbl->Release(pIY);
        printf("Can get pointer to IY via IY\n");
    }
    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoLab1, (void **) &pIEcoLab1);
    if (result == 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
        printf("Can get pointer to IEcoLab1 via IY\n");
    }

    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result == 0) {
        pIX->pVTbl->Release(pIX);
        printf("Can get pointer to IX via IX\n");
    }
    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result == 0) {
        pIY->pVTbl->Release(pIY);
        printf("Can get pointer to IY via IX\n");
    }
    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoLab1, (void **) &pIEcoLab1);
    if (result == 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
        printf("Can get pointer to IEcoLab1 via IX\n");
    }

    printf("\nStart testing sort interface using aggregated component:\n");
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab1, (void**) &pIEcoLab2);
    if (result == 0) {
        printf("Can aggregate IEcoLab1 interface using CEcoLab2\n");
    }

    printf("\nStart testing sort function:\n");
    void *testArr = 0;
    size_t testSize = 10;
    testArr = initIntArr(pIMem, testSize);
    printf("Array\n");
    printIntArray(testArr, testSize);

    pIEcoLab2->pVTbl->qsort(pIEcoLab2, testArr, testSize, sizeof(int), compareInt);

    printf("Sorted array\n");
    printIntArray(testArr, testSize);

    deleteArray(pIMem, testArr, testSize);


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

    if (pIEcoLab2 != 0) {
        pIEcoLab2->pVTbl->Release(pIEcoLab2);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

