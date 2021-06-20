#pragma once

#include <iostream>

enum class ArmorType
{
	Standard,
	Resilient,
	Heavy,
	Light
};

inline std::ostream& operator<<(std::ostream& os_p, ArmorType type_p)
{
	switch (type_p)
	{
	case ArmorType::Standard:
		os_p << "Standard";
		break;
	case ArmorType::Resilient:
		os_p << "Resilient";
		break;
	case ArmorType::Heavy:
		os_p << "Heavy";
		break;
	case ArmorType::Light:
		os_p << "Light";
		break;
	}
	return os_p;
}

inline ArmorType fromStringToArmorType(std::string const& str_p)
{
	return ArmorType::Standard;
}
