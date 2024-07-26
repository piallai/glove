# ![C++](https://img.shields.io/badge/C++-Library-blue.svg?style=flat&logo=c%2B%2B) Glove

[![License: GPLv3](https://img.shields.io/badge/license-GPLv3-blue)](https://opensource.org/license/gpl-3-0/)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://shields.io/)
[![Generic badge](https://img.shields.io/badge/C++-11,14,17,20-blue.svg)](https://shields.io/)
[![Qt5](https://img.shields.io/badge/Qt-5%20&%206-brightgreen)](https://doc.qt.io/qt-5/)
[![Single header](https://img.shields.io/badge/Single%20header-yes-green.svg)](https://shields.io/)
[![Generic badge](https://img.shields.io/badge/gcc-10+-blue.svg)](https://shields.io/)
[![Generic badge](https://img.shields.io/badge/MSVC-yes-green.svg)](https://shields.io/)
[![Generic badge](https://img.shields.io/badge/clang-TODO-red.svg)](https://shields.io/)

![Teaser](/doc/images/teaser/teaser.png)

*Code of samples above*:  
- [sample001 : Class parametrization](/src/src_samples/src_sample001/sample001.cpp)  
- [sample010_0 : Progress feedback](/src/src_samples/src_sample010_0/sample010_0.cpp)  
- [matrix8D : Table view](/src/src_samples/src_sample004_0/sample004_0.cpp)

# Summary

- The library is designed as a general C++ toolkit with straightforward bindings with Qt
  
  - to manage parametrization of a class
  
  - to manage data containers as tables
  
  - to manage progress feedback of algorithms

- Requires only [Qt](https://doc.qt.io/qt-6/get-and-install-qt.html) to be installed

- **Single header available**

- Modularity by relying on template specializations

- Documentation available [here](https://piallai.github.io/glove/)

# Table of contents

1. [Presentation](#presentation)
2. [Features](#features)
   1. [Class parametrization : automatic widgets](#class-parametrization--automatic-widgets)
      1. [Paradigm](#paradigm)
      2. [Examples](#examples-)
      3. [Save/load interface](#saveload-interface)
      4. [Remarks](#remarks)
         1. [Widget specializations](#glvwidgetdata-specializations)
         2. [Convenient macros](#convient-macros)
   2. [CLI to GUI](#cli-to-gui)
   3. [Table interfacing](#table-interfacing)
      1. [Examples](#examples--2)
   4. [Progress feedback](#progress-feedback)
      1. [Examples](#examples--3)
   5. [Files I/O](#files-io)
   6. [Specializations overview](#specializations-overview)
3. [Use Glove](#use-glove)
   1. [Single header](#single-header-option-1)
   2. [Installation and CMake use](#installation-and-cmake-use-option-2)
      1. [Windows / Visual Studio](#windows--visual-studio)
      2. [Linux](#linux)
   3. [Usage](#usage)
      1. [Library location](#library-location)
      2. [CMake configuration of a project using Glove](#cmake-configuration-of-a-project-using-glove)

# Presentation

Glove is a C++/Qt library aiming at creating simple interfaces. It proposes several basic GUI features that are often necessary to develop a user-friendly program. The toolkit aims at minimizing the required knowledge of Qt. For now, the main features of the library are:

- The management of parameters

- Table/tree interfacing with data containers

- A progress feedback tracking

- Files management (read and write)

The library consists in an alternative to Qt UI for simple prototypes (QtCreator is not required). It is particularly suited for developpers wishing to create a basic graphical user interface  (input/output) of their program or algorithm without needing in-depth knowledge of Qt. A minimal understanding of widgets may be required depending on the use of the library.

The library is separated in two layers.

- **Sleeve**
  
  - Slv prefix
  
  - C++ only
  
  - Can compile without Qt

- **Glove**
  
  - Glv prefix
  
  - Qt layer interpreting the Sleeve layer for interfacing

The library can be used either:

- by using a single header. See [details](#single-header-option-1)
  
  - [moc](https://doc.qt.io/qt-6/moc.html) management using CMake or [qmake](https://doc.qt.io/qt-6/qmake-manual.html) is still required

- by installation and direct use of sources and compiled libraires. See [details](#installation-and-cmake-use-option-2)

## Class parametrization : automatic widgets

Aims at providing a simple framework for parametrization of class instances, by inheriting a dedicated class. Creating the parametrization interface using Qt widgets is straightforward.

### Paradigm

The framework explicitly points what are the parameters of a class. Parameters are defined by:

- a variable name
- a type
- a name
- a comment
- a default value
- optional rules on its value

A parametrization can currently contain up to 25 parameters of any type. Parametrizations can contain nested parametrizations. So there is theoretically no limit to the number of parameters.

### Examples :

##### [Basic](/doc/readme/Parametrization/Parametrization_basic.md)

##### [Nested](/doc/readme/Parametrization/Parametrization_nested.md)

##### [Rules](/doc/readme/Parametrization/Parametrization_rules.md)

##### [List](/doc/readme/Parametrization/Parametrization_list.md)

### Save/load interface

Each parametrization widget <code>GlvParametrizationWidget</code> and data widget <code>GlvWidget</code> can be extended easily with an input/output file interface.

###### Examples :

###### [Save/load : binary](/doc/readme/SaveLoad/SaveLoad_binary.md)

###### [Save/load : json](/doc/readme/SaveLoad/SaveLoad_json.md)

### Remarks

#### GlvWidgetData specializations

You can find the list of type specializations provided in the library here [GlvWidgetData_specs.md](/doc/readme/GlvWidgetData_specs.md).

See [this page](/doc/readme/GlvWidgetData_spec.md) for a custom specialization.

#### Convient macros

List of convenient macros to handle parametrizations.

- `glvm_parametrization`:
  
  - Declare a parametrization
  
  - see [this page](/doc/readme/Parametrization/Parametrization_basic.md) for example

- <code>glvm_get_parameter_GlvWidget(_parametrization_widget, _parameter_index)</code>:
  
  - Get the <code>GlvWidget</code> associated to parameter <code>_parameter_index</code>

- `glvm_get_parameter_GlvWidgetData(_parametrization_widget, _parameter_index)`:
  
  - Get the parameter widget (ex: *QSpinBox*) associated to parameter `_parameter_index`
  
  - see [this page](/doc/readme/Parametrization/Parametrization_basic.md) for example

- `glvm_SlvEnum` / `glvm_SlvEnum_named`:
  
  - Declare an *enum* compatible with *glove*
  
  - see [here](/doc/readme/SlvEnum.md) and [here](/doc/readme/GlvEnumWidget.md) for example

## CLI to GUI

The framework includes a simple method to transform the command line arguments of a <code>main</code> into a basic GUI.  The framework allows a flexible CLI approach, and can manage saving and loading of the arguments as presented just above.

### Example : [CLI to GUI](/doc/readme/CLI/CLI.md)

## Table interfacing

The framework includes a data modeling extra layer for view and edition. The class [GlvTableView.h](/src/src_glove/GlvTableView.h) allows visualization of data as tables provided their modeling is defined.
The modelings are implemented in specializations.
Some specializations related to common containers are already available and listed at [Model specializations](/doc/readme/ModelView/ModelView_specs.md).

The table view can handle data of multiple dimensions, using different containers, while displaying a handy interface for view and edition.

##### Examples :

##### [Basic](/doc/readme/ModelView/ModelView_basic.md)

##### [Widget editor](/doc/readme/ModelView/ModelView_widget_editor.md)

##### [std::map](/doc/readme/ModelView/ModelView_std_map.md)

##### [SlvPool](/doc/readme/ModelView/ModelView_SlvPool.md)

##### [Multiple containers](/doc/readme/ModelView/ModelView_multiple.md)

##### [Dialog](/doc/readme/ModelView/ModelView_dialog.md)

## Progress feedback

A progress interface is proposed in the library. Running an algorithm in a separate thread and monitoring its progress is made easy. You can find examples below of how to use the interface.

##### Examples :

##### [Basic](/doc/readme/Progress/Progress_basic.md)

##### [Class method](/doc/readme/Progress/Progress_class_method.md)

##### [Class multiple](/doc/readme/Progress/Progress_class_multiple.md)

## Files I/O

Filesystem : C++11 compatible. Does not need boost.

##### Examples :

##### [File opening](/doc/readme/ReadWriteFile/ReadWriteFile_opening.md)

##### [Class binary file I/O](/doc/readme/ReadWriteFile/ReadWriteFile_class_binary.md)

##### [Class binary file I/O](/doc/readme/ReadWriteFile/ReadWriteFile_class_binary2.md)

##### [Class I/O (<< and >>)](/doc/readme/ReadWriteFile/ReadWriteFile_class_IO.md)

##### [Class writing (text)](/doc/readme/ReadWriteFile/ReadWriteFile_class_text.md)

## Specializations overview

The list of the key classes that are specialized can be found [here](/doc/readme/Specializations.md)

# Use Glove

The library can be used either:

- **Option 1** : by adding a single header to a qmake or cmake project
  
  - Does not require compilation of Glove.

- **Option 2** : by compiling and installing includes and compiled binaries,
  
  - then use the installed components in a CMake project

The second option allows parsimonious include of headers and faster compilation of the code.

## Single header (option 1)

The file [glove.h](/src/src_single_header/glove.h) available in release can be simply included in sources. The management of *Qt* can be disabled by using the macro `GLOVE_DISABLE_QT`.

To enable the json management, the macro `GLOVE_ENABLE_JSON` must be defined.

To enable the management of boost containers, the macro <code>GLOVE_ENABLE_BOOST</code> must be defined.

```cpp
#define GLOVE_DISABLE_QT // Option to disable Qt management
#define GLOVE_ENABLE_JSON // Option to enable Json management
#define GLOVE_ENABLE_BOOST // Option to enable boost containers management
#include "glove.h"
```

The file [glove.h](/src/src_single_header/glove.h) must be added to the CMake or qmake .pro file.

An example project using the single header is proposed [here](/example).

## Installation and CMake use (option 2)

The installation only requires CMake and Qt to be installed.

##### Windows / Visual Studio

###### Option 1 : CMake command line

At the root of the library, using PowerShell:

```console
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
```

###### Option 2 : CMake GUI

* In the field <code>Where is the source code</code>, select the root folder of the library. That is, where CMakeLists.txt is.
* In the field <code>Where to build the binaries</code>, select the <code>build</code> folder (to create yourself).
* Press <code>Configure</code>
* Press <code>Generate</code>

###### Generated project

Open <code>Glove.sln</code>, and compile the <code>INSTALL</code> target.
The library will install to <code>build/install</code>.

##### Linux

* The default installation path is <code>/usr/local</code>.
  * The library will install in:
    * <code>/usr/local/lib/glove</code> 
    * <code>/usr/local/include/glove</code>
* The default build type is *Release* if <code>-DCMAKE_BUILD_TYPE</code> is not specified.

At the root of the library:

```console
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make install
```

* The <code>make install</code> command may require <code>sudo make install</code> depending on privileges to install the library in <code>/usr/local/</code>.
* To install at a specific location, use <code>cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX:PATH=/path/where/to/install</code>
* For instance <code>cmake .. -DCMAKE_INSTALL_PREFIX:PATH=.</code> will install the library in the current build directory under <code>./install</code>

##### Examples

After compilation, all the executable examples using the library can be found in the directory <code>build/samples</code>.

### Usage

##### Library location

###### Windows

Set the environment variable <code>GLOVE_ROOT</code> as the path where the library was installed. That is, in the example above, <code>build/install</code>.
For this purpose, in the search field of Windows, select "Environment variables". Then in the <code>User variables</code> part, press <code>New</code>.

###### Linux

If <code>-DCMAKE_INSTALL_PREFIX:PATH=/path/where/to/install</code> was used at CMake generation, then it is required to
set the environment variable <code>GLOVE_ROOT</code> as the path where the library was installed. For instance, <code>build/install</code>.
For this purpose, edit the file <code>~/.bashrc</code> by adding the line: <code>export GLOVE_ROOT=/path/where/to/install</code>. The full path must be set (*i.e.* not relative to the library build directory).

##### CMake configuration of a project using Glove

An example project using the installed library is proposed [here](/example).

###### Find library

Copy [CMake/FindGlove.cmake](./CMake/FindGlove.cmake) to a folder named <code>/CMake/CMakeModules</code> at the root of the CMake project.
In the CMakeLists.txt, add where to look for <code>FindGlove.cmake</code> by setting  

```cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake/CMakeModules")
```

Then set:

```cmake
find_package(Glove)
```

###### Include

In CMake's <code>INCLUDE_DIRECTORIES</code>, add <code>${GLOVE_INCLUDE_DIRS}</code>.

###### Link

```cmake
foreach(lib ${GLOVE_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} optimized ${lib})
endforeach()
foreach(lib ${GLOVE_LIBRARIES_DEBUG})
    target_link_libraries(${PROJECT_NAME} debug ${lib})
endforeach()
```
