/**
 * \file ciphers.h
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#ifndef CipherS_H
#define CipherS_H

#include <string>
#include <vector>
#include "memtrace.h"

/**
 * Az ős osztály interfésze
 */ 
class Cipher {
public:
    /**
     * Titkosítja a kapott stringet
     * @param   message titkosítandó üzenet
     * @return  a message szöveg titkosított változata
     */
    virtual std::string encode(const std::string& message) = 0;
    /**
     * Dekódolja a kapott stringet
     * @param   ciphertext titkosított üzenet
     * @return  a megfejtett nyílt szöveg
     */
    virtual std::string decode(const std::string& ciphertext) = 0;
    /**
     * Létrehoz egy másolatot dinamikusan
     * @return  a létrehozott objektumra mutató pointer
     */
    virtual Cipher* clone() const = 0;
    /**
     * Alap destruktor
     */ 
    virtual ~Cipher() { };
};

//Osztályok, amiket meg kell csinálni a leírások és az osztálydiagram alapján
class CaesarCipher : public Cipher {
private:
    int shift;
public:
    CaesarCipher(int i) : shift(i) {};
    std::string encode(const std::string&);
    std::string decode(const std::string&);
    Cipher* clone() const;
};

class MyCipher : public Cipher {
private:
    std::string key;
    int offset;
public:
    MyCipher(std::string k, int o = 0) {
        key = k; offset = o;
    };
    std::string encode(const std::string&);
    std::string decode(const std::string&);
    Cipher* clone() const;
};

class CipherQueue : public Cipher {
private:
    std::vector<Cipher*> ciphers;
public:
    CipherQueue() {};
    CipherQueue(const CipherQueue& c) {
        for (size_t i = 0; i < c.ciphers.size(); i++) {
            ciphers.push_back(c.ciphers[i]->clone());
        }
    }
    void add(Cipher* c);
    std::string encode(const std::string&);
    std::string decode(const std::string&);
    CipherQueue& operator=(const CipherQueue&);
    CipherQueue* clone() const;
    ~CipherQueue() {
        for (size_t i = 0; i < ciphers.size(); i++) {
            delete ciphers[i];
        }
    }
};

#endif