# Read/write in files

### Input/output

Inheriting from *SlvIOS* provides an implementation of the insertion and extraction operators (<< and >>) which requires methods *ostream* and *istream* to be implemented.

```cpp
class ClassA : public SlvIOS {

private:

    float value1 = 20;
    std::string value2 = "foo";

public:

    ClassA() {}

    // Implement istream pure virtual method for reading from operator >>
    void istream(std::istream& _is) {
        std::cout << "Enter value1 : ";
        _is >> value1;
        std::cout << "Enter value2 : ";
        _is >> value2;
    }

    // Implement ostream pure virtual method for output with operator <<
    void ostream(std::ostream& _os) const {
        _os << "value1 : " << value1 << " ; value2 : " << value2 << std::endl;
    }

};
```

To apply <code>std::cin</code> and <code>std::cout</code> to an instance of <code>ClassA</code>:

```cpp
ClassA classA;
std::cin >> classA;
std::cout << classA << std::endl;
```

More details can be found in [sample007_1.cpp](/src/src_samples/src_sample007_1/sample007_1.cpp).

##### Remark

The insertion and extraction operators (<< and >>) can be used to write and read to text files (see [sample007_2.cpp](/src/src_samples/src_sample007_2/sample007_2.cpp)) :

```cpp
ClassA classA;
SlvFileMgr::write_text(classA, "classA.txt");// use std::ostream& operator<< and default ClassA::ostream
SlvFileMgr::read_text(classA, "classA.txt");// use std::istream& operator>> and default ClassA::istream => not adequate
```

However, the extraction operator >> is not suited for extraction from a file since the stream is managed in a different way.

For a proper management of text files, see [this example](/doc/readme/ReadWriteFile/ReadWriteFile_class_text.md).
