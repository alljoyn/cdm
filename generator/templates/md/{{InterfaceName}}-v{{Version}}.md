# {{FullInterfaceName}} version {{Version}}

## Theory of Operation

TODO

## Specification

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Version               | {{version}}                                                           |
| Annotation            | org.alljoyn.Bus.Secure = true                                         |


### Properties

{{#properties}}
#### {{PropertyName}}

|                       |                                                                       |
|-----------------------|-----------------------------------------------------------------------|
| Type                  | {{PropertyType.ajtype}}                                               |
| Access                | {{property_access}}                                                   |
{{#annotations}}
| Annotation            | {{*70                                                               }}|
{{/annotations}}
| Introduced in version | TODO n (only add this line for n > 1)                                 |

TODO: Text describing the property

{{/properties}}
{{^properties}}
No properties are exposed by this interface.
{{/properties}}

### Methods

{{#methods}}
#### {{MethodName}}(in1) -> (out1)

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
 
{{/methods}}
{{^methods}}
No methods are exposed by this interface.
{{/methods}}

### Signals

{{#signals}}
{{/signals}}
{{^signals}}
No signals are emitted by this interface.
{{/signals}}