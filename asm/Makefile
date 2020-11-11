ASM = rgbasm
LINK = rgblink
BIN = first bitop_test arith_test ld_test

%.o: %.asm
	$(ASM) $< -o $@

all: $(BIN)

first: first.o
	$(LINK) first.o -o first.gb

arith_test: arith_test.o
	$(LINK) arith_test.o -o arith_test.gb

bitop_test: bitop_test.o
	$(LINK) bitop_test.o -o bitop_test.gb

ld_test: ld_test.o
	$(LINK) ld_test.o -o ld_test.gb

jump_test: jump_test.o
	$(LINK) jump_test.o -o jump_test.gb

stack_test: stack_test.o 
	$(LINK) stack_test.o -o stack_test.gb

first.o:

arith_test.o:

bitop_test.o:

jump_test.o:

stack_test.o:

ld_test.o:
	$(ASM) ld_test.asm -L -o ld_test.o

clean:
	rm *.o *.gb || true
