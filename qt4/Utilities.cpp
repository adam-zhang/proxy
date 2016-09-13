#include "Utilities.h"
#include <QByteArray>
#include <iostream>
#include <iomanip>


using namespace std;

void output(const QByteArray& data)
{
	QByteArray hexData = data.toHex();
	//for_each(hexData.begin(), hexData.end(), [](const char& c)
	cout << "begin data:";
	for(auto i = hexData.begin(); i != hexData.end(); ++i)
	{
		std::cout << hex << setw(2) << setfill('0') << (int)(*i) << " ";
	}
	std::cout << std::endl;
	std::cout << "end data;" << endl;
	//
}

void outputData(const QByteArray& data)
{
	cout << "begin output" << std::endl;
	std::cout << data.constData() << std::endl;
	cout << "end ouput" << endl;
}
