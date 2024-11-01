# Convert C++ application to GUI : All you need is Glove!

The framework includes simple methods to transform a C++ program with command line arguments into a basic application.
The features that can be easily added are:

- CLI to GUI : Input arguments through a GUI
- Loop progress to GUI : Show and control progression of loops.
- Status infos to GUI : Show status messages

**Go to [full example](/doc/readme/App/GlvApp_full.md) for an exhaustive example.**

## CLI to GUI

The framework includes a simple method to transform the command line arguments of a <code>main</code> into a basic GUI.  The framework allows a flexible CLI approach, and can manage saving and loading of the arguments as presented just above.

**Example** : [CLI to GUI](/doc/readme/App/CLI/CLI_GUI.md)

#### Remark

Without relying on Qt, a simple parsing of a 'main' parametrization can be done.

**Example** : [CLI parametrization](/doc/readme/App/CLI/CLI_parametrization.md)

## Full

An example detailing how to use all the features managed by a Glove application can be found [here](/doc/readme/App/GlvApp_full.md).

## Important macros

The <code>GLOVE_APP</code> macro transforms a program into a GUI application. To be used at the very beginning of the main.
Depending on your needs, several declinaison of the macro exist:

- <code>GLOVE_APP</code> : Enables Glove application by setting "-glove" as CLI argument
- <code>GLOVE_APP_AUTO</code> : no need to set "-glove", the program is turned into a GUI as default
- <code>GLOVE_APP_PARAM(Tparametrization)</code> : same as <code>GLOVE_APP</code>, adds CLI arguments by-pass through a parametrization widget defined by [Tparametrization](/doc/readme/Parametrization/Parametrization_basic.md).
- <code>GLOVE_APP_PARAM_AUTO(Tparametrization)</code> : same as <code>GLOVE_APP_AUTO</code>, adds CLI arguments by-pass through a parametrization widget defined by [Tparametrization](/doc/readme/Parametrization/Parametrization_basic.md).

For example, if one wants to create an application than can be launched using no cli arguments (double clicking on the app for instance), the <code>_AUTO</code> declinaison is more suited.

To run the initial program in the same initial thread, add the macro <code>#define GLOVE_APP_THREAD_MODE false </code> before calling <code>GLOVE_APP</code>.
However, it will disable progress and status features. Input parametrization using a dedicated widget will still be active though.

Use <code>#pragma GLOVE_APP_MSVC_NO_CONSOLE</code> before <code>int main</code> to disable terminal when using MSVC.
