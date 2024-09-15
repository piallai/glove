# CLI parametrization

The framework includes a simple method to transform the command line arguments of a `main` into a parametrization, including management of types.

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

    return 0;
}
```

Defining a parametrization `ParametersCLI` taking into accound the properties of the command line arguments, and adding the macro <code>GLOVE_CLI(ParametersCLI)</code> , the program becomes:

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

    ParametersCLI parameters_CLI = SlvCLI::parse<ParametersCLI>(argc, argv);

    std::cout << parameters_CLI << std::endl;

    return 0;
}
```

Executing the program with no CLI arguments:

```shell
./main
```

Because there is no CLI argument to parse, the program (obviously) outputs the default values of the parametrization:

```shell
parameter1 : -I :
parameter2 : -O :
parameter3 : -k : 2
parameter4 : -enable : 0
parameter5 : Advanced : parameter1 : -foo : 2
parameter2 : -bar : 7
parameter3 : -size : -1x-1
```

If specifying CLI arguments:

```shell
./main -I /path/path -O /path/output_path -k 17 -size 128x64 -enable
```

The output becomes:

```shell
parameter1 : -I : /path/path
parameter2 : -O : /path/output_path
parameter3 : -k : 17
parameter4 : -enable : 1
parameter5 : Advanced : parameter1 : -foo : 2
parameter2 : -bar : 7
parameter3 : -size : 128x64
```

Meaning the CLI arguments are properly assigned to their corresponding typed parameter.

More details in [sample015_1.cpp](/src/src_samples/src_sample015_1/sample015_1.cpp).
