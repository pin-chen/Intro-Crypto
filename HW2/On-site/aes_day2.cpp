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
	byte cipher[] = "3342292597c67a1bcdb115ad51239dd636fe";
	const byte iv[] = "0000000000000000";
	string k;
	
	HexDecoder decoder;
	decoder.Attach(new StringSink(k));
	decoder.Put(cipher, sizeof(cipher));
	decoder.MessageEnd();



	for (char i = '0'; i <= '9'; i++) {
		for (char j = '0'; j <= '9'; j++) {
			key[14] = i;
			key[15] = j;
			const AlgorithmParameters cfbP = MakeParameters
			(Name::FeedbackSize(), 2)
				(Name::IV(), ConstByteArrayParameter(iv, 16));
			string output;
			CFB_Mode<AES>::Decryption cfb; cfb.SetKey(key, 16, cfbP);
			try {
				StreamTransformationFilter CFB(cfb, new StringSink(output), StreamTransformationFilter::ZEROS_PADDING);
				CFB.Put(reinterpret_cast<const unsigned char*>(k.c_str()), k.length());
				CFB.MessageEnd();
			}catch(...){}
			cout << key << " " << output << "\n";
			output.clear();
		}
	}
	return 0;
}
