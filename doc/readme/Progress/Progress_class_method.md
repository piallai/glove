# Progress

## Class method

Example of how to monitor the progress feedback of an algorithm in a method of a class. In this example, the class inherits <code>SlvProgression</code> to provide it a default progression.

```cpp
/*! Example class containing a method which progress requires monitoring.*/
class ClassC : public SlvProgression {
private:
    /*! Number of iterations of the virtual algorithm.*/
    unsigned int Niterations;
public:
    /*! \p _Niterations : Number of iterations of the virtual algorithm.*/
    ClassC(int _Niterations);
    /*! Simulate the computation of an algorithm which progress needs to be tracked.*/
    void process() {
        unsigned int i = 0;
        get_progression()->set_message("Processing ClassC");
        get_progression()->start(&i, Niterations);
        for (i = 0; i < Niterations; i++) {
            // Simulates computation
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            get_progression()->update();
        }
    }
};
```

###### Remark

Using <code>SlvProgression</code> is not mandatory. One can simply add a <code>SlvProgressionQt</code> as member of <code>ClassC</code>.

### Qt handling

To track the progress of the algorithm, simply create a <code>GlvProgressMgr</code> widget and add the progression to it. Then run the method <code>ClassC::process</code> in a <code>QtConcurrent</code> thread.

```cpp
ClassC classC(100);
GlvProgressMgr progress_mgr;
progress_mgr.add_progression(classC.get_progression());
progress_mgr.show();

QFuture<void> future = QtConcurrent::run(&classC, &ClassC::process);
FutureWrapper future_wrapper(&progress_mgr);
QFutureWatcher<void> future_watcher;
QObject::connect(&future_watcher, SIGNAL(finished()), &future_wrapper, SLOT(hide()));

future_watcher.setFuture(future);
```

Which gives:

![sample010](../../images/samples/sample010.png)

More details in [sample010.cpp](/src/src_samples/src_sample010/sample010.cpp), including OpenMP management.