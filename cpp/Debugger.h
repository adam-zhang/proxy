#ifndef __DEBUGGER__H
#define __DEBUGGER__H

#include <string>
#include <sstream>

class Debugger
{
	public:
		static void write(const std::string&);
		
		template<typename T>
		static void write(const std::string& notice, T& value)
		{
			std::stringstream ss;
			ss << notice <<  ":" << value;
			write(ss.str());
		}
};
#endif//__DEBUGGER__H
