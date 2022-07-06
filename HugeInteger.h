#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>
#include <vector>

class HugeInteger
{
private:
	std::vector<int> value;
public:
	// Required methods
	HugeInteger(const std::string& val);
	HugeInteger(int n);
	HugeInteger(std::vector<int>& k);
	HugeInteger add(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString();
};

#endif /* HUGEINTEGER_H_ */