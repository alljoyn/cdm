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

#ifndef LOCKCONTROLMODEL_H_
#define LOCKCONTROLMODEL_H_

#include <interfaces/controllee/operation/LockControlIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class LockControlModel : public virtual LockControlIntfControlleeModel {
  public:
    LockControlModel(const std::string& busPath);

    /**
     * Handler for method Lock
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    QStatus Lock(ErrorCode& error, CdmSideEffects& sideEffects) override;

  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* LOCKCONTROLMODEL_H_ */