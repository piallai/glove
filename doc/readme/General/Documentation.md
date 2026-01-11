
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
   2. [Glove application](#glove-application)
   3. [Table interfacing](#table-interfacing)
      1. [Examples](#examples--2)
   4. [Progress feedback](#progress-feedback)
      1. [Examples](#examples--3)
   5. [Files I/O](#files-io)
   6. [Specializations overview](#specializations-overview)
3. [Use Glove](/doc/readme/General/Usage.md)
4. [License](#license)      

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

A parametrization can currently contain up to 24 parameters of any type. Parametrizations can contain nested parametrizations. So there is theoretically no limit to the number of parameters.

### Examples :

##### [Basic](/doc/readme/Parametrization/Parametrization_basic.md)

##### [Nested](/doc/readme/Parametrization/Parametrization_nested.md)

##### [Rules](/doc/readme/Parametrization/Parametrization_rules.md)

##### [List](/doc/readme/Parametrization/Parametrization_list.md)

A parameter can be disabled by setting his type to <code>nullptr_t</code>.

### Save/load interface

Each parametrization widget <code>GlvParametrizationWidget</code> and data widget <code>GlvWidget</code> can be extended easily with an input/output file interface.

##### Examples :

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

## Glove Application

The framework includes simple methods to transform a C++ program with command line arguments into a basic application.
The features that can be easily added are:

- Input arguments through a GUI
- Show and control progression of loops.
- Show status messages

**Details at** [Glove application](/doc/readme/App/GlvApp.md)

## Table interfacing

The framework includes a data modeling extra layer for view and edition. The class [GlvTableView.h](/src/src_glove/GlvTableView.h) allows visualization of data as tables provided their modeling is defined.
The modelings are implemented in specializations.
Some specializations related to common containers are already available and listed at [Model specializations](/doc/readme/ModelView/ModelView_specs.md).

The table view can handle data of multiple dimensions, using different containers, while displaying a handy interface for view and edition.

#### Examples :

##### [Basic](/doc/readme/ModelView/ModelView_basic.md)

##### [Widget editor](/doc/readme/ModelView/ModelView_widget_editor.md)

##### [std::map](/doc/readme/ModelView/ModelView_std_map.md)

##### [SlvPool](/doc/readme/ModelView/ModelView_SlvPool.md)

##### [Multiple containers](/doc/readme/ModelView/ModelView_multiple.md)

##### [Dialog](/doc/readme/ModelView/ModelView_dialog.md)

## Progress feedback

A progress interface is proposed in the library. Running an algorithm in a separate thread and monitoring its progress is made easy. You can find examples below of how to use the interface.

#### Examples :

##### [Basic](/doc/readme/Progress/Progress_basic.md)

##### [Class method](/doc/readme/Progress/Progress_class_method.md)

##### [Class multiple](/doc/readme/Progress/Progress_class_multiple.md)

## Files I/O

Filesystem : C++11 compatible. Does not need boost.

#### Examples :

##### [File opening](/doc/readme/ReadWriteFile/ReadWriteFile_opening.md)

##### [Class binary file I/O](/doc/readme/ReadWriteFile/ReadWriteFile_class_binary.md)

##### [Class binary file I/O](/doc/readme/ReadWriteFile/ReadWriteFile_class_binary2.md)

##### [Class I/O (<< and >>)](/doc/readme/ReadWriteFile/ReadWriteFile_class_IO.md)

##### [Class writing (text)](/doc/readme/ReadWriteFile/ReadWriteFile_class_text.md)

## Specializations overview

The list of the key classes that are specialized can be found [here](/doc/readme/Specializations.md)

# Use Glove

Details about how to include Glove to a project can be found [here](/doc/readme/General/Usage.md).

# License

The library is licensed as GNU GPLv3. Dual licensing with commercial license is possible on demand.
