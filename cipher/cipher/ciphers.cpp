/**
 * \file ciphers.cpp
 *
 * Ebben a fájlban kell megvalósítania az CaesarCipher, MyCipher, CipherQueue osztályok metódusait.
 * 
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include "memtrace.h"
#include "ciphers.h"
#include <string>
#include <iostream>
#define string std::string
#define prn std::cout
#define endl std::endl
#define minv int('a') // 97
#define maxv int('z') // 122

string CaesarCipher::encode(const string& message) {
	string _n;
	for (size_t i = 0; i < message.size(); i++) {
		if (message[i] == ' ') {
			_n.resize(_n.size() + 1, ' ');
			continue;
		}
		if ((int)message[i] > 122 || (int)message[i] < 97) throw "I2JNLH";
		int new_char_code = message[i] + shift;
		// std::cout << "New code for " << (char)message[i] << "( " << (int)message[i] << " )" << " is " << (int)new_char_code << " (" << (char)new_char_code << ") ";
		while (new_char_code > maxv || new_char_code < minv) {
			if (new_char_code > maxv) {
				new_char_code = ((new_char_code - (maxv + 1)) % 26) + minv;
				// std::cout << " which is >122, falling back to " << (int)new_char_code << " (" << (char)new_char_code << ")" << endl;
			}
			else if (new_char_code < minv) {
				new_char_code = (maxv + 1) + ((new_char_code - minv) % 26);
				// std::cout << " which is <97, falling back to " << (int)new_char_code << " (" << (char)new_char_code << ")" << endl;
			}
			//else std::cout << " which is perfect." << endl;
		}
		_n.resize(_n.size() + 1, new_char_code);
	}
	return _n;
}

string CaesarCipher::decode(const string& message) {
	shift = -1 * shift;
	string _n = encode(message);
	shift = -1 * shift;
	return _n;
}

Cipher* CaesarCipher::clone() const {
	CaesarCipher* _n = new CaesarCipher(shift);
	return _n;
}

string MyCipher::encode(const string& message) {
	string _n;
	for (size_t i = 0; i < message.size(); i++) {
		if (message[i] == ' ') {
			_n.resize(_n.size() + 1, ' ');
			continue;
		}
		if ((int)message[i] > 122 || (int)message[i] < 97) throw "I2JNLH";
		int new_char_code =\
			message[i] + offset + i + ((int)key[i % key.size()] - minv);
		while (new_char_code > maxv || new_char_code < minv) {
			if (new_char_code > maxv)
				new_char_code = ((new_char_code - (maxv + 1)) % 26) + minv;
			else if (new_char_code < minv)
				new_char_code = (maxv + 1) + ((new_char_code - minv) % 26);
		}
		// prn << endl;
		_n.resize(_n.size() + 1, new_char_code);
		// prn << "Out with value " << new_char_code << endl;
	}
	return _n;
}

string MyCipher::decode(const string& message) {
	string _n;
	for (size_t i = 0; i < message.size(); i++) {
		if (message[i] == ' ') {
			_n.resize(_n.size() + 1, ' ');
			continue;
		}
		if ((int)message[i] > 122 || (int)message[i] < 97) throw "I2JNLH";
		int new_char_code = \
			message[i] - offset - i - ((int)key[i % key.size()] - minv);
		//std::cout << "New code for " << (char)message[i] << "( " << (int)message[i] << " )" << " is " << (int)new_char_code << " (" << (char)new_char_code << ") ";
		while (new_char_code > maxv || new_char_code < minv) {
			if (new_char_code > maxv) {
				new_char_code = ((new_char_code - (maxv + 1)) % 26) + minv;
				//std::cout << " which is >122, falling back to " << (int)new_char_code << " (" << (char)new_char_code << ")" << endl;
			}
			else if (new_char_code < minv) {
				new_char_code = (maxv + 1) + ((new_char_code - minv) % 26);
				//std::cout << " which is <97, falling back to " << (int)new_char_code << " (" << (char)new_char_code << ")" << endl;
			}
		}
		//prn << " out with char code" << new_char_code << endl;
		_n.resize(_n.size() + 1, new_char_code);
	}
	return _n;
}

Cipher* MyCipher::clone() const {
	MyCipher* _n = new MyCipher(key, offset);
	return _n;
}

void CipherQueue::add(Cipher* cipher) {
	ciphers.push_back(cipher);
}

string CipherQueue::encode(const string& message) {
	string encoded = message;
	for (size_t i = 0; i < ciphers.size(); i++) {
		encoded = ciphers[i]->encode(encoded);
	}
	return encoded;
}

string CipherQueue::decode(const string& message) {
	string decoded = message;
	for (auto cipher = ciphers.rbegin(); cipher != ciphers.rend(); ++cipher) {
		decoded = (*cipher)->decode(decoded);
	}
	return decoded;
}

CipherQueue& CipherQueue::operator=(const CipherQueue& c) {
	if (this == &c) {
		return *this;
	}
	for (size_t i = 0; i < ciphers.size(); i++) {
		delete ciphers[i];
	}
	ciphers.clear();
	for (size_t i = 0; i < ciphers.size(); i++) {
		ciphers.push_back(ciphers[i]->clone());
	}
	return *this;
}

CipherQueue* CipherQueue::clone() const {
	return new CipherQueue(*this);
}
int main_() {
	return 0;
}