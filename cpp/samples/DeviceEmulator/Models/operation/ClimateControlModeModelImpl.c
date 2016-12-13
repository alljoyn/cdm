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

#include "ClimateControlModeModelImpl.h"
#include "../../../Utils/HAL.h"




static int HAL_Encode_ClimateControlMode_Mode(FILE* fp, ClimateControlMode_Mode value) UNUSED_OK;

static int HAL_Encode_ClimateControlMode_Mode(FILE* fp, ClimateControlMode_Mode value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_ClimateControlMode_Mode(FILE* fp, ClimateControlMode_Mode* value) UNUSED_OK;

static int HAL_Decode_ClimateControlMode_Mode(FILE* fp, ClimateControlMode_Mode* value)
{
    *value = (ClimateControlMode_Mode)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_ClimateControlMode_Mode(FILE* fp, Array_ClimateControlMode_Mode value) UNUSED_OK;

static int HAL_Encode_Array_ClimateControlMode_Mode(FILE* fp, Array_ClimateControlMode_Mode value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_ClimateControlMode_Mode(FILE* fp, Array_ClimateControlMode_Mode* value) UNUSED_OK;

static int HAL_Decode_Array_ClimateControlMode_Mode(FILE* fp, Array_ClimateControlMode_Mode* value)
{
    InitArray_ClimateControlMode_Mode(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_ClimateControlMode_Mode(value, 1);
        value->elems[i] = (ClimateControlMode_Mode)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}


static int HAL_Encode_ClimateControlMode_OperationalState(FILE* fp, ClimateControlMode_OperationalState value) UNUSED_OK;

static int HAL_Encode_ClimateControlMode_OperationalState(FILE* fp, ClimateControlMode_OperationalState value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_ClimateControlMode_OperationalState(FILE* fp, ClimateControlMode_OperationalState* value) UNUSED_OK;

static int HAL_Decode_ClimateControlMode_OperationalState(FILE* fp, ClimateControlMode_OperationalState* value)
{
    *value = (ClimateControlMode_OperationalState)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_ClimateControlMode_OperationalState(FILE* fp, Array_ClimateControlMode_OperationalState value) UNUSED_OK;

static int HAL_Encode_Array_ClimateControlMode_OperationalState(FILE* fp, Array_ClimateControlMode_OperationalState value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_ClimateControlMode_OperationalState(FILE* fp, Array_ClimateControlMode_OperationalState* value) UNUSED_OK;

static int HAL_Decode_Array_ClimateControlMode_OperationalState(FILE* fp, Array_ClimateControlMode_OperationalState* value)
{
    InitArray_ClimateControlMode_OperationalState(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_ClimateControlMode_OperationalState(value, 1);
        value->elems[i] = (ClimateControlMode_OperationalState)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}




static AJ_Status GetMode(void *context, const char *objPath, ClimateControlMode_Mode *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "ClimateControlMode", "Mode");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "ClimateControlMode", "Mode");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        int const value = {0};
        HAL_Encode_Int(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "ClimateControlMode", "Mode");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(fp);
    *out = (ClimateControlMode_Mode)(int)value;
    fclose(fp);
    return result;
}



static AJ_Status SetMode(void *context, const char *objPath, ClimateControlMode_Mode input)
{
    AJ_Status result = AJ_OK;
    int value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "ClimateControlMode", "Mode");
    HAL_Encode_Int(fp, value);
    fclose(fp);
    return result;
}


static AJ_Status GetSupportedModes(void *context, const char *objPath, Array_ClimateControlMode_Mode *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "ClimateControlMode", "SupportedModes");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "ClimateControlMode", "SupportedModes");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        Array_ClimateControlMode_Mode const value = {0};
        HAL_Encode_Array_ClimateControlMode_Mode(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "ClimateControlMode", "SupportedModes");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    Array_ClimateControlMode_Mode value;
    HAL_Decode_Array_ClimateControlMode_Mode(fp, &value);

    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetOperationalState(void *context, const char *objPath, ClimateControlMode_OperationalState *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "ClimateControlMode", "OperationalState");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "ClimateControlMode", "OperationalState");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        int const value = {0};
        HAL_Encode_Int(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "ClimateControlMode", "OperationalState");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(fp);
    *out = (ClimateControlMode_OperationalState)(int)value;
    fclose(fp);
    return result;
}




static ClimateControlModeModel model = {
    GetMode
    , SetMode
    , GetSupportedModes
    , GetOperationalState

};


ClimateControlModeModel *GetClimateControlModeModel(void)
{
    return &model;
}