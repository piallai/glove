# Enum

The framework introduces a custom <code>enum</code> managing the associated static name (<code>std::string</code>) for each enumerator.

```cpp
#include "SlvEnum.h"
glvm_SlvEnum_named(Color, red, "red", green, "green", blue, "blue")
```

Alternatively, the <code>enum</code> declaration is possible without specifying the name of the enumerators. In this case, the name will be the same as the declared name.

```cpp
glvm_SlvEnum(Color, red, green, blue)
```

Each name of the <code>enum</code> is accessible through the method <code>SlvEnum\<Color>::get_name(Color)</code>.

The preprocessor macro defines the <code>std::ostream</code>, <code>std::istream</code>, <code>slv::rw::write</code> and <code>slv::rw::read</code> functions to make the <code>enum</code> compliant with the whole Glove framework. For read/write functions, the enumerators are casted to <code>int</code>.

### Encapsulation

For an <code>enum</code> encapsulated into a <code>struct</code>, <code>class</code>, or <code>namespace</code>, the macros above do not apply. It is necessary to implement the specializations in a global context.

```cpp
namespace Foo {
    enum class Color {red, green, blue};
}

#include "SlvEnum.h"
glvm_SlvEnum_implementation(Color, red, green, blue)//inline implementation
//Or: glvm_SlvEnum_named_implementation(Color, red, "red", green, "green", blue, "blue")
```

##### Remark

The maximum number of elements of enum is 99 when using the macros. The maximum is 62 for MSVC compiler. To enable a maximum of 99 for MSVC, <code>/Zc:preprocessor</code> compile option must be set.
