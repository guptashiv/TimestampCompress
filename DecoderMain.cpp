#include "MyOnlineDecoder.h"
#include<ctime>
using namespace std;

int main()
{
	MyOnlineDecoder *decoder = new MyOnlineDecoder();
	// int start_s=clock();
	decoder->parseAndDecode("myEncoded.bin", "myTimestamps");
	// int stop_s=clock();
	// cout << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

	delete(decoder);
	return 0;
}