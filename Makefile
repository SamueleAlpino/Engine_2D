CC=clang
CPPCHECK=Cppcheck
CFLAGS= -Wall  -O3 -ID:\Sam\Convert_point\header -ID:\Sam\Convert_point\SDL2-2.0.9\include -ID:\Sam\Convert_point\stb-master -Wno-pragma-pack #-Werror
BINARY= utils
BINARY_TESTS=utils_tests
LDFLAGS  = -lSDL2 -L.

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

convert_point: src/main.o src/utils.o
	$(CC) -o $(BINARY)  $(LDFLAGS) $^

main.o: src/main.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

utils.o: src/utils.c header/utils.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

tests.o: src/tests.c header/aiv_unit_test.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

test: src/tests.o src/utils.o #every .o to test
	$(CC) -o $(BINARY_TESTS)  $(LDFLAGS) $^
	./$(BINARY_TESTS)

clean: 
	rm -f *.o 