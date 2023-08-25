GPPPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exception -fno-leading-undescore#变量GPPPARAMS为32位
ASPARAMS = --32  #设为32位
LDPARAMS = -melf_i386

objects =   obj/loader.o \
			obj/gdt.o \
			obj/drivers/driver.o\
			obj/hardwarecommunication/port.o \
			obj/hardwarecommunication/interruptstubs.o \
			obj/drivers/keyboard.o \
			obj/drivers/mouse.o \
			obj/kernel.o
			#传入源文件

#.cpp生成.o文件
#传入参数GPPPARAMS
#$@取输出文件,$<取第一个依赖文件
obj/%.O:src/%.cpp
	mkdir -p $(@D)
	gcc $(GPPPARAMS) -o $@ -c $<
#.s生成.o文件
obj/%.o:src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<
#创建mykernel.binwen文件：取决于.ld文件和objects——连接kernel.o和loader.o并给到mykernel.bin
mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)
#安装
install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

//.PHONY是一个伪目标，可以防止在Makefile中定义的只执行命令的目标和工作目录下的实际文件出现名字冲突，另一种是提交执行makefile时的效率
.PHONY: clean
clean:
	rm -rf obj mykernel.bin mykernel.iso
