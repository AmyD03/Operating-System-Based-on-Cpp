# Operating-System-Based-on-Cpp
Following the course from https://www.youtube.com/playlist?list=PLHh55M_Kq4OApWScZyPl5HhgsTJS9MZ6M


kernel.cpp ：操作系统的内核部分
loader.s ：为kernel.cpp指明地址等信息、调用加载程序的汇编程序
linker.ld ：连接kernel.o和loader.o并给到kernel.bin
Makefile ：描述整个工程的编译、连接等规则
