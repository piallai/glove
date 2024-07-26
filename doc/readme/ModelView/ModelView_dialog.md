# Model View

## Dialog

A table view can be turned into a dialog widget using:

```cpp
std:vector< std::vector<float> > > matrix;
//fill matrix

GlvTableDialog< std:vector< std::vector> > > table_dialog(matrix);
```

instead of <code>GlvTableView</code>.

By default, the table dialog is not using delegate widget (see [here](/doc/readme/ModelView/ModelView_widget_editor.md)).

To use delegate widget:

```cpp
GlvTableWidgetDialog< std:vector< std::vector> > > table_dialog(matrix);
```

And to make them persistent:

```cpp
GlvTableWidgetPersistentDialog< std:vector< std::vector> > > table_dialog(matrix);
```

All these three classes are simple aliases.