#include <iostream> // for overload << & >> and debug for

class str {
public:
	str() { // constructor empty
		length = 0;
		string = new char[length];
	}
	str(const char* data) { // constr (char*)
		for (length = 0; data[length] != '\0'; length++); // measurement length

		string = new char[length + 1];
		for (unsigned i = 0; i < length; i++)
			string[i] = data[i];
		string[length] = '\0';
	}
	str(char data) { // constructor (char)
		length = 1;
		string = new char;
		*string = data;
	}
	str(const str & other) { // constr (class)
		length = other.length;

		string = new char[length + 1];
		for (unsigned i = 0; i < length; i++)
			string[i] = other.string[i];
		string[length] = '\0';
	}
	~str() { // destructor 
		delete[] string;
		string = nullptr;
	}

	void operator = (const char* data) { // overload = (char array)
		delete[] string;

		for (length = 0; data[length] != '\0'; length++); // measurement length

		string = new char[length + 1];
		for (unsigned i = 0; i < length; i++)
			string[i] = data[i];
		string[length] = '\0';
	}

	void operator = (const str & other) { // overload = (class)
		delete[] string;

		length = other.length;

		string = new char[length + 1];
		for (unsigned i = 0; i < length; i++)
			string[i] = other.string[i];
		string[length] = '\0';
	}

	void operator = (const char data) { // overload = (char)
		length = 1;
		string = new char;
		*string = data;
	}

	char& operator [] (unsigned i) { // overload []
		if (length > i)
			return string[i];
	}

	int get_length() { // getter for length
		return length;
	}

	bool operator == (const char* data) { // check if == char*
		for (int i = 0; string[i] != '\0'; i++) {
			if (string[i] == data[i])
				continue;
			else
				return 0;
		}

		return 1;
	}
	bool operator != (const char* data) { // check if != char*
		for (int i = 0; string[i] != '\0'; i++) {
			if (string[i] == data[i])
				continue;
			else return 1;
		}

		return 0;
	}
	bool operator == (str& other) { // check if == class
		if (length == other.length) {
			for (unsigned i = 0; i < length; i++) {
				if (string[i] == other.string[i])
					continue;
				else return 0;
			}
		}
		else return 0;
		
		return 1;
	}
	bool operator != (str& other) { // check if != class
		if (length == other.length) {
			for (unsigned i = 0; i < length; i++) {
				if (string[i] == other.string[i])
					continue;
				else return 1;
			}
		}
		else return 1;

		return 0;
	}


	str operator * (unsigned x) { // string multiply
		str temp;

		temp.length = length * x;
		temp.string = new char[temp.length + 1];

		int j = 0;
		for (unsigned i = 0; i < x; i++) {
			for (unsigned p = 0; p < length; j++, p++)
				temp.string[j] = string[p];
		}

		temp.string[temp.length] = '\0';

		return temp;
	}

	void operator *= (unsigned x) { // string multiply
		char* temp = string;
		unsigned temp_len = length;

		length = length * x;
		string = new char[length + 1];

		int j = 0;
		for (unsigned i = 0; i < x; i++) {
			for (unsigned p = 0; p < temp_len; j++, p++)
				string[j] = temp[p];
		}

		string[length] = '\0';
	}

	char* string;

	friend str operator + (const str& other1, const str& other); // return string + string 
	friend str operator + (const str& other, const char* data);  // return string + char arr
	friend str operator + (const char* data, const str& other);  // return char arr + string

	friend std::ostream& operator << (std::ostream& os, const str& cl); // overload <<
	friend std::istream& operator >> (std::istream& os, str& cl); // overload >>
private:
	unsigned length;
};

std::ostream& operator << (std::ostream& os, const str& cl) { // overload <<
	os << cl.string;
	return os;
}
std::istream& operator >> (std::istream& is, str& cl) { // overload >>
	char* temp = new char[10000];
	is >> temp;

	cl = temp;

	return is;
}
	
str operator + (const str& other1, const str& other) { // return string + string
	str temp;

	temp.length = other1.length + other.length;
	temp.string = new char[temp.length + 1];

	unsigned i = 0;
	for (; i < other1.length; i++)
		temp.string[i] = other1.string[i];
	for (int j = 0; i < temp.length; i++, j++)
		temp.string[i] = other.string[j];
	temp.string[temp.length] = '\0';

	return temp;
}

str operator + (const str& other, const char* data){ // return string + char array
	str temp;

	temp.length = 0;
	for (; data[temp.length] != '\0'; temp.length++);
	temp.length += other.length;

	temp.string = new char[temp.length + 1];

	unsigned i = 0;
	for (; other.string[i] != '\0'; i++)
		temp.string[i] = other.string[i];
	for (int j = 0; i < temp.length; i++, j++)
		temp.string[i] = data[j];
	temp.string[temp.length] = '\0';

	return temp;
}

str operator + (const char* data, const str& other) { // return string + char array
	str temp;

	temp.length = 0;
	for (; data[temp.length] != '\0'; temp.length++);
	temp.length += other.length;

	temp.string = new char[temp.length + 1];

	unsigned i = 0;
	for (; data[i] != '\0'; i++)
		temp.string[i] = data[i];
	for (int j = 0; i < temp.length; i++, j++)
		temp.string[i] = other.string[j];
	temp.string[temp.length] = '\0';

	return temp;
}