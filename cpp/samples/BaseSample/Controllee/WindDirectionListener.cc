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

#include <iostream>
#include "WindDirectionListener.h"

using namespace std;

QStatus WindDirectionListener::OnSetHorizontalDirection(const uint16_t& value)
{
    cout << "WindDirectionListener::OnSetHorizontalDirection() - HorizontalDirection : " << value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetHorizontalDirection(uint16_t& value)
{
    cout << "WindDirectionListener::OnGetHorizontalDirection() - HorizontalDirection : " << value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetHorizontalMax(uint16_t& value)
{
    cout << "WindDirectionListener::OnGetHorizontalMax() - HorizontalMax : " << value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnSetHorizontalAutoMode(const uint8_t& value)
{
    cout << "WindDirectionListener::OnSetHorizontalAutoMode() - HorizontalAutoMode : " << (int)value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetHorizontalAutoMode(uint8_t& value)
{
    cout << "WindDirectionListener::OnGetHorizontalAutoMode()" << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnSetVerticalDirection(const uint16_t& value)
{
    cout << "WindDirectionListener::OnSetVerticalDirection() - VerticalDirection : " << value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetVerticalDirection(uint16_t& value)
{
    cout << "WindDirectionListener::OnGetVerticalDirection() - VerticalDirection : " << (int)value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetVerticalMax(uint16_t& value)
{
    cout << "WindDirectionListener::OnGetVerticalMax() - VerticalMax : " << value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnSetVerticalAutoMode(const uint8_t& value)
{
    cout << "WindDirectionListener::OnSetVerticalAutoMode() - VerticalAutoMode : " << (int)value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetVerticalAutoMode(uint8_t& value)
{
    cout << "WindDirectionListener::OnGetVerticalAutoMode()" << endl;
    return ER_OK;
}


