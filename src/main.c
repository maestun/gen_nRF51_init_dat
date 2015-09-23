//
//  main.c
//  gen_nRF51_init_dat
//
//  Created by developer on 23/09/2015.
//  Copyright (c) 2015 maestun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hex2bin.h"
#include "common.h"
#include "tst_crc.h"

#define PROGRAM     "gen_nRF51_init_dat"
#define VERSION     "0.1"

unsigned char DEFAULT_DATA[] = {
    0xff, 0xff,                // device type
    0xff, 0xff,                // device revision
    0xff, 0xff, 0xff, 0xff,    // app version
    0x01, 0x00,                // soft devices list lenght (in Big Endian format)
    0xfe, 0xff,                // soft devices list, 2 bytes per soft device, '0xfeff' is all devices
    0x00, 0x00,                // CRC checksum, must be computed
};


int main(int argc, char * argv[]) {

    fprintf (stdout, "\n"PROGRAM" v"VERSION"\n\n");
    if(argc < 2) {
        fprintf(stdout, "%s\n\n", "Please specify a HEX input file.");
        exit(0);
    }

    char * input = argv[1];

    
    // produce .bin file from .hex file
    hex2bin(input);
    
    
    // get CRC-CCITT (0xffff seed) of .bin file
    PutExtension(input, "bin");

    unsigned short ccitt_0xffff = crc_main(input);

    
    // update default data
    unsigned char lobyte = ccitt_0xffff & 0xff;
    unsigned char hibyte = (ccitt_0xffff & 0xff00) >> 8;
    DEFAULT_DATA[sizeof(DEFAULT_DATA) - 2] = lobyte;
    DEFAULT_DATA[sizeof(DEFAULT_DATA) - 1] = hibyte;

    
    // write to .dat init file
    int data_len = sizeof(DEFAULT_DATA) / sizeof(DEFAULT_DATA[0]);
    //char fname[256] = "";
    //sprintf(fname, "%s.dat", input);
    PutExtension(input, "dat");
    FILE * fptr = fopen(input, "wb");
    for(int idx = 0; idx < data_len; idx++) {
        fputc(DEFAULT_DATA[idx], fptr);
    }
    fclose(fptr);
    
    
    printf("Done.\n");
    return 0;
}
