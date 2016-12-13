/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "RobotCleaningCyclePhaseModelImpl.h"
#include "../../../Utils/HAL.h"





static int HAL_Encode_RobotCleaningCyclePhase_CyclePhaseDescriptor(FILE* fp, RobotCleaningCyclePhase_CyclePhaseDescriptor value) UNUSED_OK;

static int HAL_Encode_RobotCleaningCyclePhase_CyclePhaseDescriptor(FILE* fp, RobotCleaningCyclePhase_CyclePhaseDescriptor value)
{
    HAL_Encode_OpenStruct(fp);
    HAL_Encode_UInt(fp, value.phase);
    HAL_Encode_String(fp, value.name);
    HAL_Encode_String(fp, value.description);
    HAL_Encode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Decode_RobotCleaningCyclePhase_CyclePhaseDescriptor(FILE* fp, RobotCleaningCyclePhase_CyclePhaseDescriptor* value) UNUSED_OK;

static int HAL_Decode_RobotCleaningCyclePhase_CyclePhaseDescriptor(FILE* fp, RobotCleaningCyclePhase_CyclePhaseDescriptor* value)
{
    HAL_Decode_OpenStruct(fp);
    value->phase = HAL_Decode_UInt(fp);
    value->name = HAL_Decode_String(fp);
    value->description = HAL_Decode_String(fp);
    HAL_Decode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_RobotCleaningCyclePhase_CyclePhaseDescriptor(FILE* fp, Array_RobotCleaningCyclePhase_CyclePhaseDescriptor value) UNUSED_OK;

static int HAL_Encode_Array_RobotCleaningCyclePhase_CyclePhaseDescriptor(FILE* fp, Array_RobotCleaningCyclePhase_CyclePhaseDescriptor value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_RobotCleaningCyclePhase_CyclePhaseDescriptor(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_RobotCleaningCyclePhase_CyclePhaseDescriptor(FILE* fp, Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* value) UNUSED_OK;

static int HAL_Decode_Array_RobotCleaningCyclePhase_CyclePhaseDescriptor(FILE* fp, Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* value)
{
    InitArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(value, 1);
        HAL_Decode_RobotCleaningCyclePhase_CyclePhaseDescriptor(fp, &value->elems[i]);
    }
    return AJ_OK;
}

static Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* getPhases(void)
{
    static Array_RobotCleaningCyclePhase_CyclePhaseDescriptor s_phases;

    if (!s_phases.elems) {
        InitArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(&s_phases, 0);
        size_t i = 0;

        i = ExtendArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 1;
        s_phases.elems[i].name = strdup("seek");
        s_phases.elems[i].description = strdup("Seek some dirt");

        i = ExtendArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 2;
        s_phases.elems[i].name = strdup("suck");
        s_phases.elems[i].description = strdup("Such it up");
    }

    return &s_phases;
}



static AJ_Status GetCyclePhase(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "RobotCleaningCyclePhase", "CyclePhase");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "RobotCleaningCyclePhase", "CyclePhase");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "RobotCleaningCyclePhase", "CyclePhase");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetSupportedCyclePhases(void *context, const char *objPath, Array_uint8 *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "RobotCleaningCyclePhase", "SupportedCyclePhases");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "RobotCleaningCyclePhase", "SupportedCyclePhases");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        Array_uint8 const value = {0};
        HAL_Encode_Array_uint8(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "RobotCleaningCyclePhase", "SupportedCyclePhases");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    Array_uint8 value;
    HAL_Decode_Array_uint8(fp, &value);

    *out = value;
    fclose(fp);
    return result;
}




static AJ_Status MethodGetVendorPhasesDescription(void *context, const char *objPath, char const* languageTag, Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* phasesDescription)
{
    Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* phases = getPhases();
    CopyArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(phases, phasesDescription);
    return AJ_OK;
}



static RobotCleaningCyclePhaseModel model = {
    GetCyclePhase
    , GetSupportedCyclePhases

    , MethodGetVendorPhasesDescription
};


RobotCleaningCyclePhaseModel *GetRobotCleaningCyclePhaseModel(void)
{
    return &model;
}