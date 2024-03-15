A cross platform low-level joypad library.

Uses GCC for Linux and MinGW for Windows.

## TODO

### Common

- Joypad mappings
    - Maybe support SDL mappings
- Common button / axis names
- Expose joypad vendor / model
- Expose joypad name
- Pump events and respond to changes

### Linux

- Open and store file pointers for joypads
- Read events
- Support both jsdev and evdev joypads

### Windows

- I don't use windows, will figure out what's needed after linux impl.

### WebAssembly

- Determine if webassembly support is worth the hassle
