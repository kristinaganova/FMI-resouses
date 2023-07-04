#pragma once

static const short MAX_PIECE_LEN = 16;
class StringPiece
{
private:
	const char* _begin;
	const char* _end;
public:
	StringPiece();
	StringPiece(const char* begin, const char* end);
	explicit StringPiece(const char* str);
	~StringPiece() = default;

	const char* c_str() const;
	const char* get() const;
	void set(const char* str);
	size_t length() const;
	void append(const char* str, size_t len);
	void appendInTheBeggining(const char* str, size_t  len);
	void print() const;

	const char* toString() const;

	StringPiece& operator<<(const char* str);
	StringPiece& operator<<(size_t num);
	StringPiece& operator>>(const char* str);
	StringPiece& operator>>(size_t num);

	void removeFirstKChars(size_t k);
	void removeLastKChars(size_t k);
	void changeCharByIndex(int index, char c);
};