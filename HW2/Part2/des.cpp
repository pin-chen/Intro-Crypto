#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

struct bits{
	bool bit[64]={};
};

string HEX = "0123456789ABCDEF";
map<char, int> HEX_I = { {'0',0}, {'1',1}, {'2',2}, {'3',3}, {'4',4}, {'5',5}, {'6',6}, {'7',7}, {'8',8}, {'9',9}, {'A',10}, {'B',11}, {'C',12}, {'D',13}, {'E',14}, {'F',15}};

int IP[64] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

int s_box[8][64] = {
	{	14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,//1
		0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
		4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
		15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	{	15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,//2
		3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
		0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
		13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	{	10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,//3
		13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
		13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
		1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
	{	7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,//4
		13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
	{	2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,//5
		14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
		4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
		11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
	{	12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,//6
		10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
		9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
		4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
	{	4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,//7
		13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
		1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
		6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
	{	13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,//8
		1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
		7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
		2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
};

int E[48] = {
	32, 1,  2,  3,  4,  5,
	4,  5,  6,  7,  8,  9,
	8,  9,  10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

int P[32] = {
	16, 7,  20, 21, 29, 12, 28, 17,
	1,  15, 23, 26, 5,  18, 31, 10,
	2,  8,  24, 14, 32, 27, 3,  9,
	19, 13, 30, 6,  22, 11, 4,  25
};

int FP[64] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41,  9, 49, 17, 57, 25
};

int PC1[56] = {
	57, 49, 41, 33, 25, 17, 9,
	1,  58, 50, 42, 34, 26, 18,
	10, 2,  59, 51, 43, 35, 27,
	19, 11, 3,  60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7,  62, 54, 46, 38, 30, 22,
	14, 6,  61, 53, 45, 37, 29,
	21, 13, 5,  28, 20, 12, 4
};

int PC2[48] = {
	14, 17, 11, 24, 1,  5,
	3,  28, 15, 6,  21, 10,
	23, 19, 12, 4,  26, 8,
	16, 7,  27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

bits key16[16];

void ASCIItoBit(string s, bits& temp){
	int k = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 1 << 7; j > 0; j = j >> 1) {
			temp.bit[k] = (s[i] & j) ? 1 : 0;
			k++;
		}
	}
}

void BittoASCII(string& s, bits temp){
	s.clear();
	for(int i = 0; i < 64; i += 8){
		s.push_back(char(temp.bit[i + 0] << 7 | temp.bit[i + 1] << 6 | temp.bit[i + 2] << 5 | temp.bit[i + 3] << 4 | temp.bit[i + 4] << 3 | temp.bit[i + 5] << 2 | temp.bit[i + 6] << 1 | temp.bit[i + 7] << 0));
	}
}

void BitToHEX(string& s, bits temp){
	s.clear();
	for(int i = 0; i < 64; i += 4){
		s.push_back(HEX[temp.bit[i + 0] << 3 | temp.bit[i + 1] << 2 | temp.bit[i + 2] << 1 | temp.bit[i + 3] << 0]);
	}
}

void HEXToBit(string s, bits& temp){
	int k = 0;
	for(int i = 0; i < 16; i++){
		for(int j = 1 << 3; j > 0; j = j >> 1) {
			temp.bit[k] = (HEX_I[s[i]] & j) ? 1 : 0;
			k++;
		}
	}
}

void shiftkey(bits& key){
	bool temp;
	temp = key.bit[0];
	for (int i = 0; i < 27; i++){
		key.bit[i] = key.bit[i+1];
	}
	key.bit[27] = temp;
	temp = key.bit[28];
	for (int i = 28; i < 55; i++){
		key.bit[i] = key.bit[i+1];
	}	
	key.bit[55] = temp;
}

void GenerateKey(bits key){
	bits key_PC1;
	for(int i=0; i<56; i++){
		key_PC1.bit[i] = key.bit[ PC1[i] - 1 ];
	}
	for(int i = 0; i < 16; i++){
		
		if(i == 0 || i == 1 || i == 8 || i ==15){
			shiftkey(key_PC1);
		}else{
			shiftkey(key_PC1);
			shiftkey(key_PC1);
		}
		for(int j = 0; j < 48; j++){
			key16[i].bit[j] = key_PC1.bit[ PC2[j] - 1];
		} 
	}
}

void XOR(bits& X, bits Y, bits Z, int size) {
	for(int i = 0; i < size; i++){
		X.bit[i] = Y.bit[i] ^ Z.bit[i];
	}
}

void F(bits& next, bits R, bits key) {
	//E
	bits ER;
	for (int i=0; i<48; i++){
		ER.bit[i] = R.bit[ E[i] - 1 ];
	}
	//ER xor key
	XOR(ER, ER, key, 48);
	//SER
	bits SER;
	int j = 0, k = 0;
	for (int i = 0, j = 0, k = 0; i < 48; i += 6) {
		int x = s_box[j][ ER.bit[i]<<5 | ER.bit[i+5]<<4 | ER.bit[i+1]<<3 | ER.bit[i+2]<<2 | ER.bit[i+3]<<1 | ER.bit[i+4] ];
		j++;
		for (int o = 1 << 3; o > 0; o = o >> 1){
			SER.bit[k] = (x & o) ? 1 : 0;
			k++;
		}
	}
	//PSER
	for (int i=0; i<32; i++){
		next.bit[i] = SER.bit[ P[i] - 1];
	}
}

void des_dec(bits cipher, bits& txt){
	bits temp;
	//IP
	for (int i = 0; i < 64; i++){
		temp.bit[i] = cipher.bit[ IP[i] - 1];
	}
	for (int i = 0; i < 64; i++){
		cipher.bit[i] = temp.bit[i];
	}
	//16 round F and XOR key 16~1
	for (int k = 15; k >= 0; k--) {
		bits tempR, tempL;
		for(int i = 0; i < 32; i++){
			tempL.bit[i] = cipher.bit[i];
		}
		for(int i = 0; i < 32; i++){
			tempR.bit[i] = cipher.bit[i + 32];
		}
		
		F(temp, tempR, key16[k]);
		XOR(temp, tempL, temp, 32);
		
		for(int i = 0; i < 32; i++){
			cipher.bit[i] = tempR.bit[i];
		}
		for(int i = 0; i < 32; i++){
			cipher.bit[i + 32] = temp.bit[i];
		}
	}
	//32-bit swap
	for(int i = 0; i < 32; i++){
		temp.bit[i] = cipher.bit[i];
	}
	for(int i = 0; i < 32; i++){
		cipher.bit[i] = cipher.bit[i + 32];
	}
	for(int i = 32; i < 64; i++){
		cipher.bit[i] = temp.bit[i - 32];
	}
	//FP
	for (int i=0; i<64; i++){
		txt.bit[i] = cipher.bit[ FP[i] - 1 ];
	}
}

void des_enc(bits& cipher, bits txt){
	bits temp;
	//IP
	for (int i = 0; i < 64; i++){
		temp.bit[i] = txt.bit[ IP[i] - 1];
	}
	for (int i = 0; i < 64; i++){
		txt.bit[i] = temp.bit[i];
	}
	//16 round F and XOR key 1~16
	for (int k = 0; k < 16; k++) {
		bits tempR, tempL;
		for(int i = 0; i < 32; i++){
			tempL.bit[i] = txt.bit[i];
		}
		for(int i = 0; i < 32; i++){
			tempR.bit[i] = txt.bit[i + 32];
		}
		
		F(temp, tempR, key16[k]);
		XOR(temp, tempL, temp, 32);
		
		for(int i = 0; i < 32; i++){
			txt.bit[i] = tempR.bit[i];
		}
		for(int i = 0; i < 32; i++){
			txt.bit[i + 32] = temp.bit[i];
		}
	}
	//32-bit swap
	for(int i = 0; i < 32; i++){
		temp.bit[i] = txt.bit[i];
	}
	for(int i = 0; i < 32; i++){
		txt.bit[i] = txt.bit[i + 32];
	}
	for(int i = 32; i < 64; i++){
		txt.bit[i] = temp.bit[i - 32];
	}
	//FP
	for (int i=0; i<64; i++){
		cipher.bit[i] = txt.bit[ FP[i] - 1 ];
	}
}

int main(){
	ifstream inP("DES-Key-Plaintext.txt");
	ifstream inC("DES-Key-Ciphertext.txt");
	ofstream outP("des-out-enc.txt");
	ofstream outC("des-out-dec.txt");
	string S_key, S_txt, S_cipher, s;
	bits key, txt, cipher;
	int i;
	while( getline(inP, s) ){//ENC
		//input
		for(i = 0; i < 8; i++){
			S_key.push_back(s[i]);
		}
		for(i = 9; i < 17; i++){
			S_txt.push_back(s[i]);
		}
		//change to bits
		ASCIItoBit(S_key, key);
		ASCIItoBit(S_txt, txt);
		//generate 16 key
		GenerateKey(key);
		//enc
		des_enc(cipher, txt);
		//change to HEX
		BitToHEX(S_cipher, cipher);
		//output
		outP << S_key << " " << S_txt << " " << S_cipher << '\n';
		//clear
		S_key.clear();
		S_txt.clear();
		S_cipher.clear(); 
	}
	while( getline(inC, s) ){//DEC
		//input
		for(i = 0; i < 8; i++){
			S_key.push_back(s[i]);
		}
		for(i = 9; i < 25; i++){
			S_cipher.push_back(s[i]);
		}
		//change to bits
		ASCIItoBit(S_key, key);
		HEXToBit(S_cipher, cipher);
		//generate 16 key
		GenerateKey(key);
		//dec
		des_dec(cipher, txt);
		//change to ASCII
		BittoASCII(S_txt, txt);
		//output
		outC << S_key << " " << S_cipher << " " << S_txt << '\n';
		//clear
		S_key.clear();
		S_txt.clear();
		S_cipher.clear(); 
	}
	return 0;
} 