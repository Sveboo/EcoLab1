﻿/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoLab1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef LAB1_IECOLAB1EVENTS_H
#define LAB1_IECOLAB1EVENTS_H

#include "IEcoBase1.h"

/* IEcoLab1Events IID = {B6D38661-6827-46D9-9135-FD4B204A68D7} */
#ifndef __IID_IEcoLab1Events
static const UGUID IID_IEcoLab1Events = {0x01, 0x10, 0xB6, 0xD3, 0x86, 0x61, 0x68, 0x27, 0x46, 0xD9, 0x91, 0x35, 0xFD, 0x4B, 0x20, 0x4A, 0x68, 0xD7};
#endif /* __IID_IEcoLab1Events */

/* Обратный интерфейс */
typedef struct IEcoLab1VTblEvents {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface )(/* in */ struct IEcoLab1Events* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef )(/* in */ struct IEcoLab1Events* me);
    uint32_t (ECOCALLMETHOD *Release )(/* in */ struct IEcoLab1Events* me);

    /* IEcoLab1Events */
    int16_t (ECOCALLMETHOD *OnInsertSortCall)(/* in */ struct IEcoLab1Events* me);
    int16_t (ECOCALLMETHOD *OnSwapCall)(/* in */ struct IEcoLab1Events* me, int step, int index, const void *startPtr, size_t size);
    int16_t (ECOCALLMETHOD *BeforeSort)(/* in */ struct IEcoLab1Events* me, /* in */ const void *startPtr, size_t size);
    int16_t (ECOCALLMETHOD *AfterSort)(/* in */ struct IEcoLab1Events* me, /* in */ const void *startPtr, size_t size);

} IEcoLab1VTblEvents, *IEcoLab1VTblEventsPtr;

interface IEcoLab1Events {
    struct IEcoLab1VTblEvents *pVTbl;
} IEcoLab1Events;


#endif //LAB1_IECOLAB1EVENTS_H
