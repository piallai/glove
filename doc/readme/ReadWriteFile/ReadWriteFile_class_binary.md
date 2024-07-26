# Read/write in files

### Binary file

For binary reading and writing to files, the type must either have the following methods implemented:

- <code>bool readB(std::ifstream& _input_file)</code>

- <code>void writeB(std::ofstream& _output_file) const</code>

or have the following template functions specialized;

- <code>template <class T> 
  bool slv::rw::readB(T& _value, std::ifstream& _input_file);</code>

- <code>template <class T>
  void slv::rw::writeB(const T& _value, std::ofstream& _output_file);</code>

Specializations for common types and containers are provided at [this page](/doc/readme/ReadWriteFile/ReadWriteFile_specs.md).

```cpp
class ClassA {

private:

    float value1 = 20;
    std::string value2 = "foo";

public:

    ClassA() {}

    bool readB(std::ifstream& _input_file) {
        bool l_read = slv::rw::readB(value1, _input_file);
        if (l_read) l_read = slv::rw::readB(value2, _input_file);
        return l_read;
    }

    void writeB(std::ofstream& _output_file) const {
        slv::rw::writeB(value1, _output_file);
        slv::rw::writeB(value2, _output_file);
    }

};
```

To write and read the instance:

```cpp
ClassA classA;
SlvFileMgr::write_binary(classA, "classA");//write to file ./classA
SlvFileMgr::read_binary(classA, "classA");//read from file ./classA
```

The instance is written/read to the file. Then the file is closed. *i.e.* the file only contains <code>classA</code> output.

More details can be found in [sample007_0.cpp](/src/src_samples/src_sample007_0/sample007_0.cpp).

##### Remark

The <code>read</code> and <code>write</code> methods being public, they can be called to provide instance read/write independently from file opening/closing. See [this example](/doc/readme/ReadWriteFile/ReadWriteFile_class_binary2.md).
