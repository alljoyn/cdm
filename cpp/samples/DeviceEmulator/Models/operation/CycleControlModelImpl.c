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

#include "CycleControlModelImpl.h"
#include "../../../Utils/HAL.h"




static int HAL_Encode_CycleControl_OperationalState(FILE* fp, CycleControl_OperationalState value) UNUSED_OK;

static int HAL_Encode_CycleControl_OperationalState(FILE* fp, CycleControl_OperationalState value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_CycleControl_OperationalState(FILE* fp, CycleControl_OperationalState* value) UNUSED_OK;

static int HAL_Decode_CycleControl_OperationalState(FILE* fp, CycleControl_OperationalState* value)
{
    *value = (CycleControl_OperationalState)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_CycleControl_OperationalState(FILE* fp, Array_CycleControl_OperationalState value) UNUSED_OK;

static int HAL_Encode_Array_CycleControl_OperationalState(FILE* fp, Array_CycleControl_OperationalState value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_CycleControl_OperationalState(FILE* fp, Array_CycleControl_OperationalState* value) UNUSED_OK;

static int HAL_Decode_Array_CycleControl_OperationalState(FILE* fp, Array_CycleControl_OperationalState* value)
{
    InitArray_CycleControl_OperationalState(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_CycleControl_OperationalState(value, 1);
        value->elems[i] = (CycleControl_OperationalState)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}


static int HAL_Encode_CycleControl_OperationalCommands(FILE* fp, CycleControl_OperationalCommands value) UNUSED_OK;

static int HAL_Encode_CycleControl_OperationalCommands(FILE* fp, CycleControl_OperationalCommands value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_CycleControl_OperationalCommands(FILE* fp, CycleControl_OperationalCommands* value) UNUSED_OK;

static int HAL_Decode_CycleControl_OperationalCommands(FILE* fp, CycleControl_OperationalCommands* value)
{
    *value = (CycleControl_OperationalCommands)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_CycleControl_OperationalCommands(FILE* fp, Array_CycleControl_OperationalCommands value) UNUSED_OK;

static int HAL_Encode_Array_CycleControl_OperationalCommands(FILE* fp, Array_CycleControl_OperationalCommands value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_CycleControl_OperationalCommands(FILE* fp, Array_CycleControl_OperationalCommands* value) UNUSED_OK;

static int HAL_Decode_Array_CycleControl_OperationalCommands(FILE* fp, Array_CycleControl_OperationalCommands* value)
{
    InitArray_CycleControl_OperationalCommands(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_CycleControl_OperationalCommands(value, 1);
        value->elems[i] = (CycleControl_OperationalCommands)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}




static AJ_Status GetOperationalState(void *context, const char *objPath, CycleControl_OperationalState *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "CycleControl", "OperationalState");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "CycleControl", "OperationalState");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        int const value = {0};
        HAL_Encode_Int(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "CycleControl", "OperationalState");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(fp);
    *out = (CycleControl_OperationalState)(int)value;
    fclose(fp);
    return result;
}


static AJ_Status GetSupportedOperationalStates(void *context, const char *objPath, Array_CycleControl_OperationalState *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "CycleControl", "SupportedOperationalStates");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "CycleControl", "SupportedOperationalStates");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        Array_CycleControl_OperationalState const value = {0};
        HAL_Encode_Array_CycleControl_OperationalState(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "CycleControl", "SupportedOperationalStates");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    Array_CycleControl_OperationalState value;
    HAL_Decode_Array_CycleControl_OperationalState(fp, &value);

    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetSupportedOperationalCommands(void *context, const char *objPath, Array_CycleControl_OperationalCommands *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "CycleControl", "SupportedOperationalCommands");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "CycleControl", "SupportedOperationalCommands");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        Array_CycleControl_OperationalCommands const value = {0};
        HAL_Encode_Array_CycleControl_OperationalCommands(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "CycleControl", "SupportedOperationalCommands");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    Array_CycleControl_OperationalCommands value;
    HAL_Decode_Array_CycleControl_OperationalCommands(fp, &value);

    *out = value;
    fclose(fp);
    return result;
}




static AJ_Status MethodExecuteOperationalCommand(void *context, const char *objPath, CycleControl_OperationalCommands command)
{
    // TODO
    return AJ_ERR_FAILURE;
}



static CycleControlModel model = {
    GetOperationalState
    , GetSupportedOperationalStates
    , GetSupportedOperationalCommands

    , MethodExecuteOperationalCommand
};


CycleControlModel *GetCycleControlModel(void)
{
    return &model;
}