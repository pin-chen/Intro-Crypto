#define _CRT_SECURE_NO_WARNINGS
#define checker 0
#define ans 457301
#define start 0
#include <iostream>
#include <fstream>
#include <string>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <iomanip>

using namespace std;
using namespace CryptoPP;

string HEX = "0123456789abcdef";

int main() {
	ofstream out;
	out.open("out.txt");
	{//I Test
		const Integer e1 = 0x11;
		const string N1 = "c963f963d93559ffh";
		const Integer n1(N1.c_str());
		const string M1 = "ElGamal";
		const Integer m1((const byte*)M1.data(), M1.size());
		RSA::PublicKey pubKey;
		pubKey.Initialize(n1, e1);
		const Integer c1 = pubKey.ApplyFunction(m1);
#if checker
		cout << "c1:\t" << hex << c1 << '\n';
#endif
	}
	{//I 128
		const Integer e2 = 0x11;
		const string N2 = "04823f9fe38141d93f1244be161b20fh";
		const Integer n2(N2.c_str());
		const string M2 = "Hello World!";
		const Integer m2((const byte*)M2.data(), M2.size());
		RSA::PublicKey pubKey;
		pubKey.Initialize(n2, e2);
		const Integer c2 = pubKey.ApplyFunction(m2);
#if checker
		cout << "c2:\t" << hex << c2 << '\n';
#endif
		out << hex << c2 << '\n';
	}
	{//I 256
		const Integer e3 = 0x10001;
		const string N3 = "9711ea5183d50d6a91114f1d7574cd52621b35499b4d3563ec95406a994099c9h";
		const Integer n3(N3.c_str());
		const string M3 = "RSA is public key.";
		const Integer m3((const byte*)M3.data(), M3.size());
		RSA::PublicKey pubKey;
		pubKey.Initialize(n3, e3);
		const Integer c3 = pubKey.ApplyFunction(m3);
#if checker
		cout << "c3:\t" << hex << c3 << '\n';
#endif
		out << hex << c3 << '\n';
	}

	{//II Test
		AutoSeededRandomPool rng;
		string msg;
		const string N = "c45350fa19fa8d93h";
		const Integer n(N.c_str());
		const string D = "454a950c5bcbaa41h";
		const Integer d(D.c_str());
		const string E = "11h";
		const Integer e(E.c_str());
		const string C = "a4a59490b843eea0h";
		const Integer c(C.c_str());
		RSA::PrivateKey priKey;
		priKey.Initialize(n, e, d);
		const Integer m = priKey.CalculateInverse(rng, c);
		msg.resize(m.MinEncodedSize());
		m.Encode((byte*)msg.data(), msg.size());
#if checker
		cout << "msg:\t" << msg << '\n';
#endif
	}

	{//II
		AutoSeededRandomPool rng;
		string msg;
		const string N = "c4b361851de35f080d3ca7352cbf372dh";
		const Integer n(N.c_str());
		const string E = "1d35h";
		const Integer e(E.c_str());
		const string C = "a02d51d0e87efe1defc19f3ee899c31dh";
		const Integer c(C.c_str());
		string D = "53a0a95b089cf23adb5cc73f07XXXXXh";
		RSA::PrivateKey priKey;
		char s[5];
		for (int i = start; i < 1048576; i++) {//6fa55  457301
			sprintf(s, "%05x", i);
			for (int j = 0; j < 5; j++) {
				D[j + 26] = s[j];
			}
			const Integer d(D.c_str());
			try{ 
				priKey.Initialize(n, e, d); 
				break;
			}
			catch(...){};
		}
		const Integer m = priKey.CalculateInverse(rng, c);
		msg.resize(m.MinEncodedSize());
		m.Encode((byte*)msg.data(), msg.size());
#if checker
		cout << "key:\t" << D << '\n';
		cout << "msg:\t" << msg << '\n';
#endif
		out << D << '\n';
		out << msg << '\n';

		//check
		const Integer M((const byte*)msg.data(), msg.size());
		RSA::PublicKey pubKey;
		pubKey.Initialize(n, e);
		const Integer CC = pubKey.ApplyFunction(M);
#if checker
		cout << "c:\t" << hex << CC << '\n';
#endif
	}
	return 0;
}