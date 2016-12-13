/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/


#ifndef ALLJOYN_BSXML_H
#define ALLJOYN_BSXML_H


#include <qcc/platform.h>

#include <alljoyn/Status.h>

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

namespace ajn {
namespace services {
namespace xml {

struct Context;

/**
 * This is not a full-blown XML parser/generator and performs no DTD validation
 * or other advanced features.
 */
class Element {
  public:

    /**
     * Retrieves the root of the XML in form of a Element.
     *
     * @param[in]     xml     Input XML.
     * @param[out]    root    XML root, null if call failed.
     *                        Must be freed by calling "delete".
     * @return    ER_OK if parse was successful.
     *            ER_WOULDBLOCK if parse is partially completed pending more I/O.
     *            Otherwise error.
     */
    static QStatus AJ_CALL GetRoot(AJ_PCSTR xml, Element **root);

    /**
     * Create an Element from an XML document fragment.
     * It is the responsibility of the caller to free the pointer returned in root.
     *
     * @param ctx    Parsing context (see {@link #Context})
     * @return    ER_OK if parse was successful,
     *            ER_WOULDBLOCK if parse is partially completed pending more I/O,
     *            Otherwise error
     */
    static QStatus AJ_CALL Parse(Context &ctx);

    /**
     * Construct an Element with a given name and parent.
     *
     * @param name     XML element name.
     * @param parent   Parent element or NULL if this element is the root.
     * @param parentOwned  When the parent elements memory is freed it will free
     *                     this this element
     */
    Element(const std::string &name = "", Element *parent = NULL, bool parentOwned = false);

    /** Destructor */
    ~Element();

    /**
     * Output an XML fragment of this Element including any childeren.
     *
     * @param outStr  Optional string to be used for output. (Defaults to empty string.)
     * @return  XML Fragment
     */
    std::string Generate(std::string *outStr = nullptr) const;

    /**
     * Get the element name
     *
     * @return XML element name or empty string if not set.
     */
    const std::string &GetName() const { return name; }

    /**
     * Get this element's parent or NULL if none exists.
     *
     * @return XML parent or NULL.
     */
    Element *GetParent() const { return parent; }

    /**
     * Set the element name.
     *
     * @param elementName    Name of XML element.`
     */
    void SetName(const std::string &elementName) { this->name = elementName; }

    /**
     * Get the attributes for this element.
     * @return  Map of attribute name/value pairs
     */
    const std::map<std::string, std::string> &GetAttributes() const { return attributes; }

    /**
     * Get an attribute with a given name or empty string if it doesn't exist.
     *
     * @param attName   Name of attribute
     */
    const std::string &GetAttribute(const char *attName) const;

    /**
     * Get an attribute with a given name or empty string if it doesn't exist.
     *
     * @param attName   Name of attribute
     */
    const std::string &GetAttribute(const std::string &attName) const;

    /**
     * Add an Xml Attribute
     *
     * @param attributeName    Attribute name.
     * @param value            Attribute value.
     */
    void AddAttribute(const std::string &attributeName,
                      const std::string &value) { attributes[attributeName] = value; }

    /**
     * Add a child element. The parent will take over memory managment for the child.
     *
     * @param child  The child Element.
     */
    void AddChild(Element *child);

    /**
     * Get the element map.
     */
    const std::vector<Element *> &GetChildren() const { return children; }

    /**
     * Get all children with a given name.
     *
     * Only return direct children. This method will not do a recursive search
     * of the child nodes.
     *
     * @param name   XML child elements name to search for.
     * @return  A vector containing the matching elements.
     */
    std::vector<const Element *> GetChildren(const std::string &name) const;

    /**
     * Get the child element with a given name if it exists.
     *
     * @param name   XML child element name to search for.
     * @return  Pointer to XML child element or NULL if not found.
     */
    const Element *GetChild(const std::string &name) const;

    /**
     * Add a child Element.
     *
     * @param name   Child node name.
     */
    Element *CreateChild(const std::string &name);

    /**
     * Get the content.
     */
    const std::string &GetContent() const { return content; }

    /**
     * Set the (unesacped) text content.
     *
     * @param  newContent    Unescaped ("&" not "&amp;") text content for this node.
     */
    void SetContent(const std::string &newContent) { this->content = newContent; }

    /**
     * Add text content to this node.
     * An Element can only have content or children. Not both. If content is added
     * to an Element that has children, the text content will be silently ignored.
     *
     * @param newContent   Text content to add to this node.
     */
    void AddContent(const std::string &newContent) { this->content.append(newContent); }

