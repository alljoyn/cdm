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

#include "WindDirectionModelImpl.h"
#include "../../../Utils/HAL.h"




static int HAL_Encode_WindDirection_AutoMode(FILE* fp, WindDirection_AutoMode value) UNUSED_OK;

static int HAL_Encode_WindDirection_AutoMode(FILE* fp, WindDirection_AutoMode value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_WindDirection_AutoMode(FILE* fp, WindDirection_AutoMode* value) UNUSED_OK;

static int HAL_Decode_WindDirection_AutoMode(FILE* fp, WindDirection_AutoMode* value)
{
    *value = (WindDirection_AutoMode)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_WindDirection_AutoMode(FILE* fp, Array_WindDirection_AutoMode value) UNUSED_OK;

static int HAL_Encode_Array_WindDirection_AutoMode(FILE* fp, Array_WindDirection_AutoMode value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_WindDirection_AutoMode(FILE* fp, Array_WindDirection_AutoMode* value) UNUSED_OK;

static int HAL_Decode_Array_WindDirection_AutoMode(FILE* fp, Array_WindDirection_AutoMode* value)
{
    InitArray_WindDirection_AutoMode(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_WindDirection_AutoMode(value, 1);
        value->elems[i] = (WindDirection_AutoMode)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}




static AJ_Status GetHorizontalDirection(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "HorizontalDirection");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "WindDirection", "HorizontalDirection");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "HorizontalDirection");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}



static AJ_Status SetHorizontalDirection(void *context, const char *objPath, uint16_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "WindDirection", "HorizontalDirection");
    HAL_Encode_UInt(fp, value);
    fclose(fp);
    return result;
}


static AJ_Status GetHorizontalMax(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "HorizontalMax");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "WindDirection", "HorizontalMax");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "HorizontalMax");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetHorizontalAutoMode(void *context, const char *objPath, WindDirection_AutoMode *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "HorizontalAutoMode");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "WindDirection", "HorizontalAutoMode");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        int const value = {0};
        HAL_Encode_Int(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "HorizontalAutoMode");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(fp);
    *out = (WindDirection_AutoMode)(int)value;
    fclose(fp);
    return result;
}



static AJ_Status SetHorizontalAutoMode(void *context, const char *objPath, WindDirection_AutoMode input)
{
    AJ_Status result = AJ_OK;
    int value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "WindDirection", "HorizontalAutoMode");
    HAL_Encode_Int(fp, value);
    fclose(fp);
    return result;
}


static AJ_Status GetVerticalDirection(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "VerticalDirection");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "WindDirection", "VerticalDirection");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "VerticalDirection");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}



static AJ_Status SetVerticalDirection(void *context, const char *objPath, uint16_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "WindDirection", "VerticalDirection");
    HAL_Encode_UInt(fp, value);
    fclose(fp);
    return result;
}


static AJ_Status GetVerticalMax(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "VerticalMax");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "WindDirection", "VerticalMax");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "VerticalMax");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetVerticalAutoMode(void *context, const char *objPath, WindDirection_AutoMode *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "VerticalAutoMode");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "WindDirection", "VerticalAutoMode");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        int const value = {0};
        HAL_Encode_Int(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "WindDirection", "VerticalAutoMode");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(fp);
    *out = (WindDirection_AutoMode)(int)value;
    fclose(fp);
    return result;
}



static AJ_Status SetVerticalAutoMode(void *context, const char *objPath, WindDirection_AutoMode input)
{
    AJ_Status result = AJ_OK;
    int value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "WindDirection", "VerticalAutoMode");
    HAL_Encode_Int(fp, value);
    fclose(fp);
    return result;
}




static WindDirectionModel model = {
    GetHorizontalDirection
    , SetHorizontalDirection
    , GetHorizontalMax
    , GetHorizontalAutoMode
    , SetHorizontalAutoMode
    , GetVerticalDirection
    , SetVerticalDirection
    , GetVerticalMax
    , GetVerticalAutoMode
    , SetVerticalAutoMode

};


WindDirectionModel *GetWindDirectionModel(void)
{
    return &model;
}