CC = gcc
CFLAGS = -Wall -g -D_SVID_SOURCE
TFLAGS = -Wall -g -lpthread

all: ejercicio1S

ejercicio1S: ejercicio1S.o 
	$(CC) $(CFLAGS) -o $@ ejercicio1S.o
	
.PHONY: clean dist run runv

clean:
	rm -f *.o ejercicio1S
dist:
	tar -zcvf G2272_P02_2.tgz *.c *.odt Makefile
run:
	@echo "#Ejecutando ejercicio1S---->"
	./ejercicio1S 
	
runv:
	@echo "#Ejecutando ejercicio1S con valgrind---->"
	valgrind --leak-check=full ./ejercicio1S
	
ejercicio1S.o: ejercicio1S.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@