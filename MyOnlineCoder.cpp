/*	Designed and Implemented by ShivGupta
*/

#include"MyOnlineCoder.h"

using namespace std;

/*
	Compression Algo:
		1. Store first timestamp as Base
		2. then, store all the differences depending on following
		   "1 <7-bits>" if difference is less then 2^7
		   "01<14 bits>" if it's between 2^7 to 2 ^14
		   "001<21 bits>" if it's between 2^14 and 2^21... and so on
		*the position of first '1' will tell the number of bytes to consider for decoding
		3. from the TempFile now read 1 byte at a time and write it on a Binary File.
*/
void MyOnlineCoder::parseAndEncode(const char* infile, const char* outputFile)
{
	ifstream in;
	in.open(infile);

	const char* tempfile = "intermediateFile";

	ofstream out;
	out.open(tempfile, ios::binary);

	double n;
	long long lastnum;
	long long num;
	in>>n;
	
	//converting double to ull (e.g., 1364281200.078739 to 1364281200078739) for ease
	lastnum = n * 1000000;  
	
	bitset<64> base = bitset<64>(lastnum);
	
	//store base as it is
	out<<base; 		
	while(in >> n)
	{
		num = n*1000000;
		long long dif = num - lastnum;
		lastnum = num;
		// the first '1' in current byte will show the number of bytes to calculate diff
		// hence 1<7-bits> for 1 byte
		// 01<14-bits> for 2 bytes
		// 001<21-bits> for 3 bytes and so on
		if(dif < (1<<7) )
		{
			dif += (1<<7);
			bitset<8> diff = bitset<8>(dif);
			out<<diff;
		}
		else if(dif < (1<<14))
		{
			dif += (1<<14);
			bitset<16> diff = bitset<16>(dif);
			out<<diff;
		}
		else if(dif < (1<<21))
		{
			dif += (1<<21);
			bitset<24> diff = bitset<24>(dif);
			out<<diff;
		}
		else if(dif < (1<<28))
		{
			dif += (1<<28);
			bitset<32> diff = bitset<32>(dif);
			out<<diff;
		}		
		else if(dif < (1LL<<35))
		{
			dif += (1LL<<35);
			bitset<40> diff = bitset<40>(dif);
			out<<diff;         
		}
	}
	in.close();
	out.close();

	//from the tempFile take 1-byte and 
	//write it to a binary file as an unsigned char

	bitset<8> byteToWrite;
	in.open(tempfile);
	out.open(outputFile, ios::binary);
	while(in >> byteToWrite)
	{
		unsigned long temp = byteToWrite.to_ulong();
		unsigned char ch = static_cast<unsigned char>(temp);
		out<<ch;
	}
	in.close();
	out.close();
	//remove the tempfile
	remove(tempfile);
}