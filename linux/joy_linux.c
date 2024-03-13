#include <dirent.h> 
#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <linux/input.h>

const char *lin_SearchPath = "/dev/input";

bool lin_IsGamepad(const char *path) {
    // Open the path
    FILE *file = fopen(path, "r");

    if (!file)
        return false;

    int fd = fileno(file);

    // We should have a descriptor, but it's always good to check.
    if (fd == -1)
        goto retfalse;

    struct input_id id;

    if (ioctl(fd, EVIOCGID, &id) == -1)
        goto retfalse;

    if (id.bustype != BUS_USB && id.bustype != BUS_BLUETOOTH)
        goto retfalse;

    if (id.vendor != 0x045e || id.product != 0x028e) // Xbox 360 Controller
        goto retfalse;

    fclose(file);
    return true;

retfalse:
    fclose(file);
    return false;
}

void lin_EnumerateDevices() {
    DIR *d;
    struct dirent *dir;
    d = opendir(lin_SearchPath);
    size_t len = strlen(lin_SearchPath);

    if (!d)
        return;

    while ((dir = readdir(d))) {
        // Ignore parent and current dirs
        if (!strcmp(dir->d_name, "."))
            continue;
        if (!strcmp(dir->d_name, ".."))
            continue;
        // Calculate the length of the full name
        size_t dirlen = strlen(dir->d_name);
        size_t size = (len+dirlen+2);
        // Allocate a string of the length of the full name
        char *filename = malloc(size);
        if (filename == NULL) 
            continue;
        // Concat the paths
        sprintf(filename, "%s/%s", lin_SearchPath, dir->d_name);

        if (!lin_IsGamepad(filename))
            goto freecontinue;

        printf("%s\n", dir->d_name);

    freecontinue:
        // Free the path
        free(filename);
    }
    closedir(d);
}
