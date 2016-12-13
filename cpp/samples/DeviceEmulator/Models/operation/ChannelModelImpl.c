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

#include "ChannelModelImpl.h"
#include "../../../Utils/HAL.h"





static int HAL_Encode_Channel_ChannelInfoRecord(FILE* fp, Channel_ChannelInfoRecord value) UNUSED_OK;

static int HAL_Encode_Channel_ChannelInfoRecord(FILE* fp, Channel_ChannelInfoRecord value)
{
    HAL_Encode_OpenStruct(fp);
    HAL_Encode_String(fp, value.channelID);
    HAL_Encode_String(fp, value.channelNumber);
    HAL_Encode_String(fp, value.channelName);
    HAL_Encode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Decode_Channel_ChannelInfoRecord(FILE* fp, Channel_ChannelInfoRecord* value) UNUSED_OK;

static int HAL_Decode_Channel_ChannelInfoRecord(FILE* fp, Channel_ChannelInfoRecord* value)
{
    HAL_Decode_OpenStruct(fp);
    value->channelID = HAL_Decode_String(fp);
    value->channelNumber = HAL_Decode_String(fp);
    value->channelName = HAL_Decode_String(fp);
    HAL_Decode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_Channel_ChannelInfoRecord(FILE* fp, Array_Channel_ChannelInfoRecord value) UNUSED_OK;

static int HAL_Encode_Array_Channel_ChannelInfoRecord(FILE* fp, Array_Channel_ChannelInfoRecord value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Channel_ChannelInfoRecord(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_Channel_ChannelInfoRecord(FILE* fp, Array_Channel_ChannelInfoRecord* value) UNUSED_OK;

static int HAL_Decode_Array_Channel_ChannelInfoRecord(FILE* fp, Array_Channel_ChannelInfoRecord* value)
{
    InitArray_Channel_ChannelInfoRecord(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_Channel_ChannelInfoRecord(value, 1);
        HAL_Decode_Channel_ChannelInfoRecord(fp, &value->elems[i]);
    }
    return AJ_OK;
}

static const char* BusPath = "/cdm/emulated";

static Array_Channel_ChannelInfoRecord* getChannels(void)
{
    static Array_Channel_ChannelInfoRecord s_channels;

    if (!s_channels.elems) {
        InitArray_Channel_ChannelInfoRecord(&s_channels, 0);
        size_t i = 0;

        i = ExtendArray_Channel_ChannelInfoRecord(&s_channels, 1);
        s_channels.elems[i].channelID = strdup("a");
        s_channels.elems[i].channelNumber = strdup("1");
        s_channels.elems[i].channelName = strdup("Hobbit News");

        i = ExtendArray_Channel_ChannelInfoRecord(&s_channels, 1);
        s_channels.elems[i].channelID = strdup("b");
        s_channels.elems[i].channelNumber = strdup("2");
        s_channels.elems[i].channelName = strdup("Shire Shopping Network");
    }

    return &s_channels;
}



static void CopyChannel_ChannelInfoRecord(Channel_ChannelInfoRecord* value, Channel_ChannelInfoRecord* copy)
{
    copy->channelID = strdup(value->channelID);
    copy->channelNumber = strdup(value->channelNumber);
    copy->channelName = strdup(value->channelName);
}



static AJ_Status GetChannelId(void *context, const char *objPath, char const* *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "Channel", "ChannelId");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "Channel", "ChannelId");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        char const* const value = "";
        HAL_Encode_String(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "Channel", "ChannelId");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    char const* value;
    value = HAL_Decode_String(fp);
    *out = value;
    fclose(fp);
    return result;
}



static AJ_Status SetChannelId(void *context, const char *objPath, char const* input)
{
    AJ_Status result = AJ_OK;
    char const* value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "Channel", "ChannelId");
    HAL_Encode_String(fp, value);
    fclose(fp);
    return result;
}


static AJ_Status GetTotalNumberOfChannels(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "Channel", "TotalNumberOfChannels");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "Channel", "TotalNumberOfChannels");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "Channel", "TotalNumberOfChannels");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}




static AJ_Status MethodGetChannelList(void *context, const char *objPath, uint16_t startingRecord, uint16_t numRecords, Array_Channel_ChannelInfoRecord* listOfChannelInfoRecords)
{
    Array_Channel_ChannelInfoRecord* channels = getChannels();

    InitArray_Channel_ChannelInfoRecord(listOfChannelInfoRecords, 0);

    if (startingRecord >= channels->numElems)
    {
        return AJ_ERR_FAILURE;
    }

    for (size_t i = startingRecord; i < startingRecord + numRecords && i < channels->numElems; ++i)
    {
        size_t j = ExtendArray_Channel_ChannelInfoRecord(listOfChannelInfoRecords, 1);
        listOfChannelInfoRecords->elems[j] = channels->elems[i];
        CopyChannel_ChannelInfoRecord(&channels->elems[i], &listOfChannelInfoRecords->elems[j]);
    }

    return AJ_OK;
}



static ChannelModel model = {
    GetChannelId
    , SetChannelId
    , GetTotalNumberOfChannels

    , MethodGetChannelList
};


ChannelModel *GetChannelModel(void)
{
    return &model;
}