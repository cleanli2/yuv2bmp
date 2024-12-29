#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>

int main()
{
    const char *filename = "test/testfile";
    FILE *fp = fopen(filename, "wb");
    if (!fp){
        printf("Open file %s fail, error code %d, error message: %s\n",
                filename, errno, strerror(errno));
        return -1;
    }

    fwrite("hello world", 10, 1, fp);
    fclose(fp);
    return 0;
}
