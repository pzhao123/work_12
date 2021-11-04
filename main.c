#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int dirinfo(char * path) {
    DIR * dir = opendir(path);
    if (!dir) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    } 
    struct dirent *file = readdir(dir);
    struct stat info;
    int size = 0;
    printf("Statistics for directory: %s\nDirectories: \n", path);
    while (file) {
        stat(file->d_name, &info);
        size += (info.st_size);
        if (file->d_type == DT_DIR) {
            printf("\t%s\n", file->d_name);
        }
        file = readdir(dir);
    }
    rewinddir(dir);
    file = readdir(dir);
    printf("Regular Files:\n");
    while (file) {
        stat(file->d_name, &info);
        if (file->d_type == DT_REG) {
            printf("\t%s\n", file->d_name);
        }
        file = readdir(dir);
    }
    printf("Total size: %f KB\n", size / 1000.0);
    closedir(dir);
    return 0;
}

int main(int argc, char *argv[]) {
    char path[200];
    if (argc <= 1) {
        printf("Enter a directory to scan: ");
        scanf("%s", path);
        dirinfo(path);
    }
    else {
        dirinfo(argv[1]);
    }
    return 0;
}