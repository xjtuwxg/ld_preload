CC = gcc
LD = ld

%.o: %.c
	$(CC) -fPIC $< -c

sig.so: sig.o
	$(LD) -shared $< -o $@

clean:
	rm *.o *.so
