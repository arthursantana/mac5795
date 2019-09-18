teste: *.c
	gcc -ggdb -O3 -Wall *.c -o teste

run: teste
	./teste

.PHONY: clean
clean:
	rm *.o teste -f
