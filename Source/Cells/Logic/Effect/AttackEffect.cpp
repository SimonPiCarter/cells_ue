// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackEffect.h"
#include "../../MobEntity.h"

void AAttackEffect::runEffect(float elapsedTime_p)
{
	// multiplier based on damage and armor types
		double mult_l = 1.;
	// Standard vs Heavy : 50%
	// Standard vs Light : 150%
	if (dmgType == DmgType::Standard)
	{
		if (target->getArmorType() == ArmorType::Heavy)
		{
			mult_l = 0.5;
		}
		else if (target->getArmorType() == ArmorType::Light)
		{
			mult_l = 1.5;
		}
	}
	// Pearcent vs Heavy : 150%
	// Pearcent vs Light : 50%
	if (dmgType == DmgType::Pearcent)
	{
		if (target->getArmorType() == ArmorType::Heavy)
		{
			mult_l = 1.5;
		}
		else if (target->getArmorType() == ArmorType::Light)
		{
			mult_l = 0.5;
		}
	}
	// Corrosive vs Resilient : 50%
	// Corrosive vs Light : 150%
	// Corrosive vs Heavy : 150%
	if (dmgType == DmgType::Corrosive)
	{
		if (target->getArmorType() == ArmorType::Resilient)
		{
			mult_l = 0.5;
		}
		else if (target->getArmorType() == ArmorType::Light)
		{
			mult_l = 1.5;
		}
		else if (target->getArmorType() == ArmorType::Heavy)
		{
			mult_l = 1.5;
		}
	}

	target->damage(mult_l * damage);

	over = true;
}
