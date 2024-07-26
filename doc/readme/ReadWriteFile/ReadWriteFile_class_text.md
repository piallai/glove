# Read/write in files

### Text file

Inheriting from *SlvIOFS* provides an implementation of the insertion and extraction operators (<< and >>) which requires methods *ofstream* and *ifstream* to be implemented.

The mechanism is different from the example presented in [input output](/doc/readme/ReadWriteFile/ReadWriteFile_class_IO.md). This time the streams are specialized for *std::ifstream* and *std::ofstream*.

```cpp
class ClassA : public SlvIOFS {

private:

    float value1 = 20;
    std::string value2 = "foo";

public:

    ClassA() {}

    void ifstream(std::ifstream& _is) {
        _is.seekg(std::string("value1 : ").size(), std::ios_base::cur);
        _is >> value1;
        _is.seekg(std::string(" ; value2 : ").size(), std::ios_base::cur);
        _is >> value2;
    }

    void ofstream(std::ofstream& _os) const {
        _os << "value1 : " << value1 << " ; value2 : " << value2 << std::endl;
    }

};
```

To write and read the instance:

```cpp
ClassA classA;
SlvFileMgr::write_text(classA, "classA.txt");// use std::ofstream& operator<< and default ClassA::ofstream
SlvFileMgr::read_text(classA, "classA.txt");// use std::ifstream& operator>> and default ClassA::ifstream
```

The instance is written/read to the file. Then the file is closed. *i.e.* the file only contains `classA` output.

More details can be found in [sample007_3.cpp](/src/src_samples/src_sample007_3/sample007_3.cpp).
