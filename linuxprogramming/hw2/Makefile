main:	task4_main.o logic.o
	gcc -o main task4_main.o logic.o

task4_main.o:	task4_main.c logic.h sensor.h
	gcc -c task4_main.c 

logic.o: logic.c logic.h
	gcc -c logic.c
