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

#ifndef {{Interface.Name.upper()}}INTFCONTROLLEE_H_
#define {{Interface.Name.upper()}}INTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}Interface.h>

namespace ajn {
namespace services {

/**
 * {{Interface.Name}} Interface Controllee class
 */
class {{Interface.Name}}IntfControllee : public {{Interface.Name}}Interface
{
  public:
    /**
     * Constructor of {{Interface.Name}}IntfControllee
     */
    {{Interface.Name}}IntfControllee() {}

    /**
     * Destructor of {{Interface.Name}}IntfControllee
     */
    virtual ~{{Interface.Name}}IntfControllee() {}

    {% for property in Interface.UserProperties %}
    {% if property.EmitsChangedSignal %}
    /**
     * Emits a changed signal for the {{property.Name}} property
     * @param[in] newValue new value of {{property.Name.add_spaces_lower()}}
     * @return ER_OK on success
     */
    virtual QStatus Emit{{property.Name}}Changed(const {{property.Type.ctype()}} newValue) = 0;
    {% endif %}
    {% endfor %}

    {% for method in Interface.Methods %}
    {% for mutator in method.Mutators %}
     /**
     * Emits a signal that the {{mutator.Property}} property from the {{mutator.Interface}} interface has been changed
     * @return ER_OK on success
     */
    virtual QStatus Emit{{mutator.Property}}Changed() = 0;
    {% endfor %}
    {% endfor %}

    {% for signal in Interface.Signals %}
    virtual QStatus Emit{{signal.Name}}() = 0;
    {% endfor %}
};

} //namespace services
} //namespace ajn

#endif /* {{Interface.Name.upper()}}INTFCONTROLLEE_H_ */
