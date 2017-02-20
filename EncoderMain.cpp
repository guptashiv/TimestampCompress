#include "MyOnlineCoder.h"
#include<ctime>
using namespace std;
#define ll long long

int main()
{
   	MyOnlineCoder *encoder = new MyOnlineCoder();
	// int start_s=clock();
    encoder->parseAndEncode("timestamps", "myEncoded.bin");
	// int stop_s=clock();
	// cout << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

    delete(encoder);
}