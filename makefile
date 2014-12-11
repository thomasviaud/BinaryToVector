CC = gcc
CCFLAGS = -Wall -lX11

all: img_bin


bmp_worker.o: bmp_worker.c makefile
	$(CC) $(CCFLAGS) -c bmp_worker.c

main.o: main.c makefile
	$(CC) $(CCFLAGS) -c main.c

img_bin: main.o bmp_worker.o makefile
	$(CC) $(CCFLAGS) -o img_bin main.o bmp_worker.o

clean:
	rm *.o 
