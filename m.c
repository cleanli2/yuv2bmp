#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>

int main()
{
    uint8_t yuv2px[4], bmp2px[6];
    const char *filename = "test/testfile";
    FILE *fps = fopen("s.bin", "rb");
    if (!fps){
        printf("Open file s.bin fail, error code %d, error message: %s\n",
                errno, strerror(errno));
        return -1;
    }
    FILE *fpd = fopen("d.bmp", "rb");
    if (!fpd){
        printf("Open file d.bmp fail, error code %d, error message: %s\n",
                errno, strerror(errno));
        return -1;
    }

    for(int i=0;i<640*480/2;i++){
        fread(yuv2px, 4, 1, fps);
        fread(bmp2px, 6, 1, fpd);

        printf("i=%d\n", i);
        printf("%02x %02x %02x %02x\n", yuv2px[0], yuv2px[1], yuv2px[2], yuv2px[3]);
        printf("%02x %02x %02x %02x %02x %02x\n", bmp2px[0], bmp2px[1], bmp2px[2], bmp2px[3], bmp2px[4], bmp2px[5]);
    }
    //fwrite("hello world", 10, 1, fps);
    fclose(fps);
    fclose(fpd);
    return 0;
}
