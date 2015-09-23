# Makefile

CPFLAGS = -std=c99 -O2 -Wall -pedantic

# Compile
%o : %c
	gcc -c $(CPFLAGS) $< -o $@

INSTALL_DIR = /usr/local
MAN_DIR = $(INSTALL_DIR)/man/man1

all: gen_nRF51_init_dat

gen_nRF51_init_dat: src/main.o src/lib_crc.o src/tst_crc.o src/binary.o src/common.o src/hex2bin.o src/libcrc.o
	gcc -O2 -Wall -o gen_nRF51_init_dat src/main.o src/lib_crc.o src/tst_crc.o src/binary.o src/common.o src/hex2bin.o src/libcrc.o

# install:
#	strip hex2bin
#	strip mot2bin
#	cp hex2bin mot2bin $(INSTALL_DIR)/bin
#	cp hex2bin.1 $(MAN_DIR)

clean:
	rm src/*.o gen_nRF51_init_dat
