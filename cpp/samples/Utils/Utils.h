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

#ifndef ALLJOYN_CDM_UTILS_H
#define ALLJOYN_CDM_UTILS_H

#include <alljoyn/Status.h>
#include <vector>
#include <string>

namespace ajn {
namespace services {
namespace utils {
//======================================================================
// Miscellaneous utilities

/**
 *  This creates a directory path including the leading components.
 *  All intermediate directories are created with the given mode.
 */
QStatus MkDirPath(const std::string& path, char delim = '/', int mode = 0777);

/**
 *  Split the text at the delimiter.  Consecutive delimiters are treated
 *  as a single one.
 */
std::vector<std::string> SplitFields(const std::string& text, char delim);

/**
 *  Split the text at white space.
 */
std::vector<std::string> SplitWords(const std::string& text);


//======================================================================
} // namespace utils
} // namespace services
} // namespace ajn

#endif // ALLJOYN_CDM_UTILS_H
