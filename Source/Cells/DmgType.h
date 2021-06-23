// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>

#include "DmgType.generated.h"

UENUM(BlueprintType)
enum class DmgType : uint8
{
	Corrosive,
	Pearcent,
	Standard
};

inline std::ostream& operator<<(std::ostream& os_p, DmgType type_p)
{
	switch (type_p)
	{
	case DmgType::Corrosive:
		os_p << "Corrosive";
		break;
	case DmgType::Pearcent:
		os_p << "Pearcent";
		break;
	case DmgType::Standard:
		os_p << "Standard";
		break;
	}
	return os_p;
}

inline DmgType fromStringToDmgType(std::string const& str_p)
{
	if (str_p == "Corrosive")
	{
		return DmgType::Corrosive;
	}
	if (str_p == "Pearcent")
	{
		return DmgType::Pearcent;
	}
	return DmgType::Standard;
}
