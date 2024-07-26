# [SlvDataName](/src/src_sleeve/misc/SlvDataName.h)

The structure is in charge of providing the static name of a type (*std::string*). See the examples below.

```cpp
std::cout << SlvDataName<int>::name() << std::endl;//Output: "int"
std::cout << SlvDataName< std::vector<std::string> >::name() << std::endl;//Output: "std::vector<std::string>"
```

#### Use typeid().name()

The default behaviour if no specialization exists is to use <code>typeid(T).name()</code>. Caution in this case, the name may differ depending on the compiler.

```cpp
struct Foo {};
```

```cpp
std::cout << SlvDataName<Foo>::name() << std::endl;//Output: "struct Foo"
```

For safety, it is rather recommended to use one of the following methods.

#### Use type static name

If the type <code>T</code> has the method <code>static std::string name()</code>implemented, then the method is used:

```cpp
struct Foo {
    static std::string name() {
        return "Foo";
    }
};
```

```cpp
std::cout << SlvDataName<Foo>::name() << std::endl;//Output: "Foo"
```

#### Use structure specialization

It is also possible to specialize the structure directly. The following specializations are available below. The bold lines correspond to specialization that are included by default in [SlvDataName](/src/src_sleeve/misc/SlvDataName.h).

| Type                       | Header                                                                                                 | Name                    |
| -------------------------- | ------------------------------------------------------------------------------------------------------ | ----------------------- |
| **int**                    | [SlvDataName_spec_AT.h](/src/src_sleeve/misc/spec/SlvDataName_spec_AT.h)                               | *int*                   |
| **unsigned int**           | [SlvDataName_spec_AT.h](/src/src_sleeve/misc/spec/SlvDataName_spec_AT.h)                               | *uint*                  |
| **float**                  | [SlvDataName_spec_AT.h](/src/src_sleeve/misc/spec/SlvDataName_spec_AT.h)                               | *float*                 |
| **double**                 | [SlvDataName_spec_AT.h](/src/src_sleeve/misc/spec/SlvDataName_spec_AT.h)                               | *double*                |
| **bool**                   | [SlvDataName_spec_AT.h](/src/src_sleeve/misc/spec/SlvDataName_spec_AT.h)                               | *bool*                  |
| **std::string**            | [SlvDataName_spec_std_string.h](/src/src_sleeve/misc/spec/SlvDataName_spec_std_string.h)               | *std::string*           |
| **std::vector**            | [SlvDataName_spec_std_vector.h](/src/src_sleeve/misc/spec/SlvDataName_spec_std_vector.h)               | *std::vector< >*        |
| std::vector\<std::vector\> | [SlvDataName_spec_std_vector_vector.h](/src/src_sleeve/misc/spec/SlvDataName_spec_std_vector_vector.h) | *matrix< >*             |
| std::array                 | [SlvDataName_spec_std_array.h](/src/src_sleeve/misc/spec/SlvDataName_spec_std_array.h)                 | *array< , N>*           |
| std::list                  | [SlvDataName_spec_std_list.h](/src/src_sleeve/misc/spec/SlvDataName_spec_std_list.h)                   | *list< >*               |
| std::deque                 | [SlvDataName_spec_std_deque.h](/src/src_sleeve/misc/spec/SlvDataName_spec_std_deque.h)                 | *deque< >*              |
| std::pair                  | [SlvDataName_spec_std_pair.h](/src/src_sleeve/misc/spec/SlvDataName_spec_std_pair.h)                   | *std::pair< , >*        |
| std::map                   | [SlvDataName_spec_std_map.h](/src/src_sleeve/misc/spec/SlvDataName_spec_std_map.h)                     | *std::map< , >*           |
| std::unordered_map         | [SlvDataName_spec_std_unordered_map.h](/src/src_sleeve/misc/spec/SlvDataName_spec_unordered_map.h)     | *std::unordered_map< >* |
| SlvPool                    | [SlvDataName_spec_SlvPool.h](/src/src_sleeve/misc/spec/SlvDataName_spec_SlvPool.h)                     | *SlvPool< >*            |
| All                        | [SlvDataName_spec_All.h](/src/src_sleeve/misc/spec/SlvDataName_spec_All.h)                             |                         |
