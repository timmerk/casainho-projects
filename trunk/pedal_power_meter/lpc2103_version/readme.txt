1. Open Debug dialog 

2. Goto 'Main' tab. In 'Project' area type name of your project. In 'C/C++ Application' area type path to your 
	project executable (for example: C:\gccfd\projects\lpc2138\main.out)

2. Goto 'Debugger' tab and GDB debugger area set path to :
	 C:\gccfd\yagarto\bin\arm-elf-gdb.exe

3. Goto 'Commands' tab and in 'Run commands' area paste:

	target remote localhost:3333
	monitor sleep 500
	monitor poll
	monitor flash probe 0
	monitor flash erase 0 0 0
	monitor flash write 0 main.bin 0x0
	monitor reset run
	monitor sleep 500
	monitor soft_reset_halt
	monitor arm7_9 force_hw_bkpts enable
	symbol-file main.out	
	thbreak main
	continue


	