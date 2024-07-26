# Read/write in files

### Binary file

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

class ClassB {

private:

    ClassA classA;
    std::vector<double> value = {1, 2, 4, 8, 16};

public:

    ClassB() {}

    bool readB(std::ifstream& _input_file) {
        bool l_read = slv::rw::readB(classA, _input_file);
        if (l_read) l_read = slv::rw::readB(value, _input_file);
        return l_read;
    }

    void writeB(std::ofstream& _output_file) const {
        slv::rw::writeB(classA, _output_file);
        slv::rw::writeB(value, _output_file);
    }


};
```

To write and read the instance:

```cpp
 ClassB classB;
 SlvFileMgr::write_binary(classB, "classB");//write to file ./classB
 SlvFileMgr::read_binary(classB, "classB");//read from file ./classB

 // Or 

 SlvFile file("classB");
 std::ofstream output_file_stream;
 SlvStatus status = SlvFileMgr::open_file(output_file_stream, file);
 if (status) {
     classB.writeB(output_file_stream);
     output_file_stream.close();
 }

 std::ifstream input_file_stream;
 status = SlvFileMgr::open_file(input_file_stream, file);
 if (status) {
     classB.readB(input_file_stream);
     input_file_stream.close();
 }
```

More details can be found in [sample007_4.cpp](/src/src_samples/src_sample007_4/sample007_4.cpp).
