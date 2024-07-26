# Read/write in files

The framework comes with classes to manage reading and writing in files conveniently.

### File management

A file is represented by the class <code>SlvFile</code>. It contains information about:

- The name of the file . See <code>SlvFile::get_file_name()</code>

- The directory where the file virtually exists (path without file name). See <code>SlvFile::get_directory()</code>

In the example below, a file is opened for writing. For reading, simply replace <code>std::ofstream</code> by <code>std::ifstream</code>.

```cpp
SlvFile file("test-file0.xyz");
std::ofstream file_stream;
// No absolute path provided => opens ./test-file0.xyz
SlvStatus status = SlvFileMgr::open_file(file_stream, file);
if (status) {
    file_stream.close();
}
```

##### Global relative path

A *global* relative path can apply to all file reading and writing:

```cpp
SlvFileMgr::master_relative_path() = "../";
file.set_name("test-file1.xyz");
// No absolute path provided => opens ../test-file0.xyz
status = SlvFileMgr::open_file(file_stream, file);
if (status) {
    file_stream.close();
}
```

###### Remark

In case the file has an absolute path, the global relative path is ignored.

More details and examples can be found in [sample007.cpp](/src/src_samples/src_sample007/sample007.cpp).
