# rpi5arc

An Acorn Archimedes for the Raspberry Pi 5, in a window of its own:
[esp32arc](https://github.com/rlucencic/esp32arc)'s Archimedes (with
esp32emu's ARM2) on the [rpi5emu](https://github.com/rlucencic/rpi5emu)
runtime.

- The A440 (ARM2 at 8 MHz) or the A3020 / A4000 (ARM250 at 12 MHz), MEMC,
  IOC and VIDC, up to 4 MB, Arthur 1.20, RISC OS 2.00 or RISC OS 3.11, two
  floppy drives (ADF, ADL, IMG) and an IDE hard disc (HDF).
- The setup screen (model, system, memory, menu button, sound, the
  drives), the web page for the disc images, the console, as the rest of
  the family.

## Building

See [rpi5emu](https://github.com/rlucencic/rpi5emu#building): esp32emu,
rpi5emu, esp32arc and rpi5arc cloned side by side, then

```sh
cd rpi5arc && cmake -S . -B build -G Ninja && cmake --build build
```

## ROMs

Arthur 1.20's or RISC OS 2.00's (512 KB) or RISC OS 3.11's (2 MB) in the
data folder's `roms/` (`~/rpi5emu/roms`), under any name (esp32arc's:
`arthur120.rom`, `riscos200.rom`, `riscos311.rom`): found by what it holds.
Not part of this repository.

## Running

```sh
build/rpi5arc                                   # the setup screen first
build/rpi5arc -S --choice "System=RISC OS 2.00"
build/rpi5arc game.adf                          # with a disc in :0
```

Disc images live in `~/rpi5emu/floppies/` (shared with rpi5ste and
rpi5ami). The keyboard by position (UK); the mouse after a click in the
window (Select, Menu, Adjust: the menu button on the right or the middle
one, a setup choice).

## Licence

MIT.
