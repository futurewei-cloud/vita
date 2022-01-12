#ifndef RANDOMSTRINGGENERATOR_H
#define RANDOMSTRINGGENERATOR_H

#include <string>
#include <vector>
#include <sodium.h>

namespace SRG{
class StringConfiguration {
public:
	bool lowercaseLetters = true;
	bool uppercaseLetters = true;
	bool numbers = true;
	bool specialCharacters = true;
	int length = 512;
};

class RandomStringGenerator {
private:
	StringConfiguration config;
	std::string base;
	std::string lowercaseLetters;
	std::string uppercaseLetters;
	std::string numbers;
	std::string specialCharacters;
	void initValues();
public:
	RandomStringGenerator(const StringConfiguration config);
	std::string getString() const;
};
}

#endif // RANDOMSTRINGGENERATOR_H