#include "HugeInteger.h"
#include <string>

HugeInteger::HugeInteger(const std::string& val) {
	// Loop variable

	unsigned int i = 0;
	// Throw exception if empty
	if (val == "") {
		throw std::out_of_range("empty string.");
	}
	// Check if first digit is '-'
	if (val[0] == '-') {
		// Skip element
		i++;
	}
	for (; i < val.length(); i++) {
		// Check if array consists of valid integers
		if ((int)val[i] >= 48 && (int)val[i] <= 57) {

		}
		else {
			throw std::out_of_range("Invalid input.");
		}
	}
	for (int b = val.length() - 1; b >= 0; b--) {
		int temp = (int)val[b] - 48;
		//std::cout << "input string is "<< val << "temp is : " << temp << std::endl;
		if (val[b] == '-') {
			value.emplace(value.begin(), -1);
		}
		else {
			value.emplace(value.begin(), temp);
		}
	}

}

HugeInteger::HugeInteger(int n) {
	// Check if input too small
	if (n < 1) {
		throw std::out_of_range("Invalid input.");
	}

	// Create random string
	for (int i = 0; i < n; i++) {
		int f = rand() % 10;
		// Check if first digit is 0
		while (i == 0 && f == 0) {
			f = rand() % 10;
		}
		// Append to string
		value.emplace_back(f);
	}
}

HugeInteger::HugeInteger(std::vector<int>& k) {
	value = k;
}

