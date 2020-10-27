ASM = rgbasm
LINK = rgblink

%.o: %.asm
	$(ASM) $< -o $@

first: first.o
	$(LINK) first.o -o first.gb

bitop_test: bitop_test.o
	$(LINK) bitop_test.o -o bitop_test.gb

arith_test: arith_test.o
	$(LINK) arith_test.o -o arith_test.gb

first.o:

arith_test.o:

bitop_test.o:

clean:
	rm *.o *.gb || true
