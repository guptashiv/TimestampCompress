Devices scanning forever for the timestamps, in order to keep the data/system Recoverable, stamps a zillion of timestamps.

Considering that timestamps are 32 bit numbers, sending an ASCII file of timestamps, gets very very frustrating.
Compressing such files with known info to binary file can reduce the space almost to log times. (But remember, extracting the file ERRORFREE is a constraint never to be forgotten.)

This is an implimentation of such encoding, filenames are self explanatory.

make* files contain the scripts for running this first-hand, without watching any code. But make sure you change the file-permissions appropriately.


Algorithm metadata:
	Compression Algo:
		1. Store first timestamp as Base
		2. then, store all the differences depending on following
		   "1 <7-bits>" if difference is less then 2^7
		   "01<14 bits>" if it's between 2^7 to 2 ^14
		   "001<21 bits>" if it's between 2^14 and 2^21... and so on
		*the position of first '1' will tell the number of bytes to consider for decoding
		3. from the TempFile now read 1 byte at a time and write it on a Binary File.


	Decoding Algo:
      		1. read base just once (first 8-bytes), store it in lastNum
      		2. read a byte
         		if(it starts with 1), convert it to diff by subtracting (2^7)
         		if(it starts with 01), take 2 bytes and subtract 2^14
		         if(it starts with 001) take 3 bytes and subtract 2^21
		         so on...
		3. update lastNum by adding the diff
      		4. convert back to Double
      		5. print double(lastnum)



Complexity:
	Encoding: O(n), where n is the size of file to be encoded.
	   It is evident since we are scanning through the input file and without processing any other information, compressing it on-line.

	Decoding: O(n)
	   Again, the similar explanation. 

just to run and check, run this on the terminal
|----------------------------------------------------------------------|

|  chmod +x makeDecode && chmod +x makeCompress						   |

| ./makeCompress  && ./makeDecode && diff testTimestamps timestamps    |

|----------------------------------------------------------------------|


Details:

> MyOnlineCoder.h and MyOnlineDecoder.h files are the declarations.
> .cpps of above implement the Comression and Extraction logic

> CoderMain.cpp uses MyOnlineCoder::parseAndEncode() to convert <infile> to <encodedFile>
	** obj->parseAndEncode(infile, encodedFile); 

> DecoderMain.cpp uses MyOnlineDecoder::parseAndDecode() to convert <encodedFile> to <newTimestamps> file
	** obj->parseAndDecode(encodedFile, newTimestampsFile);

> makeCompress is a script for linking and then running the output file for COMPRESSION.

> makeDecode is for Decoding

> valgrind takes a bit of extra time to complete, because of numerous i/o ops.
> but can be activated by uncommenting the lines inside makeCompress and mkaeDecode files


sample output for following with vagrind:
$ ./makeCompress  && ./makeDecode && diff testTimestamps timestamps

==11440== Memcheck, a memory error detector
==11440== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==11440== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==11440== Command: ./encoder
==11440== 
==11440== 
==11440== HEAP SUMMARY:
==11440==     in use at exit: 0 bytes in 0 blocks
==11440==   total heap usage: 1,636,556 allocs, 1,636,556 frees, 67,133,460 bytes allocated
==11440== 
==11440== All heap blocks were freed -- no leaks are possible
==11440== 
==11440== For counts of detected and suppressed errors, rerun with: -v
==11440== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==12919== Memcheck, a memory error detector
==12919== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==12919== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==12919== Command: ./decoder
==12919== 
==12919== 
==12919== HEAP SUMMARY:
==12919==     in use at exit: 0 bytes in 0 blocks
==12919==   total heap usage: 451,214 allocs, 451,214 frees, 14,907,418 bytes allocated
==12919== 
==12919== All heap blocks were freed -- no leaks are possible
==12919== 
==12919== For counts of detected and suppressed errors, rerun with: -v
==12919== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

$ diff testTimestamps timestamps 
<shows nothing>

compression ratio = (734126*8)/451211 = 13.016101 bits/timestamp

*Statistics can be found on metrics.txt
