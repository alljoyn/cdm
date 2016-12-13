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

#include "AudioVolumeModelImpl.h"
#include "../../../Utils/HAL.h"






static AJ_Status GetVolume(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "AudioVolume", "Volume");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "AudioVolume", "Volume");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "AudioVolume", "Volume");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}



static AJ_Status SetVolume(void *context, const char *objPath, uint8_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "AudioVolume", "Volume");
    HAL_Encode_UInt(fp, value);
    fclose(fp);
    return result;
}


static AJ_Status GetMaxVolume(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "AudioVolume", "MaxVolume");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "AudioVolume", "MaxVolume");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "AudioVolume", "MaxVolume");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetMute(void *context, const char *objPath, bool *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "AudioVolume", "Mute");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "AudioVolume", "Mute");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        int64_t const value = {0};
        HAL_Encode_Int(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "AudioVolume", "Mute");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    int64_t value;
    value = HAL_Decode_Int(fp);
    *out = value;
    fclose(fp);
    return result;
}



static AJ_Status SetMute(void *context, const char *objPath, bool input)
{
    AJ_Status result = AJ_OK;
    int64_t value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "AudioVolume", "Mute");
    HAL_Encode_Int(fp, value);
    fclose(fp);
    return result;
}




static AudioVolumeModel model = {
    GetVolume
    , SetVolume
    , GetMaxVolume
    , GetMute
    , SetMute

};


AudioVolumeModel *GetAudioVolumeModel(void)
{
    return &model;
}