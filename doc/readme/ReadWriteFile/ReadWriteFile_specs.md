# Read/write in files

### Specializations

The following types are specialized for read and write in binary files. The types highlighted in **bold** are the one included by default in the header [filestream/slv_rw.h](/src/src_sleeve/filestream/slv_rw.h).

| Type                                                                                                                                                   | Header                                                                                                                       |
| ------------------------------------------------------------------------------------------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------- |
| **int**<br>**unsigned int**<br>**long unsigned int**<br>**unsigned long long**<br>**float**<br>**double**<br>**bool**<br>**char**<br>**unsigned char** | [filestream/spec/slv_rw_spec_AT.h](/src/src_sleeve/filestream/spec/slv_rw_spec_AT.h)                                         |
| **std::string**                                                                                                                                        | [filestream/spec/slv_rw_spec_std_string.h](/src/src_sleeve/filestream/spec/slv_rw_spec_std_string.h)                         |
| **std::vector**                                                                                                                                        | [filestream/spec/slv_rw_spec_std_vector.h](/src/src_sleeve/filestream/spec/slv_rw_spec_std_vector.h)                         |
| std::array                                                                                                                                             | [filestream/spec/slv_rw_spec_std_array.h](/src/src_sleeve/filestream/spec/slv_rw_spec_std_array.h)                           |
| std::list                                                                                                                                              | [filestream/spec/slv_rw_spec_std_list.h](/src/src_sleeve/filestream/spec/slv_rw_spec_std_list.h)                             |
| std::deque                                                                                                                                             | [filestream/spec/slv_rw_spec_std_deque.h](/src/src_sleeve/filestream/spec/slv_rw_spec_std_deque.h)                           |
| std::pair                                                                                                                                              | [filestream/spec/slv_rw_spec_std_pair.h](/src/src_sleeve/filestream/spec/slv_rw_spec_std_pair.h)                             |
| std::map                                                                                                                                               | [filestream/spec/slv_rw_spec_std_map.h](/src/src_sleeve/filestream/spec/slv_rw_spec_std_map.h)                               |
| std::unordered_map                                                                                                                                     | [filestream/spec/slv_rw_spec_unordered_map.h](/src/src_sleeve/filestream/spec/slv_rw_spec_std_unordered_map.h)               |
| boost::container::vector \*                                                                                                                            | [filestream/spec/slv_rw_spec_boost_container_vector.h](/src/src_sleeve/filestream/spec/slv_rw_spec_boost_container_vector.h) |
| boost::unordered::unordered_map \*                                                                                                                     | [filestream/spec/slv_rw_spec_boost_unordered_map.h](/src/src_sleeve/filestream/spec/slv_rw_spec_boost_unordered_map.h)       |

\* Provided boost is included in your project, and:

- <code>#define GLOVE_ENABLE_BOOST</code> is set before including glove.h

- or glove was compiled with CMake option <code>OPTION_USE_BOOST</code> <code>ON</code>

##### Remark

It is possible to add specializations for other types depending on your needs. However, methods `readB` and `writeB` can also be implemented for the type to be managed, as in [this example](/doc/readme/ReadWriteFile/ReadWriteFile_class_binary.md). The choice depends essentially on the possibility or not to implement methods for the type (assuming it is a structure or a class).
