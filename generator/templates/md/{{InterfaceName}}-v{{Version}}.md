# {{Interface.FullName}} version {{Interface.Version}}

## Theory of Operation

TODO

## Specification

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Version               | {{Interface.Version                                        | pad(70)}}|
| Annotation            | org.alljoyn.Bus.Secure = true                                         |


### Properties

{% for property in Interface.Properties %}
#### {{property.Name}}

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | {{property.Type.ajtype()                                   | pad(70)}}|
| Access                | {{property.Access                                          | pad(70)}}|
{% for annotation in property.Annotations %}
| Annotation            | {{annotation.Name                                          | pad(70)}}|
{% endfor %}
| Introduced in version | TODO n (only add this line for n > 1)                                 |

TODO: Text describing the property

{% endfor %}
{% if not Interface.Properties %}
No properties are exposed by this interface.
{% endif %}

### Methods

{% for method in Interface.Methods %}
#### {{method.Name}}(in1) -> (out1)

|                       |                                             |
|-----------------------|---------------------------------------------|
| Introduced in version | TODO n (only add this line for n > 1)       |

Description of the method. This may be multi-line.

Input arguments:

  * **in1** --- Frob --- Frob is the kind of dictionary that really deserves a
    thorough discussion when you're using it as an argument to a method. It really
    does. How else would we test multi-line argument descriptions?

Output arguments:

  * **out1** --- float[] --- an array of floating point values

Errors raised by this method:

 * org.alljoyn.example.Foo.Bar.Error.BazNotHome --- with some explanation if needed
 
{% endfor %}
{% if not Interface.Methods %}
No methods are exposed by this interface.
{% endif %}

### Signals

{% for signal in Interface.Signals %}
{% endfor %}
{% if not Interface.Signals %}
No signals are emitted by this interface.
{% endif %}