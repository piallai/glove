# Progress

## Basic

Example of how to monitor the progress feedback of an algorithm. The class <code>SlvProgressionQt</code> is in charge of managing the loop range and the signal emission.

```cpp
// Global declaration for examples
SlvProgressionQt progression0("Loop 0");
SlvProgressionQt progression1("Loop 1");
SlvProgressionQt progression2("Loop 2");
SlvProgressionQt progression3("Loop 3");
```

#### Option 1

Here progressions are directly used as iterators in loops. This is the most compact option. Notice the << operator which in this case replaces the < operator for loop control.

```cpp
void process1(unsigned int _Niterations) {

    progression0.start();// No progress bar for this one
    // Simulates computation
    std::this_thread::sleep_for(std::chrono::milliseconds(_Niterations * 50));
    progression0.end();

    if (!progression0.was_canceled()) {

		progression1.set_message("Processing");
		SlvProgressionQt& i = progression1;
		for (i = 0; i << _Niterations; i++) {

			progression2.set_message("Processing");
			SlvProgressionQt& j = progression2;
			for (j = 0; j << _Niterations; j++) {

				progression3.set_message("Processing");
				SlvProgressionQt& k = progression3;
				for (k = 0; k << _Niterations; k++) {

					// Simulates computation
					std::this_thread::sleep_for(std::chrono::milliseconds(10));

					progression3.update();

				}

				progression2.update();

			}

			progression1.update();

		}

    }

}
```

#### Option 2

Here progressions are taking control of the loop iterators. This is the most explicit option for advanced needs.

```cpp
void process2(unsigned int _Niterations) {

	progression0.start();// No progress bar for this one
    // Simulates computation
    std::this_thread::sleep_for(std::chrono::milliseconds(_Niterations * 50));
    progression0.end();

    if (!progression0.was_canceled()) {

		unsigned int i = 0;
    	progression1.set_message("Processing");
		progression1.start(&i, _Niterations);
		for (i = 0; i < _Niterations; i++) {

			unsigned int j = 0;
        	progression2.set_message("Processing");
			progression2.start(&j, _Niterations);
			for (j = 0; j < _Niterations; j++) {

				unsigned int k = 0;
            	progression3.set_message("Processing");
				progression3.start(&k, _Niterations);
				for (k = 0; k < _Niterations; k++) {

					// Simulates computation
					std::this_thread::sleep_for(std::chrono::milliseconds(10));

					progression3.update();

				}

				progression2.update();

			}

			progression1.update();

		}
	
	}

}
```

At this stage, for both options, Qt is not strictly necessary for compilation.

#### Compilation without Qt

If Qt is not found during compilation/installation of Glove, or if CMake option <code>OPTION_ENABLE_SLV_QT_PROGRESS</code> is set to *OFF*, the code of this example will still compile. However, for the Qt signal emission to operate, Qt must be found and <code>OPTION_ENABLE_SLV_QT_PROGRESS</code> to be *ON* (default).

The same goes for the library as a single header: if <code>#define GLOVE_DISABLE_QT</code> is defined, then the example will still compile, but without the signal emission.

### Qt handling

To track the progress of the algorithm, simply create a <code>GlvProgressMgr</code> widget and add the progressions to it. Then run the function `process` in a `QtConcurrent` thread.

```cpp
GlvProgressMgr progress_mgr;
progress_mgr.add_progression(&progression0, true);
progress_mgr.add_progression(&progression1);
progress_mgr.add_progression(&progression2);
progress_mgr.add_progression(&progression3);
progress_mgr.show();

QFuture<void> future = QtConcurrent::run(&process1, 100);
QFutureWatcher<void> future_watcher;

future_watcher.setFuture(future);
```

Which gives:

![sample010](../../images/samples/sample010_0.png)

The *Cancel* button is operational and allows ending the current loop.

More details in [sample010_0.cpp](/src/src_samples/src_sample010_0/sample010_0.cpp).

##### Remark 1

Closing <code>GlvProgressMgr</code> widget will cancel every cancelable progressions managed by the instance.

##### Remark 2

<code>SlvProgressionQt</code> can not be constructed by copy, therefore it is recommended to use it as a pointer when embedded in a struct/class (and manage its copy construction
