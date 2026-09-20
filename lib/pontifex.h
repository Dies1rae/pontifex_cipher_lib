#ifndef PONTIFEX_H
#define PONTIFEX_H

#include <cstdio>
#include <cstdint>


namespace ptfxcpr {
    class PontifexCipher {
    public:
		/** Consts */
		static inline const uint8_t KEYLENGTH = 54;
        /** Ctors */
        PontifexCipher(void);
		
		PontifexCipher(const char* key);

        PontifexCipher(PontifexCipher&) = delete;

        PontifexCipher& operator=(PontifexCipher&) = delete;

        ~PontifexCipher(void);

        /** Main methods */
        bool encryptMessage(const unsigned char* req, unsigned char* res);

        bool decryptMessage(const unsigned char* req, unsigned char* res);

        /** Key setter */
        void setEncriptionKey(const char* key);

        /** Modern key generator, something like MT */
        void generateEncryptionKey(void);

        /** Old, closest to book encription key generator */
        void shuffleCardsEncriptionKey(void);
		
		/** Key getter */
        char* getEncriptionkey(void);
    private:
    	void generateKeyFlow(size_t size);

		void initializeKeyCardDeck(void);

    	char* _enc_key;
    	size_t _enc_data_size;
    	size_t _clear_data_size;
    };
} //ptfxcpr

#endif
