# rpi5arc: the Acorn Archimedes on the Raspberry Pi 5

esp32arc's Archimedes (`../esp32arc/components/archimedes`, platform
independent) on the rpi5emu runtime (`../rpi5emu`, its CLAUDE.md: the
workflow, the Pi, the lessons), the ARM2 esp32emu's. The machine's own
behaviour, lessons and tests are esp32arc's CLAUDE.md; this project is the
glue.

## Layout

| Path | What |
|---|---|
| `src/main.c` | The Archimedes as an `emu_machine_t`: esp32arc's `main/main.c` through `../rpi5emu/tools/port_glue.py` and `port_finish.py`, then by hand: RAM and ROM on ARM2 pages by `posix_memalign()`, the picture copier a thread (a semaphore for the task notification), the console's `C` frame timing in nanoseconds (reported as a 1 GHz clock's cycles), the ROM message, `shutdown()` saves the CMOS RAM and writes the discs back |
| `src/settings.c` | esp32arc's, over `emu/nvs.h` (section `arc`, each model's and OS's CMOS RAM as hex) |
| `src/rom_store.c` | A file in `~/rpi5emu/arc/roms/` (`emu_rom_dir()`) of the OS's ROM size (or up to 16 bytes more: Arthur's images) that holds it (any name) |

Keep `src/main.c` in step with esp32arc's `main/main.c`.

## Build, run, check

```sh
../rpi5emu/tools/pi.sh rpi5arc build
../rpi5emu/tools/pi.sh rpi5arc headless     # or run: the window here
../rpi5emu/tools/console.sh i c
../rpi5emu/tools/pi.sh rpi5arc shot out.png
```

Console: the runtime's (`h`) and esp32arc's: `k <hex>` tap a key (47
Return), `K <hex> 0|1`, `m <dx> <dy> <btn>` (1 Select, 2 Menu, 4 Adjust),
`P <x> <y> <btn>`, `T <text>`, `R <os> <KB> [model]`, `C [n|stop]` frame
timing.

Checked on the Pi (2026-11-15, headless): the A440 (4 MB) with RISC OS
3.11 at 100% to its desktop and icon bar (~20 s), RISC OS 2.00 to its
desktop. Not yet: Arthur, the A3020, discs (none here), the window by hand,
sound heard, the mouse.
