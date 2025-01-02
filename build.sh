gcc m.c yuv_rgb_tab.c -o m
./m > log
./showbmp.sh &
./showyuv.sh &
