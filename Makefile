all:
	gcc -Wall -ansi main.c -o main

compress:
	./main 0 images/image8x8.bmp image.bin

decompress:
	./main 1 image.bin output_image.bmp