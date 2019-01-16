#ifndef __TRIM__H
#define __TRIM__H

using namespace std;

template<typename T>
std::basic_string<T> trim_left(const std::basic_string<T>& value)
{
	ssize_t index = -1;
	for(ssize_t i = 0; i != value.size(); ++i)
	{
		if (value[i] == ' ' || value[i] == '\t')
			index = i;
		else
			break;
	}
	return value.substr(index + 1); // + 1);
}

template<typename T>
std::basic_string<T> trim_right(const std::basic_string<T>& value)
{
	size_t index = value.size() - 1;
	for(size_t i = value.size() - 1; i != -1; --i)
	{
		if (value[i] == ' ' || value[i] == '\t')
			index = i;
		else 
			break;
	}
	return value.substr(0, index);
}

template<typename T>
std::basic_string<T> trim(const std::basic_string<T>& value)
{
	return trim_left(trim_right(value));
}

#endif//__TRIM__H
