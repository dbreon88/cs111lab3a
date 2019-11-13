#NAME: Dylan Breon
#EMAIL: dbreon@ucla.edu
#ID: 905187210

main: clean lab3a.c
	gcc -o lab3a lab3a.c -Wall -g -Wextra -pedantic
clean:
	rm -f lab3a lab3a-905187210.tar.gz
dist:	
	tar -czvf lab3a-905187210.tar.gz Makefile README lab3a.c ext2_fs.h
