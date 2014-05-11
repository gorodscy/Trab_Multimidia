all:
	gcc -Wall -ansi main.c -o main

compress:
	./main 0 images/image512x512.bmp image.bin

decompress:
	./main 1 image.bin output_image.bmp