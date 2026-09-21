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
        bool encryptMessage(const unsigned char* req, unsigned char* res) const;

        bool decryptMessage(const unsigned char* req, unsigned char* res) const;

        /** Key setter */
        void setEncriptionKey(const char* key);

        /** Modern key generator, something like MT */
        void generateEncryptionKey(void);

        /** Old, closest to book encription key generator */
        char* shuffleCardsEncriptionKey(int shuffle_count = 10);
		
		/** Key getter */
        char* getEncriptionkey(void) const;
    private:
    	void generateKeyFlow(size_t size);

		void initializeKeyCardDeck(void);

        static inline const char _JOKER_A = '#';

        static inline const char _JOKER_B = '$';

		size_t _enc_data_size;

        size_t _clear_data_size;

    	char* _enc_key;
    };
} //ptfxcpr

#endif
