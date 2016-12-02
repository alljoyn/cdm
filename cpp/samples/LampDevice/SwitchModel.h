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

#ifndef ALLJOYN_SWITCHMODEL_H
#define ALLJOYN_SWITCHMODEL_H

#include <interfaces/controllee/operation/OnOffStatusIntfControlleeModel.h>
#include <interfaces/controllee/operation/OnControlIntfControlleeModel.h>
#include <interfaces/controllee/operation/OffControlIntfControlleeModel.h>

class SwitchModel final :
    public ajn::services::OnOffStatusIntfControlleeModel,
    public ajn::services::OnControlIntfControlleeModel,
    public ajn::services::OffControlIntfControlleeModel
{
 public:
    SwitchModel(const std::string& busPath);

    // From OnOffStatus interface
    QStatus GetIsOn(bool& out) const override;

    // From OnControl interface
    QStatus SwitchOn(ajn::services::ErrorCode& error, ajn::services::CdmSideEffects& sideEffects) override;

    // From OffControl interface
    QStatus SwitchOff(ajn::services::ErrorCode& error, ajn::services::CdmSideEffects& sideEffects) override;
 private:
    std::string m_busPath;
};


#endif //ALLJOYN_SWITCHMODEL_H
