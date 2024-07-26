# Model View

## Specializations

Here are listed all the containers that are managed by the framework. All containers can be used together.

| Type                                 | Header                                                                                                              |
| ------------------------------------ | ------------------------------------------------------------------------------------------------------------------- |
| std::vector \*                       | [glv_QStandardItemModelMaker_spec_std_container.h](/src/src_glove/glv_QStandardItemModelMaker_spec_std_container.h) |
| std::list \*                         | [glv_QStandardItemModelMaker_spec_std_container.h](/src/src_glove/glv_QStandardItemModelMaker_spec_std_container.h) |
| std::deque \*                        | [glv_QStandardItemModelMaker_spec_std_container.h](/src/src_glove/glv_QStandardItemModelMaker_spec_std_container.h) |
| std::array \*                        | [glv_QStandardItemModelMaker_spec_std_container.h](/src/src_glove/glv_QStandardItemModelMaker_spec_std_container.h) |
| std::map                             | [glv_QStandardItemModelMaker_spec_std_map.h](/src/src_glove/glv_QStandardItemModelMaker_spec_std_map.h)             |
| [SlvPool](/src/src_sleeve/SlvPool.h) | [glv_QStandardItemModelMaker_spec_SlvPool.h](/src/src_glove_add/glv_QStandardItemModelMaker_spec_SlvPool.h)             |

\* Containers creating a table when used together. Example: <code>std::vector< std::array<int, 4> ></code>.