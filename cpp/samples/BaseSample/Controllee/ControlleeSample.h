/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#ifndef CONTROLLEESAMPLE_H_
#define CONTROLLEESAMPLE_H_

#include <string>
#include <alljoyn/Session.h>
#include <alljoyn/SessionPortListener.h>
#include <alljoyn/AboutObj.h>
#include <alljoyn/AboutObjectDescription.h>
#include <alljoyn/hae/HaeControllee.h>
#include <alljoyn/hae/HaeAboutData.h>
#include "BaseSample.h"

class Commands;

using namespace std;
using namespace ajn;
using namespace services;

class AboutSessionListener : public SessionPortListener {
  public:
    /**
     * AcceptSessionJoiner - Receive request to join session and decide whether to accept it or not
     * @param sessionPort - the port of the request
     * @param joiner - the name of the joiner
     * @param opts - the session options
     * @return true/false
     */
    virtual bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts) {
        QCC_UNUSED(sessionPort);
        QCC_UNUSED(joiner);
        QCC_UNUSED(opts);
        return true;
    }
};

class ControlleeSample : public BaseSample
{
  public:
    ControlleeSample(BusAttachment* bus, HaeAboutData* aboutData);
    virtual ~ControlleeSample();

    HaeAboutData* GetAboutData() { return m_aboutData; }
    HaeControllee* GetControllee() { return m_controllee; }
    HaeInterface* CreateInterface(const HaeInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener);

  protected:
    virtual void InitSample();
    virtual void CreateInterfaces() = 0;
    virtual void SetInitialProperty() = 0;

    BusAttachment* m_bus;
    HaeAboutData* m_aboutData;
    AboutObj* m_aboutObj;
    AboutSessionListener* m_aboutSessionListener;

    QStatus Init();
    void Deinit();
    QStatus AnnounceAboutObj();
    void UnannounceAboutObj();

    HaeControllee* m_controllee;
    Commands* m_rootCommands;
};


#endif // CONTROLLEESAMPLE_H_
