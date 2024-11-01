# CLI to automatic GUI

The framework includes a simple method to transform the command line arguments of a `main` into a basic GUI. The framework allows a flexible CLI approach.

Let us consider the simple program:

```cpp
// Program supposed to manage 7 command line arguments
// -I : input path of a .txt file
// -O : output path of a .txt file
// -k : a float parameter
// -enable : an option to enable something (no parameter value associated)
// -foo : an advanced float parameter
// -bar : an advanced int parameter
// -size : and advanced parameter formatted as intxint (widthxheight)
int main(int argc, char* argv[]) {

    std::cout << "argc = " << argc << std::endl;
    for (int i = 1; i < argc; i++) {
        std::cout << "argv[i] = " << argv[i] << std::endl;
    }

    return 0;
}
```

Defining a parametrization `ParametersCLI` taking into accound the properties of the command line arguments, and adding the macro <code>GLOVE_APP_PARAM(ParametersCLI)</code>, the program becomes:

```cpp
glvm_parametrization(FooBar, "Foo Bar Size",
                    foo, float, "-foo", "Foo value", 2.f,
                    bar, int, "-bar", "Bar value", 7,
                    size, SlvSize2d<int>, "-size", "Size of processing", SlvSize2d<int>(- 1, -1))

glvm_parametrization(ParametersCLI, "CLI parameters",
                              input_file, SlvFile, "-I", "Input file", SlvFile(SlvFileExtensions({ ".txt" }), SlvFile::IO::Read),
                              output_file, SlvFile, "-O", "Output file", SlvFile(SlvFileExtensions({ ".txt" }), SlvFile::IO::Write),
                              k, float, "-k", "K value", 2.f,
                              enable, bool, "-enable", "Enable something", false,
                              advanced, FooBar, "Advanced", "Advanced parameters", FooBar());

int main(int argc, char* argv[]) {

    GLOVE_APP_PARAM(ParametersCLI)

    std::cout << "argc = " << argc << std::endl;
    for (int i = 1; i < argc; i++) {
        std::cout << "argv[i] = " << argv[i] << std::endl;
    }

    return 0;
}
```

The program can now be executed either as it was before (CLI), or using the Glove GUI by using the command line argument:

```shell
./main -glove
```

![sample015](../../images/samples/sample015.png)

If accepted, the dialog widget will proceed the program with the entered values, so that <code>argc</code> and <code>argv</code> now correspond to the dialog's input.

```shell
argc = 9
argv[i] = -k
argv[i] = 2
argv[i] = -foo
argv[i] = 2
argv[i] = -bar
argv[i] = 7
argv[i] = -size
argv[i] = -1x-1
```

Since **-I** and **-O** are empty, they are being ignored.

### Arguments also in CLI

One can also specify values by adding specifying command line arguments.
Example, preloading some parameters:

```shell
./main -glove -I /path/path -O /path/output_path -k 17 -size 128x64 -enable -extra1 -extra2 12
```

![sample015-1](../../images/samples/sample015-1.png)

If accepted:

```shell
argc = 17
argv[i] = -I
argv[i] = /path/path
argv[i] = -O
argv[i] = /path/output_path
argv[i] = -k
argv[i] = 17
argv[i] = -foo
argv[i] = 2
argv[i] = -bar
argv[i] = 7
argv[i] = -size
argv[i] = 128x64
argv[i] = -extra2
argv[i] = 12
argv[i] = -enable
argv[i] = -extra1
```

The extra arguments <code>-extra1</code> and <code>-extra2 12</code> remain in the final arguments list, despite not being managed by the CLI parametization, thus allowing more flexibility.

More details in [sample015.cpp](/src/src_samples/src_sample015/sample015.cpp).

### Auto save/load parameters

The glove CLI allows automatically saving and loading the last used parameters. 

When clicking the *Ok* button, the parameters are automatically saved in the execution directory. Considering the example above, the file name is:

- *CLI_parameters.json* if the json library is being used

- *CLI_parameters* otherwise (binary file)

When executing the program with the <code>-glove</code> cli argument, if an autosaved parameters file exists, then it is loaded.

However, if any other cli argument is added, then auto loading of the last parameters is disabled.

#### Load specific parameters file

A specific parametrization file can also be loaded (equivalent to clicking the *Load* button), such as:

```cpp
./main -glove "path-to-parametrization-file"
```

In this case, one can add parameter arguments that will replace those loaded in the parametrization file.

Considering the example above, it means that:

```cpp
./main -glove CLI_parameters.json -I /foo/foo/path
```

is not equivalent to:

```cpp
./main -glove -I /foo/foo/path
```

For the first command, the parameters contained in *CLI_parameters.json* are being loaded and the *-I* parameter is being assigned another value. 

For the second command, the default autosaved *CLI_parameters.json* is being ignored since a parameter argument is provided.

#### Parameter as output path

A parameter can used to set an additional path where to save the parametrization file. In the example above, one can define:

```cpp
GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY(ParametersCLI, "-O")
```

A copy of the parametrization file will be automatically saved in the directory of the argument *"-O"* provided the directory exsists.

Alternatively, one can specify the parameter by its declarative name:

```cpp
GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL(ParametersCLI, output_file)
```

In case the parameter is nested, one can use the same macro such as:

```cpp
GLOVE_APP_CLI_PARAMETRIZATION_OUTPUT_DIRECTORY_DECL(ParametersCLI, advanced, size)
```

even though in this example the *size* parameter is irrelevant as an output directory.

### Remarks

- If dialog is cancelled, the execution will stop.
- Command line arguments defining a parameter must start with the character - to be recognized as so.
