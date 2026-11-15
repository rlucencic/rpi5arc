#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "emu/emu.h"
#include "emu/log.h"
#include "rom_store.h"

static const char *TAG = "rom";

static const uint32_t sizes[] = { 512 * 1024, 512 * 1024, 2 * 1024 * 1024 };
static char s_name[64];

static bool is_os(arc_os_t os, const uint8_t *buf)
{
    arc_os_t found;
    return arc_rom_identify(buf, sizes[os], &found, s_name, sizeof(s_name)) != NULL && found == os;
}

/* Any file in the data folder's roms/ of the size that holds the OS
 * (Arthur's images often have a byte too many: those too)
 */
bool rom_store_load(arc_os_t os, uint8_t *buf, uint32_t *size, const char **name)
{
    if ((unsigned)os > ARC_OS_RISCOS3) {
        return false;
    }
    char folder[1200];
    snprintf(folder, sizeof(folder), "%s/roms", emu_data_dir());
    DIR *dir = opendir(folder);
    if (dir == NULL) {
        return false;
    }
    bool ok = false;
    struct dirent *e;
    while (!ok && (e = readdir(dir)) != NULL) {
        char path[1500];
        struct stat st;
        snprintf(path, sizeof(path), "%s/%s", folder, e->d_name);
        if (e->d_name[0] == '.' || stat(path, &st) != 0 || st.st_size < sizes[os] || st.st_size > sizes[os] + 16) {
            continue;
        }
        FILE *f = fopen(path, "rb");
        if (f == NULL) {
            continue;
        }
        ok = fread(buf, 1, sizes[os], f) == sizes[os] && is_os(os, buf);
        fclose(f);
        if (ok) {
            EMU_LOGI(TAG, "ROM from %s", path);
        }
    }
    closedir(dir);
    if (!ok) {
        return false;
    }
    *size = sizes[os];
    *name = s_name;
    return true;
}