HugeInteger HugeInteger::add(const HugeInteger& h) {
	// TODO

	int length1 = h.value.size();
	int length2 = this->value.size();
	std::vector<int> hval = h.value;
	//HugeInteger output = HugeInteger("0");
	//std::cout << "hvalue: " << h.value[0] << ", thisval: " << this->value[0] << std::endl;

	// Check if inputs are 0
	if (h.value[0] == 0 && this->value[0] == 0) {
		HugeInteger out = HugeInteger("0");
		return out;
	}
	if (h.value[0] == -1 && this->value[0] == 0) {
		//hval.erase(hval.begin());
		HugeInteger out = HugeInteger(hval);
		return out;
	}
	if (h.value[0] != -1 && this->value[0] == 0) {
		//hval.emplace(hval.begin(), -1);
		HugeInteger out = HugeInteger(hval);
		return out;
	}
	if (h.value[0] == 0) {
		HugeInteger out = HugeInteger(this->value);
		return out;
	}
	if (this->value[0] == 0) {

		HugeInteger out = HugeInteger(hval);
		return out;
	}
	// If both negative

	std::string output = "";
	// Case where both numbers are negative
	if (h.value[0] == -1 && this->value[0] == -1) {
		int compare = HugeInteger::compareTo(h);
		int length;
		// Compare the length of both the integers
		// Pick the longest one
		if (compare == 1) {
			length = length1;
		}
		else if (compare == -1) {
			length = length2;
		}
		else {
			length = length1;
		}
		int carry = 0;
		// Addition loop
		for (int i = 1; length - i >= 1; i++) {
			int temp = 0;
			// Assign different values when the vectors are not equal in size
			if (compare == 1) {
				if (length2 - i < 1) {
					temp = h.value[length1 - i];
				}
				else {
					temp = h.value[length1 - i] + this->value[length2 - i];
				}
			}
			else if (compare == -1) {
				if (length1 - i < 1) {
					temp = this->value[length2 - i];
				}
				else {
					temp = h.value[length1 - i] + this->value[length2 - i];
				}
			}
			else {
				temp = h.value[length1 - i] + this->value[length2 - i];
			}
			// Carry
			if (carry == 1) {
				temp += 1;
				carry = 0;

			}
			if (temp > 9) {
				temp = temp % 10;
				carry = 1;

			}
			output.insert(0, std::to_string(temp));
		}
		if (carry == 1) {
			output.insert(0, "1");
		}
		output.insert(0, "-");
	}

	// If second one negative
	else if (h.value[0] == -1 && this->value[0] != -1) {
		// Create new vector and remove first element
		int carry = 0;
		int length;
		std::vector<int> newval = h.value;
		newval.erase(newval.begin());
		HugeInteger h2 = HugeInteger(newval);
		length1 = h2.value.size();
		length2 = this->value.size();
		int compare = HugeInteger::compareTo(h2);
		if (compare == 1) {
			length = length2;
		}
		else if (compare == -1) {
			length = length1;
		}
		else {
			length = length1;
		}
		for (int i = 1; length - i >= 0; i++) {
			int temp = 0;
			if (compare == 1) {
				if (length1 - i < 0) {
					temp = this->value[length2 - i];
				}
				else {
					temp = this->value[length2 - i] - h2.value[length1 - i];
				}
			}
			else if (compare == -1) {
				if (length2 - i < 0) {
					temp = -1 * h2.value[length1 - i];
				}
				else {
					temp = this->value[length2 - i] - h2.value[length1 - i];
				}
			}
			else {
				temp = this->value[length2 - i] - h2.value[length1 - i];
			}
			if (carry == -1) {
				temp = temp - 1;
				carry = 0;

			}
			if (temp < 0) {
				temp = 10 + temp;
				carry = -1;
			}
			output.insert(0, std::to_string(temp));
		}
		for (; output[0] == '0' && output.length() != 1;) {
			output.erase(0, 1);
		}
		if (carry == -1) {
			output.insert(0, "-");
		}
	}

	// If first negative
	else if (h.value[0] != -1 && this->value[0] == -1) {
		// For sure this value is smaller than hvalue
		// If same length, remove -1 from thisvalue, subtract thisvalue from hvalue
		// 
		int carry = 0;

		int length;
		this->value.erase(this->value.begin());
		length1 = h.value.size();
		length2 = this->value.size();
		int compare = HugeInteger::compareTo(h);
		if (compare == 1) {
			length = length2;
		}
		else if (compare == -1) {
			length = length1;
		}
		else {
			length = length1;
		}
		for (int i = 1; length - i >= 0; i++) {
			int temp = 0;
			if (compare == 1) {
				if (length1 - i < 0) {
					temp = this->value[length2 - i];
				}
				else {
					temp = this->value[length2 - i] - h.value[length1 - i];
				}
			}
			else if (compare == -1) {
				if (length2 - i < 0) {
					temp = -1 * h.value[length1 - i];
				}
				else {
					temp = this->value[length2 - i] - h.value[length1 - i];
				}
			}
			else {
				temp = this->value[length2 - i] - h.value[length1 - i];
			}
			if (carry == -1) {
				temp = temp - 1;
				carry = 0;

			}
			if (temp < 0) {
				temp = 10 + temp;
				carry = -1;
			}
			output.insert(0, std::to_string(temp));
		}
		for (; output[0] == '0' && output.length() != 1;) {
			output.erase(0, 1);
		}

		//compare = HugeInteger::compareTo(h);
		if (compare == 1) {
			output.insert(0, "-");
		}
		//std::cout << "hvalue: " << h.value[0] << ", thisval: " << this->value[0] << std::endl;
	}




	//std::cout << "hvalue: " << h.value[0] << ", thisval: " << this->value[0] << std::endl;

	// If second one negative


	HugeInteger out = HugeInteger(output);

	return out;
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	// TODO
	// TODO
	int length1 = h.value.size();
	int length2 = this->value.size();
	std::vector<int> hval = h.value;
	//HugeInteger output = HugeInteger("0");
	//std::cout << "hvalue: " << h.value[0] << ", thisval: " << this->value[0] << std::endl;
	std::string output = "";
	if (h.value[0] == 0 && this->value[0] == 0) {
		HugeInteger out = HugeInteger("0");
		return out;
	}
	if (h.value[0] == -1 && this->value[0] == 0) {
		hval.erase(hval.begin());
		HugeInteger out = HugeInteger(hval);
		return out;
	}
	if (h.value[0] != -1 && this->value[0] == 0) {
		hval.emplace(hval.begin(), -1);
		HugeInteger out = HugeInteger(hval);
		return out;
	}
	if (h.value[0] == 0) {
		HugeInteger out = HugeInteger(this->value);
		return out;
	}
	if (this->value[0] == 0) {

		HugeInteger out = HugeInteger(hval);
		return out;
	}
	// If both positive
	if (h.value[0] != -1 && this->value[0] != -1) {
		int carry = 0;
		int compare = HugeInteger::compareTo(h);
		int length;
		if (compare == 1) {
			length = length2;
		}
		else if (compare == -1) {
			length = length1;
		}
		else {
			length = length1;
		}
		for (int i = 1; length - i >= 0; i++) {
			int temp = 0;
			if (compare == 1) {
				if (length1 - i < 0) {
					temp = this->value[length2 - i];
				}
				else {
					temp = this->value[length2 - i] - h.value[length1 - i];
				}
			}
			else if (compare == -1) {
				if (length2 - i < 0) {
					temp = -h.value[length1 - i];
				}
				else {
					temp = this->value[length2 - i] - h.value[length1 - i];
				}
			}
			else {
				temp = this->value[length2 - i] - h.value[length1 - i];
			}
			if (carry == -1) {
				temp = temp - 1;
				carry = 0;

			}
			if (temp < 0) {
				temp = 10 + temp;
				carry = -1;
			}
			output.insert(0, std::to_string(temp));
		}
		for (; output[0] == '0' && output.length() != 1;) {
			output.erase(0, 1);
		}
		if (carry == -1) {
			output.insert(0, "-");
		}
	}
	// If both negative
	else if (h.value[0] == -1 && this->value[0] == -1) {
		int carry = 0;
		int i;
		int compare = HugeInteger::compareTo(h);
		int length;

		if (compare == 1) {
			length = length1;
		}
		else if (compare == -1) {
			length = length2;
		}
		else {
			length = length1;
		}
		for (i = 1; length - i >= 1; i++) {
			int temp = 0;
			if (compare == 1) {
				if (length2 - i < 1) {
					temp = -1 * h.value[length1 - i];
				}
				else {
					temp = this->value[length2 - i] - h.value[length1 - i];
				}
			}
			else if (compare == -1) {
				if (length1 - i < 1) {
					temp = this->value[length2 - i];
				}
				else {
					temp = this->value[length2 - i] - h.value[length1 - i];
				}
			}
			else {
				temp = this->value[length2 - i] - h.value[length1 - i];
			}
			if (carry == -1) {
				temp -= 1;
				carry = 0;

			}
			if (temp < 0) {
				temp = 10 + temp;
				carry = -1;

			}
			output.insert(0, std::to_string(temp));
		}
		for (; output[0] == '0' && output.length() != 1;) {
			output.erase(0, 1);
		}
		if (carry == 0 && output[0] != '0') {
			output.insert(0, "-");
		}
	}
	// If this is negative
	else if (h.value[0] != -1 && this->value[0] == -1) {

		int length;
		this->value.erase(this->value.begin());
		length1 = h.value.size();
		length2 = this->value.size();

		int compare = HugeInteger::compareTo(h);

		if (compare == 1) {
			length = length2;
		}
		else if (compare == -1) {
			length = length1;
		}
		else {
			length = length1;
		}
		int carry = 0;
		for (int i = 1; length - i >= 0; i++) {
			int temp = 0;
			if (compare == 1) {
				if (length1 - i < 0) {
					temp = this->value[length2 - i];
				}
				else {
					temp = h.value[length1 - i] + this->value[length2 - i];
				}
			}
			else if (compare == -1) {
				if (length2 - i < 0) {
					temp = h.value[length1 - i];
				}
				else {
					temp = h.value[length1 - i] + this->value[length2 - i];
				}
			}
			else {
				temp = h.value[length1 - i] + this->value[length2 - i];
			}
			//temp = h.value[length1 - i] + this->value[length2 - i];

			if (carry == 1) {
				temp += 1;
				carry = 0;

			}
			if (temp > 9) {
				temp = temp % 10;
				carry = 1;

			}
			output.insert(0, std::to_string(temp));
			//std::cout << "output:" << output << std::endl;
		}
		if (carry == 1) {
			output.insert(0, "1");
		}

		output.insert(0, "-");

		//output.insert(0, "-");
		//std::cout << "---hvalue: " << h.value[0] << ", thisval: " << this->value[0] << ", compare: " << compare << std::endl;
	}
	// If h is negative
	else if (h.value[0] == -1 && this->value[0] != -1) {
		int carry = 0;
		int i;
		int length;
		std::vector<int> newval = h.value;
		newval.erase(newval.begin());
		HugeInteger h2 = HugeInteger(newval);
		length1 = h2.value.size();
		length2 = this->value.size();
		int compare = HugeInteger::compareTo(h2);

		if (compare == 1) {
			length = length2;
		}
		else if (compare == -1) {
			length = length1;
		}
		else {
			length = length1;
		}

		for (int i = 1; length - i >= 0; i++) {
			int temp = 0;
			if (compare == 1) {
				if (length1 - i < 0) {
					temp = this->value[length2 - i];
				}
				else {
					temp = h2.value[length1 - i] + this->value[length2 - i];
				}
			}
			else if (compare == -1) {
				if (length2 - i < 0) {
					temp = h2.value[length1 - i];
				}
				else {
					temp = h2.value[length1 - i] + this->value[length2 - i];
				}
			}
			else {
				temp = h2.value[length1 - i] + this->value[length2 - i];
			}

			if (carry == 1) {
				temp += 1;
				carry = 0;

			}
			if (temp > 9) {
				temp = temp % 10;
				carry = 1;

			}
			output.insert(0, std::to_string(temp));
			//std::cout << "output:" << output << std::endl;
		}
		if (carry == 1) {
			output.insert(0, "1");
		}
		//for (; output[0] == '0' && output.length() != 1;) {
			//output.erase(0, 1);
		//}
		if (compare == -1) {
			//output.insert(0, "-");
		}
		//std::cout << "hsize: " << length1 << ", thissize: " << length2 << std::endl;
		//std::cout << "hvalue: " << h2.value[0] << ", thisval: " << this->value[0] << ", compare: " << compare << std::endl;
	}

	HugeInteger out = HugeInteger(output);
	return out;
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	// TODO
	int length1 = h.value.size();
	int length2 = this->value.size();
	//int sum = 0;
	std::vector<int> result;
	// If one or both of inputs are zero
	if ((length1 == 1 && h.value[0] == 0) || (length2 == 1 && this->value[0] == 0)) {
		result.emplace_back(0);
	}
	else {

		for (int b = 0; b < length1 + length2; b++) {
			result.emplace_back(0);
		}

		// debug code
		/*std::cout << "rowsum: ";
				for (int f = 0; f < rowsumsize; f++) {
					std::cout << rowsum[f];
				}
				std::cout << std::endl;
				std::cout << "result: ";

				int resultsize = result.size();
				for (int f = 0; f < resultsize; f++) {
					std::cout << result[f];
				}
				std::cout << std::endl;*/

				// Case for when both values are positive

		if (h.value[0] != -1 && this->value[0] != -1) {
			for (int i = 1; length2 - i >= 0; i++) {
				int temp = 0;
				std::vector<int> rowsum;
				int carry = 0;
				for (int j = 1; length1 - j >= 0; j++) {
					temp = h.value[length1 - j] * this->value[length2 - i];
					if (carry != 0) {
						temp += carry;
						carry = 0;
					}
					if (temp > 9) {
						carry = temp / 10;
						temp = temp % 10;
					}
					rowsum.emplace(rowsum.begin(), temp);
				}
				if (carry != 0) {
					rowsum.emplace(rowsum.begin(), carry);
				}
				for (int q = 1; i - q > 0; q++) {
					rowsum.emplace_back(0);
				}
				int rowsumsize = rowsum.size();
				int carry2 = 0;
				int temp2 = 0;
				int k = 1;
				for (; rowsumsize - k >= 0; k++) {
					temp2 = result[result.size() - k] + rowsum[rowsum.size() - k];
					if (carry2 == 1) {
						temp2 += 1;
						carry2 = 0;
					}
					if (temp2 > 9) {
						temp2 %= 10;
						carry2 = 1;
					}
					result[result.size() - k] = temp2;
				}
				if (carry2 == 1) {
					result[result.size() - k] += 1;
				}
			}
			int resultsize = result.size();
			for (int u = 0; result[u] == 0;) {
				resultsize = result.size();
				if (resultsize == 1) {
					break;
				}
				result.erase(result.begin());
			}
			// Both negative
		}
		else if (h.value[0] == -1 && this->value[0] == -1) {
			for (int i = 1; length2 - i >= 1; i++) {
				int temp = 0;
				std::vector<int> rowsum;
				int carry = 0;
				for (int j = 1; length1 - j >= 1; j++) {
					temp = h.value[length1 - j] * this->value[length2 - i];
					if (carry != 0) {
						temp += carry;
						carry = 0;
					}
					if (temp > 9) {
						carry = temp / 10;
						temp = temp % 10;
					}
					rowsum.emplace(rowsum.begin(), temp);
				}
				if (carry != 0) {
					rowsum.emplace(rowsum.begin(), carry);
				}
				for (int q = 1; i - q > 0; q++) {
					rowsum.emplace_back(0);
				}
				int rowsumsize = rowsum.size();
				int carry2 = 0;
				int temp2 = 0;
				int k = 1;
				for (; rowsumsize - k >= 0; k++) {
					temp2 = result[result.size() - k] + rowsum[rowsum.size() - k];
					if (carry2 == 1) {
						temp2 += 1;
						carry2 = 0;
					}
					if (temp2 > 9) {
						temp2 %= 10;
						carry2 = 1;
					}
					result[result.size() - k] = temp2;

				}
				if (carry2 == 1) {
					result[result.size() - k] += 1;
				}
			}
			int resultsize = result.size();
			for (int u = 0; result[u] == 0;) {
				resultsize = result.size();
				if (resultsize == 1) {
					break;
				}
				result.erase(result.begin());
			}
		}
		else if (h.value[0] == -1 && this->value[0] != -1) {
			for (int i = 1; length2 - i >= 0; i++) {
				int temp = 0;
				std::vector<int> rowsum;
				int carry = 0;
				for (int j = 1; length1 - j >= 1; j++) {
					temp = h.value[length1 - j] * this->value[length2 - i];
					if (carry != 0) {
						temp += carry;
						carry = 0;
					}
					if (temp > 9) {
						carry = temp / 10;
						temp = temp % 10;
					}
					rowsum.emplace(rowsum.begin(), temp);
				}
				if (carry != 0) {
					rowsum.emplace(rowsum.begin(), carry);
				}
				for (int q = 1; i - q > 0; q++) {
					rowsum.emplace_back(0);
				}
				int rowsumsize = rowsum.size();
				int carry2 = 0;
				int temp2 = 0;
				int k = 1;
				for (; rowsumsize - k >= 0; k++) {
					temp2 = result[result.size() - k] + rowsum[rowsum.size() - k];
					if (carry2 == 1) {
						temp2 += 1;
						carry2 = 0;
					}
					if (temp2 > 9) {
						temp2 %= 10;
						carry2 = 1;
					}
					result[result.size() - k] = temp2;
				}
				if (carry2 == 1) {
					result[result.size() - k] += 1;
				}
			}
			int resultsize = result.size();
			for (int u = 0; result[u] == 0;) {
				resultsize = result.size();
				if (resultsize == 1) {
					break;
				}
				result.erase(result.begin());
			}
			result.emplace(result.begin(), -1);
		}
		else if (h.value[0] != -1 && this->value[0] == -1) {
			for (int i = 1; length2 - i >= 1; i++) {
				int temp = 0;
				std::vector<int> rowsum;
				int carry = 0;
				for (int j = 1; length1 - j >= 0; j++) {
					temp = h.value[length1 - j] * this->value[length2 - i];
					if (carry != 0) {
						temp += carry;
						carry = 0;
					}
					if (temp > 9) {
						carry = temp / 10;
						temp = temp % 10;
					}
					rowsum.emplace(rowsum.begin(), temp);
				}
				if (carry != 0) {
					rowsum.emplace(rowsum.begin(), carry);
				}
				for (int q = 1; i - q > 0; q++) {
					rowsum.emplace_back(0);
				}
				int rowsumsize = rowsum.size();
				int carry2 = 0;
				int temp2 = 0;
				int k = 1;
				for (; rowsumsize - k >= 0; k++) {
					temp2 = result[result.size() - k] + rowsum[rowsum.size() - k];
					if (carry2 == 1) {
						temp2 += 1;
						carry2 = 0;
					}
					if (temp2 > 9) {
						temp2 %= 10;
						carry2 = 1;
					}
					result[result.size() - k] = temp2;
				}
				if (carry2 == 1) {
					result[result.size() - k] += 1;
				}
			}
			int resultsize = result.size();
			for (int u = 0; result[u] == 0;) {
				resultsize = result.size();
				if (resultsize == 1) {
					break;
				}
				result.erase(result.begin());
			}
			result.emplace(result.begin(), -1);
		}
	}
	HugeInteger output = HugeInteger(result);
	return output;
}

