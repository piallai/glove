# [GlvOpenFile](/src/src_glove/GlvOpenFile.h)

![GlvOpenFile](../images/widgets/GlvOpenFile.png)

Widget designed for opening a file either in read or write mode. The right button can be toggled to change the mode. The mention *Ok* is greyed if the file does not exist. The path of the file can be modified directly in the left entry.

When used as a parameter, an empty field does not return and invalid warning. The reason is in some cases where multiple file paths are not required in the parametrization, it would return unnecessary invalidity. One can simply set a default value such as *"."* to enforce validity check.
