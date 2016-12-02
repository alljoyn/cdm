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

#include <signal.h>
#include <map>
#include <functional>
#include <iostream>

namespace InterruptHandler {

std::map<int, std::function<void()>> handlers;

void handlerRouter(int interrupt) {
    if (handlers.count(interrupt) > 0)
        handlers[interrupt]();
    else
        std::cout<<"No handler for interrupt "<<interrupt<<"."<<std::endl;
}

bool addHandler(int interrupt, std::function<void()> handler) {
    if (signal(interrupt, handlerRouter) == SIG_ERR)
        return false;

    handlers[interrupt] = handler;
    return true;
}

} // namespace InterruptHandler