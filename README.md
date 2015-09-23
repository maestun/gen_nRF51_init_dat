# gen_nRF51_init_dat
Tool to generate "init" .dat files, needed when flashing an application into nRF51822-BEACON in DFU mode.
Usage:
  gen_nRF51_init_dat <your_hex_file>

This quick and dirty hack relies the following programs:
- hex2bin ( http://hex2bin.sourceforge.net/ )
- crc-lib ( http://www.lammertbies.nl/comm/info/crc-calculation.html )
