#include "pontifex.h"

#include <cstring>


namespace ptfxcpr {
    PontifexCipher::PontifexCipher() : _enc_key(new char[PontifexCipher::KEYLENGTH + 1]), _enc_data_size(0), 
										_clear_data_size(0) {
		this->initializeKeyCardDeck();
    }
	
	PontifexCipher::PontifexCipher(const char* key) : _enc_key(new char[PontifexCipher::KEYLENGTH + 1]), 
													_enc_data_size(0), _clear_data_size(0) {
		std::strncpy(this->_enc_key, key, PontifexCipher::KEYLENGTH + 1);	
	}

	PontifexCipher::~PontifexCipher(void) {
		if(this->_enc_key) delete [] this->_enc_key;
		this->_enc_key = NULL;
	}
	
	void PontifexCipher::initializeKeyCardDeck(void) {
		for (size_t ptr = 0; ptr < PontifexCipher::KEYLENGTH; ++ ptr) { 
            if(ptr == 52) { 
                this->_enc_key[ptr] = '#';
                continue;
            } 
            if(ptr == 53) { 
                this->_enc_key[ptr] = '$';
                continue;
            } 
            this->_enc_key[ptr] = ptr + 48;
        } 
		this->_enc_key[PontifexCipher::KEYLENGTH] = '\0';
	}
	
	void PontifexCipher::generateEncryptionKey(void) {
	}

	char* PontifexCipher::getEncriptionkey(void) {
		return this->_enc_key;
	}

}
