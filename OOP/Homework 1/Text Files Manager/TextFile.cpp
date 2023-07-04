#include "helpers.h"
#include "TextFile.h"
#include <iostream>

TextFile::TextFile(const char* name, const char* content, size_t size,
    const Time& createdAt, const Time& modifiedAt, FileAccess rigths)
{
    setName(name);
    setContent(content);
    setSize(size);
    setCreatedAt(createdAt);
    setModifiedAt(modifiedAt);
    setAccessRigths(rigths);
}

TextFile::TextFile() : size(0), rigths(FileAccess()), createdAt(Time()), modifiedAt(Time())
{
    name[0] = '\0';
    content[0] = '\0';
}

TextFile::TextFile(const char* name, const Time& createdAt, const char* accessRights)
    : size(0), rigths(FileAccess()), createdAt(createdAt), modifiedAt(Time())
{
    setName(name);
    setAccessRigths(accessRights);
    content[0] = '\0';
}

bool TextFile::hasAccess(char role) const
{
    switch (role) 
    {
    case 'o':
        return rigths.canRead(role);
    case 'g':
        return rigths.canWrite(role);
    case 'a':
        return rigths.canExecute(role);
    default:
        return false;
    }
}

const char* TextFile::getName() const
{
	return this->name;
}

const char* TextFile::getContent() const
{
	return this->content;
}

size_t TextFile::getSize() const
{
	return this->size;
}

Time TextFile::getCreatedAt() const 
{
	return this->createdAt;
}

Time TextFile::getModifiedAt() const
{
	return this->modifiedAt;
}

FileAccess TextFile::getAccessRights() const
{
	return this->rigths;
}

void TextFile::setName(const char* name) 
{
    if (name != nullptr && strLen(name) <= MAX_NAME_LEN)
    {
        strCpy(this->name, name);
    }
}

void TextFile::setContent(const char* content) 
{
    if (content != nullptr && strLen(content) <= MAX_CONTENT_LEN)
    {
        strCpy(this->content, content);
        size = strLen(content);
    }
}

void TextFile::setSize(size_t size)
{
    if (size <= MAX_CONTENT_LEN)
    {
        this->size = size;
    }
}

void TextFile::setCreatedAt(const Time& createdAt)
{
    this->createdAt = createdAt;
}

void TextFile::setModifiedAt(const Time& modifiedAt) 
{
    this->modifiedAt = modifiedAt;
}

void TextFile::setAccessRigths(const FileAccess& rigths)
{
    this->rigths = rigths;
}

void TextFile::appendContent(const char* content)
{
    size_t currentLength = strLen(this->content);

    size_t newLength = strLen(content);

    if (currentLength + newLength > MAX_CONTENT_LEN) 
    {
        std::cout << "Error: Content exceeds maximum length" << std::endl;
        return;
    }

    for (size_t i = 0; i < newLength; i++)
    {
        this->content[currentLength + i] = content[i];
    }
    this->content[currentLength + newLength] = '\0';
}

void TextFile::printInfo(char role) const 
{
    std::cout << std::endl;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Size: " << this->size << std::endl;
    std::cout << "Created At: "; getCreatedAt().print(); std::cout << std::endl;
    std::cout << "Modified At: "; getModifiedAt().print(); std::cout << std::endl;
    std::cout << "Access Rights: "; getAccessRights().printRights(rigths, role); 
}

void TextFile::printContent() const
{
    std::cout << this->content << std::endl;
}

bool TextFile::compareByName(const TextFile& file) const
{
    return strCmp(this->getName(), file.getName()) < 0;
}

bool TextFile::compareByCreationTime(const TextFile& file) const 
{
    return this->getCreatedAt().compareTime(file.getCreatedAt());
}

bool TextFile::compareByModificationTime(const TextFile& file) const 
{
    return this->getModifiedAt().compareTime(file.getModifiedAt());
}

bool TextFile::compareBySize(const TextFile& file) const 
{
    return this->getSize() < file.getSize();
}