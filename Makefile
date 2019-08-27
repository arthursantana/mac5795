teste: *.c
	gcc -O2 -Wall *.c -o teste

run: teste
	./teste

.PHONY: clean
clean:
	rm *.o teste -f
