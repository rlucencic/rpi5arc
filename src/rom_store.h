#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "arc.h"

#define ROM_MAX_SIZE    ARC_ROM_MAX

/* Load the ROM of `os` into buf (ROM_MAX_SIZE bytes): a file in the machine's
 * roms/ folder (any name) that holds that OS (the boards also read flash
 * partitions). Its size in *size, its version ("RISC OS 3.11 (29 Sep
 * 1992)") in *name.
 */
bool rom_store_load(arc_os_t os, uint8_t *buf, uint32_t *size, const char **name);
