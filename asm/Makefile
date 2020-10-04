ASM = rgbasm
LINK = rgblink

%.o: %.asm
	$(ASM) $< -o $@

first: first.o
	$(LINK) first.o -o first.gb

first.o:

test.o:

hello.o:

clean:
	rm *.o *.gb || true
