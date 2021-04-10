# truncated-cube-lamp

Testing a cool idea for a lamp

## Build

Get, make and install [QtHttpServer](https://code.qt.io/qt-extensions/qthttpserver.git).

Qt 6 doesn't detect its code build tools,
and HttpServer needs to be manually specified if you use a different install prefix:

```bash
mkdir build && cd build
cmake .. \
  -DQt6_DIR=~/Qt/6.1.0/gcc_64/lib/cmake/Qt6/ \
  -DQt6CoreTools_DIR=/home/mercotui/Qt/6.1.0/gcc_64/lib/cmake/Qt6CoreTools \
  -DQt6QmlTools_DIR=/home/mercotui/Qt/6.1.0/gcc_64/lib/cmake/Qt6QmlTools \
  -DQt6GuiTools_DIR=/home/mercotui/Qt/6.1.0/gcc_64/lib/cmake/Qt6GuiTools
make -j 8
```
