# Progress

## Basic

Example of how to monitor the progress feedback of an algorithm. The class <code>SlvProgressionQt</code> is in charge of managing the loop range and the signal emission.

```cpp
// Global declaration for example
SlvProgressionQt progression1("Loop 1");
SlvProgressionQt progression2("Loop 2");
SlvProgressionQt progression3("Loop 3");
```

```cpp
void process(unsigned int _Niterations) {

    unsigned int i = 0;
    progression1.emit_start("Processing", &i, _Niterations);
    for (i = 0; i < _Niterations; i++) {

        unsigned int j = 0;
        progression2.emit_start("Processing", &j, _Niterations);
        for (j = 0; j < _Niterations; j++) {

            unsigned int k = 0;
            progression3.emit_start("Processing", &k, _Niterations);
            for (k = 0; k < _Niterations; k++) {

                // Simulates computation
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                progression3.emit_progress();

            }

            progression2.emit_progress();

        }

        progression1.emit_progress();

    }

}
```

At this stage, Qt is not strictly necessary for compilation.

###### Compilation without Qt

If Qt is not found during compilation/installation of Glove, or if CMake option <code>OPTION_ENABLE_SLV_QT_PROGRESS</code> is set to *OFF*, the code of this example will still compile. However, for the Qt signal emission to operate, Qt must be found and <code>OPTION_ENABLE_SLV_QT_PROGRESS</code> to be *ON* (default).

The same goes for the library as a single header: if <code>#define GLOVE_DISABLE_QT</code> is defined, then the example will still compile, but without the signal emission.

### Qt handling

To track the progress of the algorithm, simply create a <code>GlvProgressMgr</code> widget and add the progressions to it. Then run the function `process` in a `QtConcurrent` thread.

```cpp
GlvProgressMgr progress_mgr;
progress_mgr.add_progression(&progression1);
progress_mgr.add_progression(&progression2);
progress_mgr.add_progression(&progression3);
progress_mgr.show();

QFuture<void> future = QtConcurrent::run(&process, 100);
QFutureWatcher<void> future_watcher;

future_watcher.setFuture(future);
```

Which gives:

![sample010](../../images/samples/sample010_0.png)

The *Cancel* button is operational and allows ending the current loop.

More details in [sample010_0.cpp](/src/src_samples/src_sample010_0/sample010_0.cpp).

##### Remark

<code>SlvProgressionQt</code> can not be constructed by copy, therefore it is recommended to use it as a pointer when embedded in a struct/class (and manage its copy construction