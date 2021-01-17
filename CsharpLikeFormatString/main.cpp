#include <iostream>
#include <string>
#include <sstream>
#include <vector>

template<typename T>
void ToStrings(std::vector<std::string>& result, T value)
{
	std::ostringstream oss{};
	oss << value;
	result.push_back(oss.str());
}

template<typename First, typename ...Rest>
void ToStrings(std::vector<std::string>& result, First value, Rest ...rest)
{
	std::ostringstream oss{};
	oss << value;
	result.push_back(oss.str());

	ToStrings(result, rest...);
}

std::string StringFormat(const std::string& fstr)
{
	return fstr;
}

template<typename ...Args>
std::string StringFormat(const std::string& fstr, Args ...args)
{
	// args를 vector<string>으로 변경
	std::vector<std::string> strings{};
	ToStrings(strings, args...);

	// {n}을 찾아서 대체하기
	std::string result{ fstr };

	auto n = strings.size();
	for (std::vector<std::string>::size_type i = 0; i < n; i++)
	{
		std::ostringstream oss{};
		oss << '{' << i << '}';
		std::string target = oss.str();

		std::string::size_type pos;
		do
		{
			pos = result.find(target);
			if (pos != std::string::npos)
			{
				result.replace(result.begin() + pos, result.begin() + pos + 3, strings.at(i));
			}
		} while (pos != std::string::npos);
	}

	return result;
}

int main()
{
	std::string formated = StringFormat("This {0} is {1} Format {2} String {0} Wow! {3}", 1, 2.2, "Hello?", 1.5F);
	std::cout << formated << std::endl;

	return 0;
}