    /**
     * Get all elements that have the specified path relative to the current element. The path is a
     * series of tag names separated by '/' with an optional attribute specified by an '@' character
     * followed by the attribute name.
     *
     * Given the XML below GetPath("foo/bar/value@first") will return the <value> element
     * containing "hello" and GetPath("foo/bar/value@second") will return the <value> element
     * containing "world". GetPath("foo/bar/value") will return both <value> elements.
     *
     * <foo>
     *    <bar>
     *       <value first="hello"/>
     *       <value second="world"/>
     *    </bar>
     * </foo>
     *
     * @param key   The key is a dotted path (with optional attribute) to a value in the XML
     *
     * @param path   The path to elements in the XML tree.
     */
    std::vector<const Element *> GetPath(const std::string &path) const;

    /**
     * Utility function to escape text for use in XML
     *
     * @param str The unescaped string
     * @return The escaped string
     */
    static std::string AJ_CALL EscapeXml(const std::string &str);

    /**
     * Utility function to unescape text from XML
     *
     * @param str The escaped string
     * @return The unescaped string
     */
    static std::string AJ_CALL UnescapeXml(const std::string &str);

  private:
    std::string name;                                /**< Element name */
    std::vector<Element *> children;               /**< XML child elements */
    std::map<std::string, std::string> attributes;   /**< XML attributes */
    std::string content;                             /**< XML text content (unesacped) */
    Element *parent;                              /**< XML parent element or NULL if root */
    bool parentOwned;                                /**< XML parent responsible for freeing this xml element */

    /**
     * Helper used during parsing.
     * @param ctx  Parsing context.
     */
    static void FinalizeElement(Context &ctx);
};

/**
 * Context contains XML parsing state.
 */
struct Context {
    friend class Element;

  public:
    /**
     * Create a parse context that uses a given XML source.
     *
     * @param source  std::stringstream containing XML formatted data.
     */
    Context(std::stringstream &source) :
            source(source),
            parseState(IN_ELEMENT),
            root(new Element()),
            curElem(NULL),
            attrInQuote(false),
            isEndTag(false),
            isDoctype(false),
            foundHyphen(false),
            isCommentDelim(false),
            shouldIgnore(false),
            isTextDecleration(false),
            foundTxtDeclDelim(false) {}

    /** Reset state of Context in preparation for reuse */
    void Reset();

    /**
     * Detach the current root and return it. It is the responsiblity of the caller
     * to free the root when no longer needed.
     */
    Element *DetachRoot() {
        Element *xml = root;
        root = NULL;
        Reset();
        return xml;
    }

    /**
     * Return a const pointer to the current root. The root will become invalid when the context is
     * freed.
     */
    const Element *GetRoot() const {
        return root;
    }

    /**
     * Destructor
     */
    ~Context() {
        delete root;
    }

  private:

    /*
     * Default constructor not defined
     */
    Context();

    /*
     * Copy constructor not defined
     */
    Context(const Context &other);

    /*
     * Assignment operator not defined
     */
    Context &operator=(const Context &other);

    /** Xml source */
    std::stringstream &source;

    /** Parse state */
    enum {
        IN_ELEMENT,
        IN_ELEMENT_START,
        IN_ATTR_NAME,
        IN_ATTR_VALUE,
        IN_SKIP,
        IN_SKIP_START,
        PARSE_COMPLETE
    } parseState;

    Element *root;         /**< Parsed root element */
    Element *curElem;      /**< XML element currently being parsed */
    std::string rawContent;   /**< Text content for current element */
    std::string elemName;     /**< Name of current element */
    std::string attrName;     /**< Name of attribute currently being parsed. */
    std::string attrValue;    /**< Value of attribute currently being parsed. */
    std::string doctypeStr;
    bool attrInQuote;         /**< true iff inside attribute value quotes */
    char quoteChar;           /**< a " or ' character used for quote matching of an attribute */
    bool isEndTag;            /**< true iff currently parsed tag is an end tag */
    bool isDoctype;           /**< true iff currently parsed tag is a doctype tag */
    bool foundHyphen;         /**< true iff a hyphen was found during the current pass */
    bool isCommentDelim;      /**< true iff a comment tag delimeter (--) was found */
    bool shouldIgnore;        /**< true iff currently parsed tag is a comment */
    bool isTextDecleration;   /**< true iff currently parsed tag is a text decleration tag (<?) */
    bool foundTxtDeclDelim;   /**< true iff a question mark was found during the current pass */
};

}
}
}


#endif //ALLJOYN_BSXML_H