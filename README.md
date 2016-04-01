# mouse-device-driver
Simple mouse device driver that increases brightness on right click and decreases the same on left click

Steps for running Mouse Driver(needs root access):

1. mknod /dev/ourDev c 90 1 
 
2. chmod a+r+w /dev/ourDev

3. Go to the directory that contains the source code. 

4. make

5. insmod mouse.ko

6. gcc test.c -o test

7. ./test 

