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

#ifndef ALLJOYN_ROBOTCLEANINGCYCLEPHASE_MODELIMPL_H
#define ALLJOYN_ROBOTCLEANINGCYCLEPHASE_MODELIMPL_H

#include <stdio.h>

#include <ajtcl/cdm/interfaces/operation/RobotCleaningCyclePhaseModel.h>
#include <ajtcl/cdm/interfaces/operation/RobotCleaningCyclePhaseInterface.h>

RobotCleaningCyclePhaseModel *GetRobotCleaningCyclePhaseModel(void);

// REVISIT delete this
extern int Encoder_RobotCleaningCyclePhase_CyclePhaseDescriptor(FILE* fp, void* value);

#endif // ALLJOYN_ROBOTCLEANINGCYCLEPHASE_MODELIMPL_H
