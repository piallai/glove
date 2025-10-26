# Convert C++ application to GUI : All you need is Glove!

The framework includes simple methods to transform a C++ program with command line arguments into a basic application.
The features that can be easily added are:

- CLI to GUI : Input arguments through a GUI
- Loop progress to GUI : Show and control progression of loops.
- Status infos to GUI : Show status messages
- Use program recurrently to simulate an interactive mode

**Go to [full example](/doc/readme/App/GlvApp_full.md) for an exhaustive example.**

## CLI to GUI

The framework includes a simple method to transform the command line arguments of a <code>main</code> into a basic GUI.  The framework allows a flexible CLI approach, and can manage saving and loading of the arguments as presented just above.

**Example** : [CLI to GUI](/doc/readme/App/CLI/CLI_GUI.md)

#### Remark

Without relying on Qt, a simple parsing of a 'main' parametrization can be done.

**Example** : [CLI parametrization](/doc/readme/App/CLI/CLI_parametrization.md)

## Full

An example detailing how to use all the features managed by a Glove application can be found [here](/doc/readme/App/GlvApp_full.md).

## Json parametrization

The parametrization can be defined at the project generation stage. It means that the coding of the parametrization does not have to be done in the sources. A json file is in charge of configuring the parametrization.

An example can be found [here](/doc/readme/App/CLI/CLI_GUI_json.md).

## Base macros

The <code>GLOVE_APP</code> macro transforms a program into a GUI application. To be used at the very beginning of the main.
Depending on your needs, several declinaison of the macro exist:

- <code>GLOVE_APP</code> : Enables Glove application by setting "-glove" as CLI argument
- <code>GLOVE_APP_PARAM(Tparametrization)</code> : same as <code>GLOVE_APP</code>, adds CLI arguments by-pass through a parametrization widget defined by [Tparametrization](/doc/readme/Parametrization/Parametrization_basic.md).

## Optional macros

#### <code>GLOVE_APP_AUTO</code>

To create an application than can be launched using no cli arguments (double clicking on the app for instance), add the macro <code>#define GLOVE_APP_AUTO true</code> before calling <code>GLOVE_APP</code>.
Default is <code>false</code>.

#### <code>GLOVE_APP_RECURRENT_MODE</code>

To run the program recurrently, add the macro <code>#define GLOVE_APP_RECURRENT_MODE true</code> before calling <code>GLOVE_APP</code>.
Applies only if <code>GLOVE_APP_THREAD_MODE</code> is set to true.
Default is <code>false</code>.

#### <code>GLOVE_APP_RECURRENT_TYPE</code>

If <code>GLOVE_APP_RECURRENT_MODE</code> is set to <code>true</code>, the macro defines the type of the variable to be kept across all recurrent runs.
One can for example define a structure in charge of keeping data from a run to another. Set <code>#define GLOVE_APP_RECURRENT_TYPE *Type*</code> before calling <code>GLOVE_APP</code>.
Default is <code>int</code>. Must be castable to <code>bool</code>. The returned boolean value accounts for the auto repeat mode to be enabled or not.

#### <code>GLOVE_APP_THREAD_MODE</code>

To run the initial program in the same initial thread, add the macro <code>#define GLOVE_APP_THREAD_MODE false</code> before calling <code>GLOVE_APP</code>.
However, it will disable progress and status features. Input parametrization using a dedicated widget will still be active though.
Default is <code>true</code>.

#### <code>GLOVE_APP_MSVC_NO_CONSOLE</code>

Use <code>#pragma GLOVE_APP_MSVC_NO_CONSOLE</code> before <code>int main</code> to disable terminal when using MSVC.

#### <code>GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY</code>

Use a parameter of the CLI parametrization as a location where to save the configuration file in addition to execution location.
Example: <code>GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY(ParametersCLI, "-O")</code>. With <code>ParametersCLI</code> being the CLI parametrization.
If the parameter does not exist in the CLI parametrization, returns an empty string.
