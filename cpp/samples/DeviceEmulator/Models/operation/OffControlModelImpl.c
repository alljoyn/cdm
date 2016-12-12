/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "OffControlModelImpl.h"
#include "../../../Utils/HAL.h"



#include <ajtcl/cdm/interfaces/operation/OnOffStatusInterface.h>

static const char* s_objPath = "/cdm/emulated";





static AJ_Status MethodSwitchOff(void *context, const char *objPath)
{
    bool value = false;

    FILE* fp = HAL_WriteProperty(s_objPath, "OnOffStatus", "IsOn");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    HAL_Encode_Int(fp, value);
    fclose(fp);

    OffControlModel* model = (OffControlModel*)context;
    Cdm_OnOffStatus_EmitIsOnChanged(model->busAttachment, s_objPath, value);

    return AJ_OK;
}



static OffControlModel model = {

    MethodSwitchOff
};


OffControlModel *GetOffControlModel(void)
{
    return &model;
}
