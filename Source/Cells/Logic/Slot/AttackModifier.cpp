// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackModifier.h"

#include <sstream>

AAttackModifier::AAttackModifier() : ASlot(true)
{}

FString AAttackModifier::buildBasicDesc()
{
	std::stringstream ss_l;
	ss_l << "Deal " << damage << " damages of type " << _damageType << " with an attack speed of " << 1 / speed
		<< " attacks per second with a range of " << range << ".";

	std::string str_l = ss_l.str();
	return FString(str_l.c_str());
}
