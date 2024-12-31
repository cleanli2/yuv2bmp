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
        int32_t y1, y2, u, v;
        int32_t r1, r2, b1, b2, g1, g2;
        fread(yuv2px, 4, 1, fps);

        printf("i=%d\n", i);
        printf("%02x %02x %02x %02x\n", yuv2px[0], yuv2px[1], yuv2px[2], yuv2px[3]);
        y1=yuv2px[0];
        u=yuv2px[1];
        y2=yuv2px[2];
        v=yuv2px[3];
#if 0
        r1 = y1 + ((360 * (v - 128))>>8) ;
        g1 = y1 - (( ( 88 * (u - 128)  + 184 * (v - 128)) )>>8) ;
        b1 = y1 +((455 * (u - 128))>>8) ;
        r2 = y2 + ((360 * (v - 128))>>8) ;
        g2 = y2 - (( ( 88 * (u - 128)  + 184 * (v - 128)) )>>8) ;
        b2 = y2 +((455 * (u - 128))>>8) ;
#endif
        /*
        r1=0x00;
        g1=0x00;
        b1=0xff;
        r2=0x00;
        g2=0x00;
        b2=0xff;
        */
#if 0
        if(y1<16)y1=16;
        if(y2<16)y2=16;
        if(y1>235)y1=235;
        if(y2>235)y2=235;
        if(u<16)u=16;
        if(v<16)v=16;
        if(u>235)u=235;
        if(v>235)v=235;
        b1=(1164*(y1-16)+2018*(u-128))/1000;
        r1=(1164*(y1-16)+1596*(v-128))/1000;
        g1=(1164*(y1-16)-813*(v-128)-391*(u-128))/1000;
        b2=(1164*(y2-16)+2018*(u-128))/1000;
        r2=(1164*(y2-16)+1596*(v-128))/1000;
        g2=(1164*(y2-16)-813*(v-128)-391*(u-128))/1000;
#endif
#if 0
        b1=y1+1770*(u-128)/1000;
        g1=y1-(343*(u-128)+714*(v-128))/1000;
        r1=y1+1403*(v-128)/1000;
        b2=y2+1770*(u-128)/1000;
        g2=y2-(343*(u-128)+714*(v-128))/1000;
        r2=y2+1403*(v-128)/1000;
#endif
#if 1
        r1=y1+14075*(v-128)/10000;
        g1=y1-3455*(u-128)/10000-7169*(v-128)/10000;
        b1=y1+1779*(u-128)/1000;
        r2=y2+14075*(v-128)/10000;
        g2=y2-3455*(u-128)/10000-7169*(v-128)/10000;
        b2=y2+1779*(u-128)/1000;
#endif
        if(b1>255)b1=255;
        if(g1>255)g1=255;
        if(r1>255)r1=255;
        if(b2>255)b2=255;
        if(g2>255)g2=255;
        if(r2>255)r2=255;
        bmp2px[0]=b1;
        bmp2px[1]=g1;
        bmp2px[2]=r1;
        bmp2px[3]=b2;
        bmp2px[4]=g2;
        bmp2px[5]=r2;
        printf("%02x %02x %02x %02x %02x %02x\n", bmp2px[0], bmp2px[1], bmp2px[2], bmp2px[3], bmp2px[4], bmp2px[5]);
        fwrite(bmp2px, 6, 1, fpd);
    }
    //fwrite("hello world", 10, 1, fps);
    fclose(fps);
    fclose(fpd);
    return 0;
}
