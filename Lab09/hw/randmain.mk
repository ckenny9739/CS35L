randmain: randmain.o randcpuid.o randlibhw.so randlibsw.so
	$(CC) $(CFLAGS) randmain.o randcpuid.o -ldl -Wl,-rpath=$(PWD) -o randmain

randlibhw.so: randlibhw.o
	$(CC) $(CFLAGS) -shared randlibhw.c -fPIC -o randlibhw.o -o randlibhw.so

randlibsw.so: randlibsw.o
	$(CC) $(CFLAGS)	-shared randlibsw.c -fPIC -o randlibsw.o -o randlibsw.so
