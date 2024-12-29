#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>

unsigned char bmphd[] = {
  0x42, 0x4d, 0x36, 0x10, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00,
  0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0xe0, 0x01,
  0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
int main()
{
    uint8_t yuv2px[4], bmp2px[6], head[54];
    const char *filename = "test/testfile";
    FILE *fps = fopen("s.bin", "rb");
    if (!fps){
        printf("Open file s.bin fail, error code %d, error message: %s\n",
                errno, strerror(errno));
        return -1;
    }
    FILE *fpd = fopen("d.bmp", "wb");
    if (!fpd){
        printf("Open file d.bmp fail, error code %d, error message: %s\n",
                errno, strerror(errno));
        return -1;
    }

    fwrite(bmphd, 54, 1, fpd);
    for(int i=0;i<640*480/2;i++){
        uint8_t y1, y2, u, v;
        uint8_t r1, r2, b1, b2, g1, g2;
        fread(yuv2px, 4, 1, fps);

        printf("i=%d\n", i);
        printf("%02x %02x %02x %02x\n", yuv2px[0], yuv2px[1], yuv2px[2], yuv2px[3]);
        y1=yuv2px[0];
        u=yuv2px[1];
        y2=yuv2px[2];
        v=yuv2px[3];
        r1 = y1 + ((360 * (v - 128))>>8) ;
        g1 = y1 - (( ( 88 * (u - 128)  + 184 * (v - 128)) )>>8) ;
        b1 = y1 +((455 * (u - 128))>>8) ;
        r2 = y2 + ((360 * (v - 128))>>8) ;
        g2 = y2 - (( ( 88 * (u - 128)  + 184 * (v - 128)) )>>8) ;
        b2 = y2 +((455 * (u - 128))>>8) ;
        bmp2px[0]=r1;
        bmp2px[1]=g1;
        bmp2px[2]=b1;
        bmp2px[3]=r2;
        bmp2px[4]=g2;
        bmp2px[5]=b2;
        printf("%02x %02x %02x %02x %02x %02x\n", bmp2px[0], bmp2px[1], bmp2px[2], bmp2px[3], bmp2px[4], bmp2px[5]);
        fwrite(bmp2px, 6, 1, fpd);
    }
    //fwrite("hello world", 10, 1, fps);
    fclose(fps);
    fclose(fpd);
    return 0;
}