int HugeInteger::compareTo(const HugeInteger& h) {
	// TODO
	// Check if one or both is negative
	if (h.value[0] == -1 || this->value[0] == -1) {
		if (h.value[0] == -1 && this->value[0] != -1) {
			return 1;
		}
		else if (h.value[0] != -1 && this->value[0] == -1) {
			return -1;
		}

		else if (this->value.size() > h.value.size()) {
			return -1;
			// If this value is shorter than h value
		}
		else if (this->value.size() < h.value.size()) {
			return 1;
		}
		else {
			// If both lengths equal
			for (int i = 1; i < this->value.size(); i++) {
				if (this->value[i] < h.value[i]) {
					return 1;
				}
				if (this->value[i] > h.value[i]) {
					return -1;
				}
			}
			return 0;
		}
	}
	else {
		// If this value is longer than h value
		if (this->value.size() > h.value.size()) {
			return 1;
			// If this value is shorter than h value
		}
		else if (this->value.size() < h.value.size()) {
			return -1;
		}
		else {
			// If both lengths equal
			for (int i = 0; i < this->value.size(); i++) {
				if (this->value[i] < h.value[i]) {
					return -1;
				}
				if (this->value[i] > h.value[i]) {
					return 1;
				}
			}
			return 0;
		}
	}
	return 0;
}

std::string HugeInteger::toString() {
	std::string temp = "";
	//std::cout << value[0];
	for (int i = value.size() - 1; i >= 0; i--) {
		if (value[i] == -1) {
			temp.insert(0, "-");
		}
		else {
			temp.insert(0, std::to_string(value[i]));
		}

	}
	return temp;
}
