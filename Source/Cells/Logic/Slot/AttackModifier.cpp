// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackModifier.h"

#include <sstream>
#include <iomanip>
#include <cmath>

UAttackModifier::UAttackModifier() : USlot(true, false)
{}

namespace
{
	float cround(float val_p)
	{
		return std::ceil(val_p * 100.f) / 100.f;
	}
}

FString UAttackModifier::buildBasicDesc()
{
	std::stringstream ss_l;
	ss_l << "Deal <YellowReg>" << cround(damage) << "</> damages of type <YellowReg>" << _damageType << "</> with an attack speed of <YellowReg>" << cround(speed)
		<< "</> attacks per second with a range of <YellowReg>" << cround(range) << "</>.";

	std::string str_l = ss_l.str();
	return FString(str_l.c_str());
}
