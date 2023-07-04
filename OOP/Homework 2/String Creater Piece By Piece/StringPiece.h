#pragma once

static const short MAX_PIECE_LEN = 16;
class StringPiece
{
private:
	char _str[MAX_PIECE_LEN + 1]; 
	unsigned int _start; 
	unsigned int _end; 
public:
    StringPiece();
    StringPiece(const char* str);
    StringPiece(const char* str, unsigned int start, unsigned int end);
    ~StringPiece() = default;

    const char* c_str() const;
    const char* get() const;
    void set(const char* str);
    size_t length() const;
    void append(const char* str, unsigned int len);
    void appendInTheBeginning(const char* str, unsigned int len);
    void print() const;

    const char* toString() const;

    StringPiece& operator<<(const char* str);
    StringPiece& operator<<(unsigned int num);
    StringPiece& operator>>(const char* str);
    StringPiece& operator>>(unsigned int num);

    void removeFirstKChars(unsigned int k);
    void removeLastKChars(unsigned int k);
    void changeCharByIndex(int index, char c);
};
