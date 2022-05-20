# unicode_UTF-8_UTF-16_converter
Convert UTF-8 encoded data to UTF-16 and vice versa 

Implementation examples:
1) ./utf16to8 < elytis_mon_16.txt
2) ./utf16to8 < elytis_pol_16.txt
3) ./utf16to8 < elytis_mon_16.txt > elytis_mon_8_new.txt 

After given command in implementation 3, type:
 cmp elytis_mon_8_new.txt elytis_mon_8.txt (so as to check that there are not any differences between the 2 files)
