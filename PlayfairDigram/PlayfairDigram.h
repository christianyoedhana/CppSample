#pragma once
#include <string>
#include <memory>
#include "PlobiusSquare.h"

namespace playfair_digram {
	class PlayfairDigram {
	public:
		PlayfairDigram() = delete;
		explicit PlayfairDigram(const std::string& key);	//initialize the digram with the key.
		std::string encrypt(const std::string& msg) const;
		std::string decrypt(const std::string& msg) const;

	private:
		std::string createValidKey(const std::string& key); //helper function to create a valid key. Key can only contain alphanumerics and whitespace
		std::unique_ptr<PlobiusSquare> m_cipher;
	};
}