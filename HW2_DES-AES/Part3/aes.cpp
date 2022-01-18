// Class: 1101 密碼學概論 曾文貴
// Author: 陳品劭 109550206
// Date: 20211019
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

int main() {
	ofstream out("aes-out.txt", ios::out);

	//byte key[] = "1234567890ABCDEF";
	//string txt = "Hello World!";

	byte key[] = "keyis84932731830";
	string txt = "AES is the US block cipher standard.";

	const byte IV0[] = "0000000000000000";
	const byte IV9[] = "9999999999999999";
	
	string output;

	AESEncryption aesencry(key, 16);
	CFB_Mode_ExternalCipher::Encryption cfb(aesencry, IV0, 4);
	StreamTransformationFilter CFB(cfb, new StringSink(output), StreamTransformationFilter::NO_PADDING);
	CFB.Put(reinterpret_cast<const unsigned char*>(txt.c_str()), txt.length());
	CFB.MessageEnd();
	for(byte x : output){
		out << setfill('0') << setw(2) << hex << int(x) << " ";
	}
	out << '\n';
	output.clear();

	CBC_Mode<AES>::Encryption cbc0(key, 16, IV0);
	StreamTransformationFilter CBC0(cbc0, new StringSink(output), StreamTransformationFilter::ZEROS_PADDING);
	CBC0.Put(reinterpret_cast<const unsigned char*>(txt.c_str()), txt.length());
	CBC0.MessageEnd();
	for(byte x : output){
		out << setfill('0') << setw(2) << hex << int(x) << " ";
	}
	out << '\n';
	output.clear();

	CBC_Mode<AES>::Encryption cbc9(key, 16, IV9);
	StreamTransformationFilter CBC9(cbc9, new StringSink(output), StreamTransformationFilter::PKCS_PADDING);
	CBC9.Put(reinterpret_cast<const unsigned char*>(txt.c_str()), txt.length());
	CBC9.MessageEnd();
	for(byte x : output){
		out << setfill('0') << setw(2) << hex << int(x) << " ";
	}
	out << '\n';
	output.clear();

	ECB_Mode<AES>::Encryption ecb(key, 16);
	StreamTransformationFilter ECB(ecb, new StringSink(output), StreamTransformationFilter::PKCS_PADDING);
	ECB.Put(reinterpret_cast<const unsigned char*>(txt.c_str()), txt.length());
	ECB.MessageEnd();
	for(byte x : output){
		out << setfill('0') << setw(2) << hex << int(x) << " ";
	}
	out << '\n';
	output.clear();

	return 0;
}