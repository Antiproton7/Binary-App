#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

int IntToBinary(int value);
int BinToInt(int binary);
void ParseFile(bool checkBinary, bool encrypted, string encryption_key);
string encryption_key = "a";

ifstream instream("IO Files/Input.txt");
ofstream outstream("IO Files/Output.dat");
ofstream keyfile("IO Files/Cipher_key.dat");


int main(){
bool checkBinary=false, encrypted=false;
int temp = 0;
	
if (!instream.good()){
cout<<"Unable to open input file";
return -1;}


if (instream >> temp) {
	checkBinary = true;
	if (temp == 1) {
		encrypted = true;
		cout << "Encrypted binary detected, please enter decryption key" << endl;
		cin >> encryption_key;
	}
}
else {
	cout << "Text detected, would you like to encrypt the file? (1|0)" << endl;
	cin >> temp;
	if (temp == 1) { cout << "Please enter an encryption string" << endl; cin >> encryption_key; encrypted = true; 
	keyfile<<encryption_key;}
	instream.seekg(0, ios::beg); //reset to start since it isn't binary
	instream.clear();
}

cout<<"Parsing..."<<endl;

ParseFile(checkBinary, encrypted, encryption_key);

cout<<"Done Parsing! Check output."<<endl;
system("PAUSE");	
return 0;}

int IntToBinary(int value){
int binary=0, logarithm=0;

while (value>0){
logarithm=log2(value);
value-=pow(2,logarithm);
binary+=pow(10,logarithm);
if (value==1){binary++; value--;}
} //by the definition of binary, we cannot have another way of expressing the same number, thus this is the optimal way. 
return binary;}

int BinToInt(int binary){
int integer=0,logarithm=0;

while (binary>0){
logarithm=log10(binary);
binary-=pow(10,logarithm);
integer+=pow(2,logarithm);
if (binary==1){integer++; binary--;}
} //I can see why binary conversion is so bloody useful
return integer;}

void ParseFile(bool checkBinary, bool encrypted, string encryption_key) {
	int temp = 0, byteCount = 0, pos = 0;
	string str="";
	char chars = 'a';
	if (checkBinary) {
		cout << "Binary to String" << endl;
		if (encrypted) { cout << "Using encryption key: " << encryption_key << endl;}
		while (instream >> temp) {
			chars= (BinToInt(temp));
			if (encrypted) {
				chars ^= (encryption_key[pos%encryption_key.length()]); //XOR deciphering
					pos++;
			}
			outstream << chars;
		}
	}

	else {
		cout << "String to Binary" << endl;
		if (encrypted) { cout << "Using encryption key: " << encryption_key << endl; outstream << 1<<' '; }
		else { outstream << 0<<' '; }
		int val = 0, pos = 0;
		while (getline(instream, str)) {
			for (int i = 0; i<str.length(); i++) {
				if (encrypted) {
					str[i] ^= (encryption_key[pos%encryption_key.length()]);//XOR cipher
					pos++;
				} 
				val = (str[i]); //parse as separate letters, convert to integers
				outstream << setfill('0');
				outstream << setw(8) << IntToBinary(val); //print binary equivalent
				byteCount++;
				outstream << ' ';
			}
			outstream <<00100000<<' ';
		}
		cout << "ByteCount: " << byteCount << endl;
	}
}
	
