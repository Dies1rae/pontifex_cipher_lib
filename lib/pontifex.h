



class PontifexCipher {
public:
    /** Constructors */
    PontifexCipher() = default;

    PontifexCipher(PontifexCipher&) = delete;

    ~PontifexCipher();
    
    /** Main methods */
    bool encryptMessage(const unsigned char* req, unsigned char* res);

    bool decryptMessage(const unsigned char* req, unsigned char* res);
    
    void setEncriptionKey( /** some encription keys args */ );
    
    /** Modern key generator, something like MT */
    void generateEncryptionKey(void);
    
    /** Old, closest to book encription key generator */
    void shuffleCardsEncriptionKey(void);

    int* getEncriptionkey(void);
private:
    
};
