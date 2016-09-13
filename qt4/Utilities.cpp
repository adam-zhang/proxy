#include "Utilities.h"

void output(const QByteArray& data)
{
	QByteArray hex = data.toHex();
	for_each(hex.begin(), hex.end(), [](const char& c)
	{
		std::cout << hex << setw(2) << setfill('0') << (int)c;
	}
	);
}
