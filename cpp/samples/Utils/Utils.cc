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

#include <errno.h>
#include <sys/stat.h>
#include <iostream>
#include <cctype>

#if defined(QCC_OS_GROUP_WINDOWS)
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#else
#include <sys/utsname.h>
#endif

#include "Utils.h"
using namespace std;

namespace ajn {
namespace services {
namespace utils {
//======================================================================

static const char PathDelim = '/';



QStatus MkDirPath(const string& path, char delim, int mode)
{
    string piece;
    vector<string> parts = SplitFields(path, delim);

    for (auto& p : parts)
    {
        piece += p;
        piece += PathDelim;

        int err = mkdir(piece.c_str(), 0777);

        if (!(err == 0 || errno == EEXIST))
        {
            cerr << "Cannot create the directory " << piece << "\n";
            return ER_FAIL;
        }
    }

    return ER_OK;
}


std::string GetHostName()
{
    std::string host;
#if defined(QCC_OS_GROUP_WINDOWS)
#else
    utsname uts;
    if (uname(&uts) == 0)
    {
        host = uts.nodename;
    }
#endif
    return host;
}



vector<string> SplitFields(const string& text, char delim)
{
    vector<string> fields;
    size_t start = 0;
    size_t len   = text.size();

    while (start < len)
    {
        while (start < len && text[start] == delim)
        {
            ++start;
        }

        // Find the end
        size_t end = start;

        while (end < len && text[end] != delim)
        {
            ++end;
        }

        if (end > start)
        {
            fields.push_back(text.substr(start, end - start));
        }

        start = end;
    }

    return fields;
}



vector<string> SplitWords(const string& text)
{
    vector<string> words;
    size_t start = 0;
    size_t len   = text.size();

    while (start < len)
    {
        while (start < len && std::isspace(text[start]))
        {
            ++start;
        }

        // Find the end
        size_t end = start;

        while (end < len && !std::isspace(text[end]))
        {
            ++end;
        }

        if (end > start)
        {
            words.push_back(text.substr(start, end - start));
        }

        start = end;
    }

    return words;
}

//======================================================================
} // namespace utils
} // namespace services
} // namespace ajn
