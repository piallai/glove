# GlvWidgetData specializations

Here is the list of the managed types and containers in the library. You can include the corresponding header to your code depending on your needs.
More types can be specialized.
Also, you can modify the specialization of a type depending on your needs.

| Type                                                      | Header                                                                                                      | Widget                                                                |
| --------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------- |
| int                                                       | [GlvWidgetData_spec_AT.h](/src/src_glove/GlvWidgetData_spec_AT.h)                                           | [QSpinBox](https://doc.qt.io/qt-5/qspinbox.html)                      |
| unsigned int                                              | [GlvWidgetData_spec_AT.h](/src/src_glove/GlvWidgetData_spec_AT.h)                                           | [QSpinBox](https://doc.qt.io/qt-5/qspinbox.html)                      |
| float                                                     | [GlvWidgetData_spec_AT.h](/src/src_glove/GlvWidgetData_spec_AT.h)                                           | [QDoubleSpinBox](https://doc.qt.io/qt-5/qdoublespinbox.html)          |
| double                                                    | [GlvWidgetData_spec_AT.h](/src/src_glove/GlvWidgetData_spec_AT.h)                                           | [QDoubleSpinBox](https://doc.qt.io/qt-5/qdoublespinbox.html)          |
| bool                                                      | [GlvWidgetData_spec_AT.h](/src/src_glove/GlvWidgetData_spec_AT.h)                                           | [QCheckBox](https://doc.qt.io/qt-5/qcheckbox.html)                    |
| std::string                                               | [GlvWidgetData_spec_std_string.h](/src/src_glove/GlvWidgetData_spec_std_string.h)                           | [QLineEdit](https://doc.qt.io/qt-5/qlineedit.html)                    |
| std::pair                                                 | [GlvWidgetData_spec_std_pair.h](/src/src_glove/GlvWidgetData_spec_std_pair.h)                               | [GlvPairWidget](/doc/readme/GlvPairWidget.md)                         |
| std::vector \*                                            | [GlvWidgetData_spec_std_vector.h](/src/src_glove/GlvWidgetData_spec_std_vector.h)                           | [GlvVectorWidget](/doc/readme/GlvVectorWidget.md)                     |
| std::array \*                                             | [GlvWidgetData_spec_std_array.h](/src/src_glove/GlvWidgetData_spec_std_array.h)                             | [GlvArrayWidget](/doc/readme/GlvArrayWidget.md)                       |
| Nested containers \*\*                                    | [GlvWidgetData_spec_std_container_container.h](/src/src_glove/GlvWidgetData_spec_std_container_container.h) | [GlvTableView](/doc/readme/ModelView/ModelView_basic.md)              |
| std::map                                                  | [GlvWidgetData_spec_std_map.h](/src/src_glove/GlvWidgetData_spec_std_map.h)                                 | [GlvMapWidget](/doc/readme/GlvMapWidget.md)                           |
| [enum](/doc/readme/SlvEnum.md)                            | [GlvWidgetData_spec_SlvEnum.h](/src/src_glove_add/GlvWidgetData_spec_SlvEnum.h)                             | [GlvEnumWidget](/doc/readme/GlvEnumWidget.md)                         |
| [SlvProportion](/src/src_sleeve/SlvProportion.h)          | [GlvWidgetData_spec_SlvProportion.h](/src/src_glove_add/GlvWidgetData_spec_SlvProportion.h)                 | [GlvProportionWidget](/doc/readme/GlvProportionWidget.md)             |
| [SlvSize2d](/src/src_sleeve/SlvSize2d.h)                  | [GlvWidgetData_spec_SlvSize2d.h](/src/src_glove_add/GlvWidgetData_spec_SlvSize2d.h)                         | [GlvSize2dWidget](/doc/readme/GlvSize2dWidget.md)                     |
| [SlvFile](/src/src_sleeve/filestream/SlvFile.h)           | [GlvWidgetData_spec_SlvFile.h](/src/src_glove_add/GlvWidgetData_spec_SlvFile.h)                             | [GlvOpenFile](/doc/readme/GlvOpenFile.md)                             |
| [SlvDirectory](/src/src_sleeve/filestream/SlvDirectory.h) | [GlvWidgetData_spec_SlvDirectory.h](/src/src_glove_add/GlvWidgetData_spec_SlvDirectory.h)                   | [GlvOpenDirectory](/doc/readme/GlvOpenDirectory.md)                   |
| std::filesystem::path \*\*\*                              | [GlvWidgetData_spec_std_filesystem_path.h](/src/src_glove/GlvWidgetData_spec_std_filesystem_path.h)         | [GlvOpenFile](/doc/readme/GlvOpenFile.md)                             |
| SlvParametrization                                        | [GlvWidgetData_spec_SlvParametrization.h](/src/src_glove_add/GlvWidgetData_spec_SlvParametrization.h)       | [GlvParametrizationWidget](/src/src_glove/GlvParametrizationWidget.h) |
| **All**                                                   | [GlvWidgetData_spec_All.h](/src/src_glove_add/GlvWidgetData_spec_All.h)                                     |                                                                       |

\* If nested type is not a container. Example: <code>std::vector<int></code>.  
\*\* Example: <code>std::vector< std::array<int, 4> ></code>. See [this page](/doc/readme/ModelView/ModelView_specs.md).  
\*\*\* C++17 and above only

#### Remark

For numerical types, the default range and number of decimals is:

| Type         | Range                                                                       | Decimals                                 |
|:------------ | --------------------------------------------------------------------------- | ---------------------------------------- |
| int          | [std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max()]       | -                                        |
| unsigned int | [0, std::numeric_limits<int>::max()]                                        | -                                        |
| float        | [std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max()]   | max(2, N decimals of construction value) |
| double       | [std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max()] | max(2, N decimals of construction value) |
