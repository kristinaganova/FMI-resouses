#pragma once
#include "Time.h"
#include "constants.h"
#include "FileAccess.h"

class TextFile 
{
private:
	char name[MAX_NAME_LEN + 1];
	char content[MAX_CONTENT_LEN + 1];
	size_t size;
	Time createdAt;
	Time modifiedAt;
	FileAccess rigths;
public:
	TextFile(const char* name, const char* content, size_t size,
		const Time& createdAt, const Time& modifiedAt, 
		FileAccess rigths);
	TextFile();
	TextFile(const char* name ,const Time& modifiedAt, const char* accessRights);

	const char* getName() const;
	const char* getContent() const;
	size_t getSize() const;
	Time getCreatedAt() const;
	Time getModifiedAt() const;
	FileAccess getAccessRights() const;

	void setName(const char* name);
	void setContent(const char* content);
	void setSize(size_t size);
	void setCreatedAt(const Time& createdAt);
	void setModifiedAt(const Time& modifiedAt);
	void setAccessRigths(const FileAccess& rigths);

	void appendContent(const char* content);
	void printInfo(char role) const;
	void printContent() const;

	bool hasAccess(char role) const;

	bool compareByName(const TextFile& file) const;
	bool compareByCreationTime(const TextFile& file) const ;
	bool compareByModificationTime(const TextFile& file) const;
	bool compareBySize(const TextFile& file) const;
};