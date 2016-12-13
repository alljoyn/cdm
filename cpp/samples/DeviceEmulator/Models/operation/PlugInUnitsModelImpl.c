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

#include "PlugInUnitsModelImpl.h"
#include "../../../Utils/HAL.h"





static int HAL_Encode_PlugInUnits_PlugInInfo(FILE* fp, PlugInUnits_PlugInInfo value) UNUSED_OK;

static int HAL_Encode_PlugInUnits_PlugInInfo(FILE* fp, PlugInUnits_PlugInInfo value)
{
    HAL_Encode_OpenStruct(fp);
    HAL_Encode_String(fp, value.objectPath);
    HAL_Encode_UInt(fp, value.deviceId);
    HAL_Encode_Int(fp, value.pluggedIn);
    HAL_Encode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Decode_PlugInUnits_PlugInInfo(FILE* fp, PlugInUnits_PlugInInfo* value) UNUSED_OK;

static int HAL_Decode_PlugInUnits_PlugInInfo(FILE* fp, PlugInUnits_PlugInInfo* value)
{
    HAL_Decode_OpenStruct(fp);
    value->objectPath = HAL_Decode_String(fp);
    value->deviceId = HAL_Decode_UInt(fp);
    value->pluggedIn = HAL_Decode_Int(fp);
    HAL_Decode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_PlugInUnits_PlugInInfo(FILE* fp, Array_PlugInUnits_PlugInInfo value) UNUSED_OK;

static int HAL_Encode_Array_PlugInUnits_PlugInInfo(FILE* fp, Array_PlugInUnits_PlugInInfo value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_PlugInUnits_PlugInInfo(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_PlugInUnits_PlugInInfo(FILE* fp, Array_PlugInUnits_PlugInInfo* value) UNUSED_OK;

static int HAL_Decode_Array_PlugInUnits_PlugInInfo(FILE* fp, Array_PlugInUnits_PlugInInfo* value)
{
    InitArray_PlugInUnits_PlugInInfo(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_PlugInUnits_PlugInInfo(value, 1);
        HAL_Decode_PlugInUnits_PlugInInfo(fp, &value->elems[i]);
    }
    return AJ_OK;
}




static AJ_Status GetPlugInUnits(void *context, const char *objPath, Array_PlugInUnits_PlugInInfo *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "PlugInUnits", "PlugInUnits");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "PlugInUnits", "PlugInUnits");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        Array_PlugInUnits_PlugInInfo const value = {0};
        HAL_Encode_Array_PlugInUnits_PlugInInfo(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "PlugInUnits", "PlugInUnits");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    Array_PlugInUnits_PlugInInfo value;
    HAL_Decode_Array_PlugInUnits_PlugInInfo(fp, &value);

    *out = value;
    fclose(fp);
    return result;
}




static PlugInUnitsModel model = {
    GetPlugInUnits

};


PlugInUnitsModel *GetPlugInUnitsModel(void)
{
    return &model;
}