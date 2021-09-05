#ifndef CCELL_HPP
#define CCELL_HPP

#include <iostream>
class CCell {
public:
	CCell (){}
	CCell (double _temp) : temp{_temp}{}
	bool active = false;
	bool source = false;
	double temp = 0;
	double temp_nu = 0;
	double temp_nup1 = 0;
	friend std::ostream& operator << (std::ostream& os, const CCell& cell) { return os << cell.temp; }
};
#endif