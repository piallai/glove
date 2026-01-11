
   1. [Single header](#single-header-option-1)
   2. [Installation and CMake use](#installation-and-cmake-use-option-2)
      1. [Windows / Visual Studio](#windows--visual-studio)
      2. [Linux](#linux)
   3. [Usage](/doc/readme/General/Usage.md#usage)
      1. [Library location](#library-location)
      2. [CMake configuration of a project using Glove](#cmake-configuration-of-a-project-using-glove)

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

To enable table view for widget data of type double containers, the macro <code>GLOVE_WIDGET_DATA_CONTAINER_TABLE</code> must be defined.

To enable use of glove application [GlvApp](/doc/readme/App/GlvApp.md) across shared libraries, <code>GLOVE_APP_SHARED</code> and <code>GLOVE_APP_SHARED_EXPORT</code> must be defined.
The latter to be defined in the shared library.

```cpp
#define GLOVE_DISABLE_QT // Option to disable Qt management
#define GLOVE_ENABLE_JSON // Option to enable Json management
#define GLOVE_ENABLE_BOOST // Option to enable boost containers management
#define GLOVE_WIDGET_DATA_CONTAINER_TABLE // Option to auto assign double containers as tables for data widgets
#define GLOVE_APP_SHARED // Option to use GlvApp in a shared library
#define GLOVE_APP_SHARED_EXPORT // If GLOVE_APP_SHARED is set, to define in the shared library
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

Copy [CMake/FindGlove.cmake](./CMake/FindGlove.cmake) to a folder named <code>/CMake/CMakeModules</code> at the root of your CMake project.
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

Let <code>myproject</code> be the executable project name. Glove libraries can be linked using:

```cmake
glove_link(myproject)
```