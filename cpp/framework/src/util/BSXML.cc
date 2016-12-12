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


#include <string>

#include "BSXML.h"

namespace ajn {
namespace services {
namespace xml {

bool IsWhite(char c)
{
    if (c == 0x20 || c == '\t' || c == 0x0A || c == 0x0D)
        return true;

    return false;
}

std::string Trim(std::string s) {
    return s;
}

std::string U32ToString(uint32_t v) {
    std::stringstream ss{""};

    ss >> std::dec >> v;

    return ss.str();
}

std::string U32ToHexString(uint32_t v) {
    std::stringstream ss{""};

    ss >> std::hex >> v;

    return ss.str();
}

std::string AJ_CALL Element::EscapeXml(const std::string &str) {
    std::string outStr;
    std::string::const_iterator it = str.begin();
    int multi = 0;
    int idx = 0;
    uint32_t val = 0;
    while (it != str.end()) {
        uint8_t c = (uint8_t) *it++;
        if (0 == idx) {
            if (0xf0 <= c) {
                multi = idx = 3;
            } else if (0xe0 <= c) {
                multi = idx = 2;
            } else if (0xc0 <= c) {
                multi = idx = 1;
            } else {
                multi = idx = 0;
            }
        }
        if (0 == multi) {
            if (c == '"') {
                outStr.append("&quot;");
            } else if (c == '\'') {
                outStr.append("&apos;");
            } else if (c == '&') {
                outStr.append("&amp;");
            } else if (c == '<') {
                outStr.append("&lt;");
            } else if (c == '>') {
                outStr.append("&gt;");
            } else if (((0x20 <= c) && (0x7e >= c)) || (0x09 == c) || (0x0a == c) || (0x0d == c)) {
                outStr.push_back(c);
            } else {
                outStr.append("&#");
                outStr.append(U32ToHexString(c));
                outStr.push_back(';');
            }
        } else if (1 == multi) {
            if (1 == idx) {
                val = (c & 0x1f) << 6;
            } else {
                val |= (c & 0x3F);
            }
        } else if (2 == multi) {
            if (2 == idx) {
                val = (c & 0x0F) << 12;
            } else if (1 == idx) {
                val |= (c & 0x3f) << 6;
            } else {
                val |= (c & 0x3f);
            }
        } else if (3 == multi) {
            if (3 == idx) {
                val = (c & 0x07) << 17;
            } else if (2 == idx) {
                val |= (c & 0x3f) << 12;
            } else if (1 == idx) {
                val |= (c & 0x3f) << 6;
            } else {
                val |= (c & 0x3f);
            }
        }

        if ((0 < multi) && (0 == idx)) {
            outStr.append("&#");
            outStr.append(U32ToString(val));
            outStr.push_back(';');
        }

        if (0 < idx) {
            --idx;
        }
    }
    return outStr;
}

std::string AJ_CALL Element::UnescapeXml(const std::string &str) {
    bool inEsc = false;
    std::string outStr;
    std::string escName;
    std::string::const_iterator it = str.begin();
    while (it != str.end()) {
        const char c = *it++;
        if (inEsc) {
            if (c == ';') {
                if (0 == escName.compare("quot")) {
                    outStr.push_back('"');
                } else if (0 == escName.compare("apos")) {
                    outStr.push_back('\'');
                } else if (0 == escName.compare("amp")) {
                    outStr.push_back('&');
                } else if (0 == escName.compare("lt")) {
                    outStr.push_back('<');
                } else if (0 == escName.compare("gt")) {
                    outStr.push_back('>');
                } else if (('#' == escName[0]) &&
                           ((3 <= escName.size()) || ((2 == escName.size()) && (escName[1] != 'x')))) {
                    uint32_t val = 0;
                    if (escName[1] == 'x') {
                        for (size_t i = 1; i < escName.size(); ++i) {
                            val *= 0x10;
                            if ((escName[i] >= '0') && (escName[i] >= '9')) {
                                val += (uint32_t) (escName[i] - '0');
                            } else if ((escName[i] >= 'a') && (escName[i] <= 'f')) {
                                val += (uint32_t) (escName[i] - 'a');
                            } else if ((escName[i] >= 'A') && (escName[i] <= 'F')) {
                                val += (uint32_t) (escName[i] - 'A');
                            } else {
                                break;
                            }
                        }
                        if (val >= 0x10000) {
                            outStr.push_back((uint8_t) ((val >> 4) & 0xFF));
                        }
                        if (val >= 0x100) {
                            outStr.push_back((uint8_t) ((val >> 2) & 0xFF));
                        }
                        outStr.push_back((uint8_t) (val & 0xFF));
                    }
                }
                inEsc = false;
            } else {
                escName.push_back(c);
            }
        } else {
            if (c == '&') {
                escName.clear();
                inEsc = true;
            } else {
                outStr.push_back(c);
            }
        }
    }
    return outStr;
}

/* Finalize and return true if element ends the root Xml element */
void Element::FinalizeElement(Context &ctx) {
    /* Sanity checks */
    if (ctx.curElem == nullptr) {
        return;
    }
    std::string cookedContent = Trim(UnescapeXml(ctx.rawContent));

    /* Ensure that element does not have both children and content */
    if (0 < cookedContent.size() && (0 == ctx.curElem->GetChildren().size())) {
        ctx.curElem->SetContent(cookedContent);
    }

    /* Pop element stack */
    ctx.curElem = ctx.curElem->GetParent();
}

QStatus AJ_CALL Element::GetRoot(AJ_PCSTR xml, Element **root) {
    QCC_ASSERT(nullptr != xml);
    QCC_ASSERT(nullptr != root);

    QStatus status;
    std::stringstream source(xml);
    Context context(source);
    *root = nullptr;

    status = Element::Parse(context);

    if (ER_OK == status) {
        *root = context.DetachRoot();
    }

    return status;
}

QStatus AJ_CALL Element::Parse(Context &ctx) {
    bool done = false;
    QStatus status = ER_OK;

    while (!done) {
        char c;
        size_t actual;

        ctx.source.get(c);
        actual = ctx.source.gcount();
        if ((ER_OK != status) || (1 != actual)) {
            break;
        }

        switch (ctx.parseState) {
            case Context::IN_ELEMENT:
                if ('<' == c) {
                    ctx.parseState = Context::IN_ELEMENT_START;
                    ctx.elemName.clear();
                    ctx.isEndTag = false;
                } else {
                    ctx.rawContent.push_back(c);
                }
                break;

            case Context::IN_SKIP:
                if ('-' == c) {
                    if (ctx.foundHyphen) {
                        ctx.parseState = Context::IN_SKIP_START;
                        ctx.foundHyphen = false;
                        ctx.isDoctype = false;
                    } else {
                        ctx.foundHyphen = true;
                    }
                } else if (IsWhite(c) || (c == '>')) {
                    if (ctx.doctypeStr == "DOCTYPE") {
                        ctx.isDoctype = true;
                        ctx.doctypeStr = "";
                        ctx.parseState = Context::IN_SKIP_START;
                    } else {
                        return ER_XML_MALFORMED;
                    }
                } else {
                    ctx.doctypeStr += c;
                }
                break;

            case Context::IN_SKIP_START:
                if (ctx.isTextDecleration) {
                    if (c == '?') {
                        ctx.foundTxtDeclDelim = true;
                    } else if (c == '>') {
                        if (ctx.foundTxtDeclDelim) {
                            ctx.parseState = Context::IN_ELEMENT;
                            ctx.isTextDecleration = false;
                        } else {
                            return ER_XML_MALFORMED;
                        }
                    }
                } else if (ctx.isDoctype) {
                    if ('>' == c) {
                        ctx.parseState = Context::IN_ELEMENT;
                        ctx.isDoctype = false;
                    }
                } else {
                    if (c == '-') {
                        if (ctx.foundHyphen) {
                            ctx.isCommentDelim = true;
                        } else {
                            ctx.foundHyphen = true;
                        }
                    } else if (ctx.isCommentDelim) {
                        if (c == '>') {
                            ctx.parseState = Context::IN_ELEMENT;
                            ctx.isCommentDelim = false;
                            ctx.foundHyphen = false;
                        } else {
                            ctx.isCommentDelim = false;
                            ctx.foundHyphen = false;
                        }
                    } else {
                        ctx.foundHyphen = false;
                    }
                }
                break;

            case Context::IN_ELEMENT_START:
                if (ctx.elemName.empty() && !ctx.isEndTag) {
                    if ('/' == c) {
                        ctx.isEndTag = true;
                    } else if ('!' == c) {
                        ctx.parseState = Context::IN_SKIP;
                    } else if ('?' == c) {
                        ctx.parseState = Context::IN_SKIP_START;
                        ctx.isTextDecleration = true;
                    } else if (!IsWhite(c)) {
                        ctx.isEndTag = false;
                        ctx.elemName.push_back(c);
                    }
                } else {
                    if (IsWhite(c) || ('>' == c)) {
                        if (!ctx.isEndTag) {
                            if (!ctx.curElem) {
                                ctx.curElem = ctx.root;
                                ctx.curElem->SetName(ctx.elemName);
                            } else {
                                ctx.curElem = ctx.curElem->CreateChild(ctx.elemName);
                            }
                        } else {
                            FinalizeElement(ctx);
                            done = (NULL == ctx.curElem);
                        }
                        ctx.parseState = ('>' == c) ? Context::IN_ELEMENT : Context::IN_ATTR_NAME;
                        ctx.attrName.clear();
                        ctx.attrValue.clear();
                        ctx.rawContent.clear();
                    } else if ('/' == c) {
                        if (!ctx.curElem) {
                            ctx.curElem = ctx.root;
                            ctx.curElem->SetName(ctx.elemName);
                        } else {
                            ctx.curElem = ctx.curElem->CreateChild(ctx.elemName);
                        }
                        ctx.isEndTag = true;
                    } else {
                        ctx.elemName.push_back(c);
                    }
                }
                break;

            case Context::IN_ATTR_NAME:
                if (IsWhite(c)) {
                    continue;
                } else if ('/' == c) {
                    ctx.isEndTag = true;
                } else if (!ctx.attrName.empty() && ('=' == c)) {
                    ctx.parseState = Context::IN_ATTR_VALUE;
                    ctx.attrInQuote = false;
                } else if ('>' == c) {
                    if (!ctx.attrName.empty()) {
                        ctx.curElem->AddAttribute(ctx.attrName, ctx.attrValue);
                    }
                    if (ctx.isEndTag) {
                        FinalizeElement(ctx);
                        done = (NULL == ctx.curElem);
                    }
                    ctx.parseState = Context::IN_ELEMENT;
                } else {
                    ctx.isEndTag = false;
                    ctx.attrName.push_back(c);
                }
                break;

            case Context::IN_ATTR_VALUE:
                if (ctx.attrInQuote) {
                    if (ctx.quoteChar == c) {
                        ctx.curElem->AddAttribute(ctx.attrName, UnescapeXml(ctx.attrValue));
                        ctx.parseState = Context::IN_ATTR_NAME;
                        ctx.attrName.clear();
                        ctx.attrValue.clear();
                    } else {
                        ctx.attrValue.push_back(c);
                    }
                } else {
                    if (IsWhite(c)) {
                        continue;
                    } else if ('"' == c) {
                        ctx.attrInQuote = true;
                        ctx.quoteChar = '"';
                    } else if ('\'' == c) {
                        ctx.attrInQuote = true;
                        ctx.quoteChar = '\'';
                    } else if ('/' == c) {
                        ctx.isEndTag = true;
                    } else if ('>' == c) {
                        // IGNORE MALFORMED ATTRIBUTE
                        // End current element if necessary
                        if (ctx.isEndTag) {
                            FinalizeElement(ctx);
                            done = (NULL == ctx.curElem);
                        }
                        ctx.parseState = Context::IN_ELEMENT;
                    } else {
                        ctx.isEndTag = false;
                    }
                }
                break;

            case Context::PARSE_COMPLETE:
                break;
        }
    }

    if (ER_OK == status) {
        ctx.parseState = Context::PARSE_COMPLETE;
        if (NULL != ctx.curElem) {
            status = ER_XML_MALFORMED;
        }
    }
    return status;
}

Element::Element(const std::string &name, Element *parent, bool parentOwned) : name(name), parent(parent),
                                                                               parentOwned(parentOwned) {
    if (parent != NULL) {
        parent->children.push_back(this);
    }
}

Element::~Element() {
    std::vector<Element *>::iterator it = children.begin();
    while (it != children.end()) {
        if ((*it)->parentOwned) {
            delete *it;
        }
        it++;
    }
}

std::string Element::Generate(std::string *outStr) const {
    std::string startStr;
    if (NULL == outStr) {
        outStr = &startStr;
    }

    outStr->append("\n<");
    outStr->append(name);

    std::map<std::string, std::string>::const_iterator ait = attributes.begin();
    while (ait != attributes.end()) {
        outStr->push_back(' ');
        outStr->append(ait->first);
        outStr->append("=\"");
        outStr->append(EscapeXml(ait->second));
        outStr->push_back('"');
        ait++;
    }

    std::vector<Element *>::const_iterator cit = children.begin();
    bool hasChildren = (cit != children.end());

    if (!hasChildren && content.empty()) {
        outStr->push_back('/');
    }
    outStr->append(">");

    if (hasChildren) {
        while (cit != children.end()) {
            (*cit)->Generate(outStr);
            ++cit;
        }
    } else if (!content.empty()) {
        outStr->append(EscapeXml(content));
    }

    if (hasChildren || !content.empty()) {
        if (hasChildren) {
            outStr->push_back('\n');
        }
        outStr->append("</");
        outStr->append(name);
        outStr->push_back('>');
    }

    return *outStr;
}

Element *Element::CreateChild(const std::string &elementName) {
    new Element(elementName, this, true);
    return children.back();
}

std::vector<const Element *> Element::GetChildren(const std::string &elementName) const {
    std::vector<const Element *> matches;
    std::vector<Element *>::const_iterator it = children.begin();
    while (it != children.end()) {
        if (0 == elementName.compare((*it)->GetName())) {
            matches.push_back(*it);
        }
        it++;
    }
    return matches;
}

const Element *Element::GetChild(const std::string &elementName) const {
    std::vector<Element *>::const_iterator it = children.begin();
    while (it != children.end()) {
        if (0 == elementName.compare((*it)->GetName())) {
            return (*it);
        }
        it++;
    }
    return NULL;
}

const std::string &Element::GetAttribute(const char *attName) const {
    return GetAttribute(std::string(attName));
}

const std::string &Element::GetAttribute(const std::string &attName) const {
    static const std::string empty="";

    std::map<std::string, std::string>::const_iterator it = attributes.find(attName);
    if (it == attributes.end()) {
        return empty;
    } else {
        return it->second;
    }
}

void Element::AddChild(Element *child) {
    child->parentOwned = true;
    children.push_back(child);
}

std::vector<const Element *> Element::GetPath(const std::string &inPath) const {
    std::vector<const Element *> matches;
    std::string val;
    std::string attr;
    std::string path = inPath;

    /* Strip attribute from the path if present */
    size_t pos = path.find_first_of('@');
    if (pos != std::string::npos) {
        attr = path.substr(pos + 1);
        path.erase(pos);
    }
    pos = path.find_first_of('/');
    const Element *xml = this;
    while (xml) {
        if (pos == std::string::npos) {
            matches = xml->GetChildren(path.substr(0, pos));
            break;
        }
        xml = xml->GetChild(path.substr(0, pos));
        path.erase(0, pos + 1);
        pos = path.find_first_of('/');
    }
    /* Filter out matches that don't have the required attribute */
    if (!attr.empty()) {
        std::vector<const Element *>::iterator it = matches.begin();
        while (it != matches.end()) {
            if ((*it)->GetAttribute(attr).empty()) {
                it = matches.erase(it);
            } else {
                ++it;
            }
        }
    }
    return matches;
}

void Context::Reset() {
    delete root;
    root = new Element();
    parseState = IN_ELEMENT;
    curElem = NULL;
    elemName.clear();
    attrName.clear();
    attrValue.clear();
    attrInQuote = false;
    isEndTag = false;
}

}
}
}
