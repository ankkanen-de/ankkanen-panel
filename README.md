# ankkanen-panel

A panel and taskbar for Ankkanen implemented using QtWidgets. It can be used with any wayland compositor supporting wlr-layer-shell and wlr-foreign-toplevel-management. The client implementation of wlr-foreign-toplevel-management can be found [here](https://github.com/ankkanen-de/qt6-foreign-toplevel-management).

## Building and installing

```
mkdir build
cd build
cmake ..
make
sudo make install
```
