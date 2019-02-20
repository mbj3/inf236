CC = gcc
CFLAGS = -Wall -g -D_SVID_SOURCE -lm
TFLAGS = -Wall -g -lpthreadc

all: Cellular2D-Secuential

Cellular2D-Secuential: Cellular2D-Secuential.o 
	$(CC) $(CFLAGS) -o $@ Cellular2D-Secuential.o
	
.PHONY: clean dist run runv

clean:
	rm -f *.o Cellular2D-Secuential
dist:
	tar -zcvf G2272_P02_2.tgz *.c *.odt Makefile
run:
	@echo "#Ejecutando ejerCellular2D-Secuential---->"
	./Cellular2D-Secuential 
	
runv:
	@echo "#Ejecutando Cellular2D-Secuential con valgrind---->"
	valgrind --leak-check=full ./Cellular2D-Secuential
	
Cellular2D-Secuential.o: Cellular2D-Secuential.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@