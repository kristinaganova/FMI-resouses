#include "StartUp.h"

MyString readString(std::ifstream& file)
{
    uint32_t length;
    file.read((char*)(&length), sizeof(uint32_t));

    if (length == 0)
        return MyString();

    char* buffer = new char[length];
    file.read(buffer, length);

    MyString str(buffer);

    delete[] buffer;

    return str;
}

bool containsNumber(const Vector<uint32_t>& numbers, size_t number)
{
    for (const auto& n : numbers)
    {
        if (n == number)
            return true;
    }
    return false;
}

bool isDivisibleByOne(const Vector<uint32_t>& numbers, size_t number)
{
    size_t count = 0;
    for (const auto& n : numbers)
    {
        if (number % n == 0)
            count++;
    }
    return count == 1;
}

bool criterionOne(const Vector<uint32_t>& numbers, size_t number)
{
    return containsNumber(numbers, number);
}

bool criterionTwo(const Vector<uint32_t>& numbers, size_t number)
{
    return !containsNumber(numbers, number);
}

bool criterionThree(const Vector<uint32_t>& numbers, size_t number)
{
    return isDivisibleByOne(numbers, number);
}

Set* constructSetFromFile(std::ifstream& file)
{
    uint32_t N, T;
    file.read((char*)&N, sizeof(N));
    file.read((char*)&T, sizeof(T));


    if (T == 0)
    {
        Vector<uint32_t> numbers(N);
        file.read((char*)(numbers.getData()), N * sizeof(uint32_t));
        return new CriterionSet<uint32_t>(numbers, criterionOne);
    }
    else if (T == 1)
    {
        Vector<uint32_t> numbers(N);
        file.read((char*)(numbers.getData()), N * sizeof(uint32_t));
        return new CriterionSet<uint32_t>(numbers, criterionOne);
    }
    else if (T == 2)
    {
        Vector<uint32_t> numbers(N);
        file.read((char*)(numbers.getData()), N * sizeof(uint32_t));
        return new CriterionSet<uint32_t>(numbers, criterionTwo);
    }

    else if (T == 3)
    {
        Vector<MyString> filePaths(N);
        for (size_t i = 0; i < N; i++)
        {
            filePaths[i] = readString(file);
        }

        Vector<const Set*> sets;
        for (const auto& filePath : filePaths)
        {
            std::ifstream externalFile(filePath.c_str(), std::ios::binary);
            if (!externalFile)
            {
                std::cerr << "Failed to open external file: " << filePath << std::endl;
                return nullptr;
            }
            Set* set = constructSetFromFile(externalFile);
            if (set == nullptr)
                return nullptr;
            sets.pushBack(set);
            externalFile.close();
        }
        return new UnionSet(sets);
    }
    else if (T == 4)
    {
        Vector<MyString> filePaths(N);
        for (size_t i = 0; i < N; i++)
        {
            filePaths[i] = readString(file);
        }

        Vector<const Set*> sets;
        for (const auto& filePath : filePaths)
        {
            std::ifstream externalFile(filePath.c_str(), std::ios::binary);
            if (!externalFile)
            {
                std::cerr << "Failed to open external file: " << filePath << std::endl;
                return nullptr;
            }
            Set* set = constructSetFromFile(externalFile);
            if (set == nullptr)
                return nullptr;
            sets.pushBack(set);
            externalFile.close();
        }
        return new IntersectionSet(sets);
    }

    return nullptr;
}

void createFilee(const char* filename, const char* content)
{
    std::ofstream file(filename, std::ios::binary);
    if (file)
    {
        size_t length = strlen(content);
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(content, length);
        file.close();
        std::cout << "File created: " << filename << std::endl;
    }
    else
    {
        std::cout << "Failed to create file: " << filename << std::endl;
    }
}

void run()
{
    try
    {
        std::ifstream file("set.bin", std::ios::binary);
        if (!file.is_open())
        {
            std::cout << "Failed to open input file" << std::endl;
            return;
        }

        Set* set = constructSetFromFile(file);
        if (set == nullptr)
        {
            std::cout << "Failed to construct the set from the file" << std::endl;
            return;
        }

        delete set;

        file.close();
        return;
    }
    catch (const std::exception& ex)
    {
        std::cout << "Exception occurred: " << ex.what() << std::endl;
        return;
    }
    catch (...)
    {
        std::cout << "Unknown exception occurred" << std::endl;
        return;
    }
}

//how i created the files to test them
//
//void createFile(const char* filename, const char* content)
//{
//    std::ofstream file(filename, std::ios::binary);
//    if (file)
//    {
//        size_t length = strlen(content);
//        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
//        file.write(content, length);
//        file.close();
//        std::cout << "File created: " << filename << std::endl;
//    }
//    else
//    {
//        std::cout << "Failed to create file: " << filename << std::endl;
//    }
//}
//
//int main()
//{
//    createFile("first.bin", "1 3 4 6 2 8 9");
//    createFile("second.bin", "");
//    createFile("third.bin", "4 6\n2 3 5");
//
//    std::ofstream setFile("set.bin", std::ios::binary);
//    if (setFile)
//    {
//        uint32_t N = 3;
//        uint32_t T = 4;
//        setFile.write(reinterpret_cast<const char*>(&N), sizeof(N));
//        setFile.write(reinterpret_cast<const char*>(&T), sizeof(T));
//
//        const char* content1 = "first.bin";
//        size_t length = strlen(content1);
//        setFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
//        setFile.write(content1, length);
//
//        const char* content2 = "second.bin";
//        size_t length2 = strlen(content2);
//        setFile.write(reinterpret_cast<const char*>(&length2), sizeof(length2));
//        setFile.write(content2, length2);
//
//        const char* content3 = "third.bin";
//        size_t length3 = strlen(content3);
//        setFile.write(reinterpret_cast<const char*>(&length3), sizeof(length3));
//        setFile.write(content3, length3);
//        setFile.close();
//        std::cout << "File created: set.bin" << std::endl;
//    }
//    else
//    {
//        std::cout << "Failed to create file: set.bin" << std::endl;
//    }
//
//    return 0;
//}
//
