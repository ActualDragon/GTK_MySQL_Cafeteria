Pfinal.out: Pfinal.c
	gcc -g -Wall -o Pfinal.out Pfinal.c `pkg-config --cflags --libs gtk+-2.0` -lnsl -lm -lz -lmysqlclient

Pfinal.o: Pfinal.c
	gcc -c Pfinal.c

clean:
	rm *.o