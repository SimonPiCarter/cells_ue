#pragma once

#include <iostream>

#include "ArmorType.generated.h"

UENUM(BlueprintType)
enum class ArmorType : uint8
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
	if (str_p == "Resilient")
	{
		return ArmorType::Resilient;
	}
	if (str_p == "Heavy")
	{
		return ArmorType::Heavy;
	}
	if (str_p == "Light")
	{
		return ArmorType::Light;
	}
	return ArmorType::Standard;
}
