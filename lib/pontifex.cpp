#include "pontifex.h"

#include <cstring>
#include <random>
#include <ctime>
#include <algorithm>


namespace ptfxcpr {
	const uint8_t PontifexCipher::KEYLENGTH = 54;

    PontifexCipher::PontifexCipher() : _enc_data_size(0), _clear_data_size(0), _enc_key(new char[(size_t)PontifexCipher::KEYLENGTH + 1]) {
		this->initializeKeyCardDeck();
    }
	
	PontifexCipher::PontifexCipher(const char* key) : _enc_data_size(0), _clear_data_size(0), _enc_key(new char[(size_t)PontifexCipher::KEYLENGTH + 1]) {
		if(strlen(key) != PontifexCipher::KEYLENGTH) {
            exit(-1);
		}
		std::strcpy(this->_enc_key, key);	
		this->_enc_key[PontifexCipher::KEYLENGTH] = '\0';
	}

	PontifexCipher::~PontifexCipher(void) {
		if(this->_enc_key) delete [] this->_enc_key;
		this->_enc_key = NULL;
	}
	
	void PontifexCipher::initializeKeyCardDeck(void) {
		if(!this->_enc_key) {
			this->_enc_key = new char[(size_t)PontifexCipher::KEYLENGTH + 1];
		}
		for (size_t ptr = 0; ptr < PontifexCipher::KEYLENGTH; ++ ptr) { 
            if(ptr == 52) { 
				/** Joker A */
                this->_enc_key[ptr] = this->_JOKER_A;
                continue;
            } 
            if(ptr == 53) { 
				/** Joker B */
                this->_enc_key[ptr] = this->_JOKER_B;
                continue;
            } 
            this->_enc_key[ptr] = ptr + 48;
        } 
		this->_enc_key[PontifexCipher::KEYLENGTH] = '\0';
	}
	
   char* PontifexCipher::shuffleCardsEncriptionKey(int shuffle_count) {
		if(this->_enc_key == NULL) {
			return NULL;
		}
		int shfl_cnt = std::max(shuffle_count, 10);
		do {
			for(size_t ptr = PontifexCipher::KEYLENGTH - 1; ptr > 0; --ptr) {
				std::random_device rd;
				std::mt19937 seed (rd());
				std::uniform_int_distribution<size_t> distrib(0, ptr);
				std::swap(this->_enc_key[ptr], this->_enc_key[distrib(seed)]);
			}
			
		} while (--shfl_cnt > 0);
		return this->getEncriptionkey();
	}

	void PontifexCipher::generateEncryptionKey(void) {
		this->shuffleCardsEncriptionKey(20);
	}

	char* PontifexCipher::getEncriptionkey(void) const {
		return this->_enc_key;
	}

	void PontifexCipher::generateKeyFlow(size_t size) {
		if (size == 0) {
			exit(-1);
		}
		/** Joker placed on deck in work position */
		bool jk_plased = false;
		size_t pos_jk_a = 0;
		size_t pos_jk_b = 0;
		for (size_t ptr = 0; ptr < PontifexCipher::KEYLENGTH && !jk_plased; ++ptr) {
			if(this->_enc_key[ptr] == this->_JOKER_A) {
				if(ptr == (size_t)PontifexCipher::KEYLENGTH - 1) {
					std::swap(this->_enc_key[ptr], this->_enc_key[1]);
					pos_jk_a = 1;
				} else {
					std::swap(this->_enc_key[ptr], this->_enc_key[ptr + 1]);
                      pos_jk_a = ptr + 1;
				}
				jk_plased = pos_jk_a > 0 && pos_jk_b > 0 ? true : false;
				continue;
			}
            if(this->_enc_key[ptr] == this->_JOKER_B) {
				if(ptr == (size_t)PontifexCipher::KEYLENGTH - 1) {
					std::swap(this->_enc_key[ptr], this->_enc_key[2]);
					pos_jk_b = 2;
				} else if(ptr == (size_t)PontifexCipher::KEYLENGTH - 2) {
					std::swap(this->_enc_key[ptr], this->_enc_key[1]);
					pos_jk_b = 1;
				} else {
					std::swap(this->_enc_key[ptr], this->_enc_key[ptr + 2]);
					pos_jk_b = ptr + 2;
				}
				jk_plased = pos_jk_a > 0 && pos_jk_b > 0 ? true : false;
				continue;
            }
		}
	}
	
	void PontifexCipher::setEncriptionKey(const char* key) {
        if(strlen(key) != PontifexCipher::KEYLENGTH) {
            exit(-1);
        }
		std::strcpy(this->_enc_key, key);
        this->_enc_key[PontifexCipher::KEYLENGTH] = '\0';
	}
}
