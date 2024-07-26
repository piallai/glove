# GlvWidgetData specialization

It is possible to add specializations for other types. Let us consider the class *Foo* encapsulating a simple *int*.

```cpp
class Foo {
    int value;
public:
    Foo(int _value = 7) { value = _value; }
    ~Foo() {}
    int get_value() const {
        return value;
    }
    void set_value(const int _value) {
        value = _value;
    }
    friend std::ostream& operator<<(std::ostream& _os, const Foo& _foo) {
        _os << _foo.value;
        return _os;
    }
    friend std::istream& operator>>(std::istream& _is, Foo& _foo) {
        _is >> _foo.value;
        return _is;
    }
};
```

For this example, the widget associated to *Foo* will be a simple *QSpinBox*. But one can design a specific widget. In any case, methods *get_value*, *set_value* and *set_editable* must be properly implemented to bridge the methods to the associated widget, as shown below.

```cpp
template <>
class GlvWidgetData<Foo> : public QSpinBox {
public:
    GlvWidgetData(QWidget* _parent = 0) {}
    GlvWidgetData(const Foo& _value, QWidget* _parent = 0) {
        set_value(_value);
    }
    ~GlvWidgetData() {}
    /*! Implement editability of associated widget.*/
    void set_editable(bool _l_editable) {
        QSpinBox::setReadOnly(!_l_editable);
    }
    /*! Implement Foo from associated widget.*/
    Foo get_value() const {
        return Foo(QSpinBox::value());
    }
    /*! Implement Foo to associated widget.*/
    void set_value(const Foo& _value) {
        QSpinBox::setValue(_value.get_value());
    }
};
```

Also, the signals of the associated widget (still *QSpinBox* in this example) must be properly connected to the widget connector:

```cpp
template <>
struct GlvWidgetMakerConnect<Foo> {
    static void connect(GlvWidgetData<Foo>* _widget, GlvWidget_base::GlvWidgetConnector* _widget_connector) {
        /*! Apply connections of the associated widget (first two arguments of QObject::connect). Necessary for GlvParametrizationWidget.*/
        QObject::connect(_widget, SIGNAL(valueChanged(int)), _widget_connector, SLOT(valueChanged_slot(int)));
    }
};
```

*Foo* can now be used with *GlvWidget* or *GlvParametrizationWidget* :

```cpp
// Use a simple type widget
GlvWidget<Foo>* widget = new GlvWidget<Foo>;
widget->show();

// Use a parametrization widget
GlvParametrizationWidget<ClassA>* parametrization_widget = new GlvParametrizationWidget<ClassA>;
parametrization_widget->show();
```

More details can be found in [sample001_3.cpp](/src/src_samples/src_sample001_3/sample001_3.cpp).
