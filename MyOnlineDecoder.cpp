#include "MyOnlineDecoder.h"
using namespace std;

#define ull unsigned long long

/*
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

*/

void MyOnlineDecoder::parseAndDecode(const char* inputFile, const char* outputFile)
{
   ofstream out;
   out.open(outputFile);

   ifstream in;
   in.open(inputFile, ios::binary);
   
   unsigned char n;
   ull base = 0;
   for(int i=0;i<8;i++)
   {
      //calculating First Timestamp
      n = in.get();      
      base += long (int(n))<<(8*(7-i));
   }
   ull lastnum = base;
   
   double res = lastnum*(.000001);
   out<<fixed<<setprecision(6)<<res<<endl;

   n = in.get();
   while(in)
   {
         bitset<8>firstByte = bitset<8>(n);
         // bitset indexing is done right to left
         // hence for the conventional iteration (left to right) convert it to string
         string firstByteString = firstByte.to_string(); 
         unsigned short bytes = 1;

         //calculate position of first '1'
         while(firstByteString[bytes-1]!='1')
         {           
            bytes++;          
         }
         
         ull diff = 0LL;
         //read more bytes if needed
         for(int i=0;i<bytes;i++)
         {
            diff += long(n)<<(8*(bytes-i-1));

            n = in.get();
            firstByte = bitset<8>(n);            
         }

         // subtract the identifier we added while Encoding
         //2^7 for 1-byte difference, 2^14 for 2 bytes, 2^21 for 3-byte and so on
         diff -= 1LL<<(8*(bytes)-(bytes));
         
         //update lastNum
         lastnum  += diff;
         
         //convert back to double
         res = lastnum *(0.000001);
         out<<fixed<<setprecision(6)<<res<<endl;
   }
   in.close();
   out.close();
}