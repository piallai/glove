# Program to Glove app

## Initial program

Let us consider the simple program:

```cpp
// Program supposed to manage 3 command line arguments
// -N1 : Number of iterations for loop 1
// -N2 : Number of iterations for loop 2
// -N3 : Number of iterations for loop 3
int main(int argc, char* argv[]) {

    int N1, N2, N3;
    bool l_args_valid = true;

    // Consider here the program manages its own CLI parser so that:
    // N1, N2, N3 and l_args_valid are parsed.

    if (l_args_valid) {
        for (int i = 0; i < N1; i++) {
            for (int j = 0; j < N2; j++) {
                for (int k = 0; k < N3; k++) {
                    // Simulates computation
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            }
            printf("display some values: %zu and %.2f", std::size_t(i), float(j));
        }
    }

    return 0;
}
```

## Modified program to obtain the Glove app

By defining:

```cpp
glvm_parametrization(ParametersCLI, "CLI parameters",
                                        N1, int, "-N1", "Number of iterations for loop 1.", 100,
                                        N2, int, "-N2", "Number of iterations for loop 2.", 100,
                                        N3, int, "-N3", "Number of iterations for loop 3.", 100);
```

```cpp
struct RecurrentStruct {
    int total_loops = 0;
    // Auto repeat if returns true
    operator bool() const {
    	return false;
    }                
};

int main(int argc, char* argv[]) {

    GlvApp::get_progression("Loop1");
    GlvApp::get_progression("Loop2");
    GlvApp::get_progression("Loop3");

#define GLOVE_APP_RECURRENT_MODE true
#define GLOVE_APP_RECURRENT_TYPE RecurrentStruct
    RecurrentStruct glove_recurrent_var;
    glove_recurrent_var.total_loops = 0;

    GLOVE_APP_PARAM(ParametersCLI);

    int N1, N2, N3;
    bool l_args_valid = true;

    // Consider here the program manages its own CLI parser so that:
    // N1, N2, N3 and l_args_valid are parsed.

    if (l_args_valid) {

        SlvProgressionQt& i = *GlvApp::get_progression("Loop1");// instead of: int i;
        for (i = 0; i << N1; i++) {// instead of : i < N1

            SlvProgressionQt& j = *GlvApp::get_progression("Loop2");
            for (j = 0; j << N2; j++) {// instead of : j < N2

                SlvProgressionQt& k = *GlvApp::get_progression("Loop3");
                for (k = 0; k << N3; k++) {// instead of : k < N3

                    // Simulates computation
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));

                    glove_recurrent_var.total_loops++;
                }

            }

            // instead of printf("display some values: %zu and %.2f", std::size_t(i), float(j))
            bool l_wait = true;
            GlvApp::show(SlvStatus(SlvStatus::statusType::warning, "display some values: %zu and %.2f", std::size_t(i), float(j)), l_wait);

        }

    }

    GlvApp::show(SlvStatus(SlvStatus::statusType::information, "Total loops: " + std::to_string(glove_recurrent_var.total_loops)), true);

    return 0;
}
```

More details in [sample015_0.cpp](/src/src_samples/src_sample015_0/sample015_0.cpp).
