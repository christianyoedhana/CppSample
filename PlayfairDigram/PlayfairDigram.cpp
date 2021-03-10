#include <string>
#include <memory>
#include <vector>
#include <utility>
#include "HelperFunctions.h"
#include "PlayfairDigram.h"
#include "PlobiusSquare.h"

using std::string;
using std::make_unique;
using std::unique_ptr;
using std::vector;
using std::make_pair;

namespace playfair_digram {
	

	PlayfairDigram::PlayfairDigram(const string& key){
		if (!validateMessage(key)) throw InvalidKeyException("Invalid key " + key);
		m_cipher = make_unique<PlobiusSquare>(removeSpaces(key));
	}

	string PlayfairDigram::encrypt(const string& msg) const{
		if (!validateMessage(msg)) throw InvalidKeyException("Invalid message " + msg);
		vector<string> digrams = applyRule1(msg);
		string encoded;
		for (const auto& digram : digrams){
			if (isRule2(digram, *m_cipher)) {//I and J encoding are resolved here
				encoded += encryptRule2(digram, *m_cipher); 
				continue;
			}
			if (isRule3(digram, *m_cipher)) {
				encoded += encryptRule3(digram, *m_cipher);
				continue;
			}
			if (isRule4(digram, *m_cipher)) {
				encoded += encryptRule4(digram, *m_cipher);
				continue;
			}
		}
		
		return encoded;
	}

	string PlayfairDigram::decrypt(const string& msg) const
	{
		string decoded;
		for (string::size_type i = 0; i < msg.size(); i+=2) {
			string digram = msg.substr(i, 2);
			if (isRule2(digram, *m_cipher)) {
				decoded += decryptRule2(digram, *m_cipher);
				continue;
			}
			if (isRule3(digram, *m_cipher)) {
				decoded += decryptRule3(digram, *m_cipher);
				continue;
			}
			if (isRule4(digram, *m_cipher)) {
				decoded += decryptRule4(digram, *m_cipher);
				continue;
			}
		}
	
		return decoded;
	}
}