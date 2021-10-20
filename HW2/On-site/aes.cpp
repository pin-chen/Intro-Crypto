#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

int main() {

	byte key[] = "0000000000000000";
	byte cipher[] = "ac45d78068c2bd87c3f50dec9f898260";
	const byte IV0[] = "0000000000000000";

	string sink;

	HexDecoder decoder;
	decoder.Attach(new StringSink(sink));
	decoder.Put(cipher, sizeof(cipher));
	decoder.MessageEnd();
	
	string output;
	for (char i = '0'; i <= '9'; i++) {
		for (char j = '0'; j <= '9'; j++) {
			key[0] = i;
			key[1] = j;
			CBC_Mode<AES>::Decryption cbc0(key, 16, IV0);
			StreamTransformationFilter CBC0(cbc0, new StringSink(output), StreamTransformationFilter::PKCS_PADDING);
			CBC0.Put(reinterpret_cast<const unsigned char*>(sink.c_str()), sink.length());
			try { CBC0.MessageEnd(); }
			catch (...) {}
			cout << key << '\n' << output << '\n';
			output.clear();
		}
	}
	return 0;
}
