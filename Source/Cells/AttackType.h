#pragma once

#include <string>
#include <stdexcept>

#include "AttackType.generated.h"

UENUM(BlueprintType)
enum class AttackType : uint8
{
	Direct,
	Arc,
	Splash,
	Line
};

inline std::string to_string(AttackType type_p)
{
	switch (type_p)
	{
	case AttackType::Direct:
		return "Direct";
	case AttackType::Arc:
		return "Arc";
	case AttackType::Splash:
		return "Splash";
	case AttackType::Line:
		return "Line";
	};
	throw std::logic_error("missing implem for AttackType");
}

inline AttackType fromStringToAttackType(std::string const& str_p)
{
	if (str_p == "Arc")
	{
		return AttackType::Arc;
	}
	if (str_p == "Splash")
	{
		return AttackType::Splash;
	}
	if (str_p == "Line")
	{
		return AttackType::Line;
	}
	return AttackType::Direct;
}
