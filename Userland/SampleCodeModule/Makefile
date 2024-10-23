include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES_C=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard [^_]*.asm)
OBJECTS_C=$(SOURCES_C:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

all: $(MODULE)

# Regla para crear el binario final a partir de archivos C y ASM
$(MODULE): $(OBJECTS_C) $(OBJECTS_ASM) _loader.o
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.o $(OBJECTS_C) $(OBJECTS_ASM) -o ../$(MODULE)

# Regla para compilar archivos .c a .o
%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

# Regla para compilar archivos .asm a .o
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o

.PHONY: all clean print