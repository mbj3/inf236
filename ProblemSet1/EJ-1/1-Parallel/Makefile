CC = gcc
CFLAGS = -Wall -g -D_SVID_SOURCE
TFLAGS = -Wall -g -lpthread

all: ejercicio1P

ejercicio1S: ejercicio1P.o 
	$(CC) $(CFLAGS) -o $@ ejercicio1P.o
	
.PHONY: clean dist run runv

clean:
	rm -f *.o ejercicio1P
dist:
	tar -zcvf G2272_P02_2.tgz *.c *.odt Makefile
run:
	@echo "#Ejecutando ejercicio1S---->"
	./ejercicio1P
	
runv:
	@echo "#Ejecutando ejercicio1S con valgrind---->"
	valgrind --leak-check=full ./ejercicio1P
	
ejercicio1S.o: ejercicio1P.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@