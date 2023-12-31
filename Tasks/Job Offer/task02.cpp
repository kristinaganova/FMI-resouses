#include <iostream>
#include <fstream>
#pragma warning(disable : 4996) 

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;

const int MAX_COMPANY_NAME_LEN = 25;
const char* ERROR_MS = "Error!";
const char* BINARY_FILE_NAME = "JobOffers.dat";
const long long MIN_SALARY = 1234;
const char* PERFECT_OFFERS = "perfectOffers.dat";

namespace myFunctions
{
	int strCmp(const char* str1, const char* str2)
	{
		while (*str1 && (*str1 == *str2))// compares two strings character by character
		{
			str1++;
			str2++;
		}
		return *(const unsigned char*)str1 - *(const unsigned char*)str2; //ASCII difference
	}

	int myStrlen(const char* str)
	{
		if (str == nullptr)
		{
			return 0;
		}

		int count = 0;

		while (*str != '\0')
		{
			count++;
			str++;
		}

		return count;
	}

	void myStrCopy(const char* source, char* dest)
	{
		if (source == nullptr || dest == nullptr)
			return;

		while (*source != '\0')
		{
			*dest = *source;
			dest++;
			source++;
		}
		*dest = '\0';
	}
}

struct JobOffer
{
	char companyName[MAX_COMPANY_NAME_LEN + 1];
	int coworkersCount;
	int paidPaysOff;
	long long projectSalary;
};

void initJobOffer(JobOffer& offer, const char* name, int coworkers, int daysOff, long long salary)
{
	myFunctions::myStrCopy(name, offer.companyName);
	offer.coworkersCount = coworkers;
	offer.paidPaysOff = daysOff;
	offer.projectSalary = salary;
}

void saveToFile(const JobOffer& offer, ofstream& ofs)
{
	ofs.write((const char*)&offer, sizeof(offer));
}

void clearBinaryFile(const char* filePath)
{
	ofstream ofs(filePath, ios::out | ios::binary | ios::trunc);
	ofs.close();
}

size_t getFileSize(ifstream& ifs)
{
	size_t currPos = ifs.tellg();
	ifs.seekg(0, ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(currPos, ios::beg);

	return size;
}

void readFromFile(ifstream& in, JobOffer& jobOffer)
{
	in.read((char*)&jobOffer, sizeof(jobOffer));
}

void filterOffers(const char* fileName, long long minSalary)
{
	JobOffer jobOffer = {};
	ifstream in(fileName);

	if (!in.is_open())
	{
		cout << ERROR_MS << endl;
		return;
	}

	size_t fileSize = getFileSize(in);
	size_t numberOfOrders = fileSize / sizeof(JobOffer);

	for (size_t i = 0; i < numberOfOrders; i++)
	{
		in.read((char*)&jobOffer, sizeof(JobOffer));
		if (jobOffer.projectSalary >= minSalary)
		{
			cout << "Company: " << jobOffer.companyName << " covers the minimum" << endl;
		}
	}
	in.close();

}

bool existOffer(const char* fileName, const char* companyName)
{
	JobOffer jobOffer;
	ifstream in(fileName);

	if (!in.is_open())
	{
		cout << ERROR_MS << endl;
		return false;
	}

	size_t fileSize = getFileSize(in);
	size_t numberOfOrders = fileSize / sizeof(JobOffer);

	for (size_t i = 0; i < numberOfOrders; i++)
	{
		in.read((char*)&jobOffer, sizeof(JobOffer));
		if (myFunctions::strCmp(jobOffer.companyName, companyName))
		{
			in.close();
			return true;
		}
	}
	in.close();
	return false;
}
//Bonus 1
void perfectOffer(const char* filePath, int maxCoworkers, int minVacancyDays, int minSalary) {
	ifstream fileIn(filePath, ios::binary);

	if (!fileIn.is_open()) {
		cout << ERROR_MS << endl;
		return;
	}

	ofstream fileOut(PERFECT_OFFERS, ios::binary);

	if (!fileOut.is_open()) {
		cout << ERROR_MS << endl;
		return;
	}

	JobOffer offer = {};

	while (fileIn.read(reinterpret_cast<char*>(&offer), sizeof(JobOffer))) {
		if (offer.coworkersCount == maxCoworkers && offer.paidPaysOff == minVacancyDays && offer.projectSalary == minSalary) {
			fileOut.write((const char*)(&offer), sizeof(JobOffer));
		}
	}

	fileIn.close();
	fileOut.close();
}
//Bonus2

void addJobOffers(JobOffer * jobOffers, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Job offer: " << i + 1 << endl << "Enter company name: " << endl;
		cin.getline(jobOffers[i].companyName, MAX_COMPANY_NAME_LEN + 1);
		cout << "Enter coworkers count: " << endl;
		cin >> jobOffers[i].coworkersCount;
		cout << "Enter paid leave days: " << endl;
		cin >> jobOffers[i].paidPaysOff;
		cout << "Enter project pay: " << endl;
		cin >> jobOffers[i].projectSalary;

		cin.ignore();
	}
}

void displayAllOffers(const char* filePath)
{
	ifstream in(filePath, ios::in | ios::binary);
	if (!in.is_open())
	{
		cout << ERROR_MS << endl;
		return;
	}

	JobOffer offer;
	while (in.read((char*)&offer, sizeof(offer)))
	{
		cout << "Company name: " << offer.companyName << endl;
		cout << "Number of coworkers: " << offer.coworkersCount << endl;
		cout << "Number of vacation days: " << offer.paidPaysOff << endl;
		cout << "Salary: $" << offer.projectSalary << endl;
		cout << endl;
	}
	in.close();
}

int main()
{
	JobOffer jobOffers[10];
	int n = 0;

	{
		cout << "How many job offers would you like to add?" << endl;
		cin >> n;

		cin.ignore();

		addJobOffers(jobOffers, n);
	}

	{
		ofstream ofs(BINARY_FILE_NAME, ios::out | ios::binary | ios::app);
		if (!ofs.is_open()) {
			cout << ERROR_MS << endl;
			return 1;
		}

		for (int i = 0; i < n; i++) {
			saveToFile(jobOffers[i], ofs);
		}

		ofs.close();
	}

	displayAllOffers(BINARY_FILE_NAME);

	{
		long long minSalary = 0;

		cout << "Enter minimum salary: " << endl;
		cin >> minSalary;

		filterOffers(BINARY_FILE_NAME, minSalary);
	}

	{
		cout << "Enter company name: " << endl;
		char companyName[26];
		cin.ignore();
		cin.getline(companyName, 26);

		if (existOffer(BINARY_FILE_NAME, companyName)) {
			cout << companyName << " exists" << endl;
		}
		else {
			cout << companyName << " does not exist" << endl;
		}
	}

	perfectOffer(BINARY_FILE_NAME, 5, 25, 1234);


}

