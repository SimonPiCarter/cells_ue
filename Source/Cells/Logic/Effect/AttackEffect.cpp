// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackEffect.h"
#include "../../MobEntity.h"
#include "../../TowerEntity.h"
#include "../Slot/EffectMaker/BuffOnHit.h"

UAttackEffect::UAttackEffect() : UEffect(), _damage(0.), _dmgType(DmgType::Standard), _lethal(true), _primary(false)
{}

void UAttackEffect::runEffect(float elapsedTime_p)
{
	// multiplier based on damage and armor types
		double mult_l = 1.;
	// Standard vs Heavy : 50%
	// Standard vs Light : 150%
	if (_dmgType == DmgType::Standard)
	{
		if (_mobTarget->getArmorType() == ArmorType::Heavy)
		{
			mult_l = 0.5;
		}
		else if (_mobTarget->getArmorType() == ArmorType::Light)
		{
			mult_l = 1.5;
		}
	}
	// Pearcent vs Heavy : 150%
	// Pearcent vs Light : 50%
	if (_dmgType == DmgType::Pearcent)
	{
		if (_mobTarget->getArmorType() == ArmorType::Heavy)
		{
			mult_l = 1.5;
		}
		else if (_mobTarget->getArmorType() == ArmorType::Light)
		{
			mult_l = 0.5;
		}
	}
	// Corrosive vs Resilient : 50%
	// Corrosive vs Light : 150%
	// Corrosive vs Heavy : 150%
	if (_dmgType == DmgType::Corrosive)
	{
		if (_mobTarget->getArmorType() == ArmorType::Resilient)
		{
			mult_l = 0.5;
		}
		else if (_mobTarget->getArmorType() == ArmorType::Light)
		{
			mult_l = 1.5;
		}
		else if (_mobTarget->getArmorType() == ArmorType::Heavy)
		{
			mult_l = 1.5;
		}
	}

	float dmg_l = mult_l * _damage * _mobTarget->damageMultiplier;
	if(!_lethal)
	{
		dmg_l = std::min(dmg_l, _mobTarget->hitpoint-1);
	}
	if(dmg_l>1e-5)
	{
		_mobTarget->damage(dmg_l);
	}

	if(_primary)
	{
		// Check tower for buff on hit effects
		for(USlot const * slot_l : source->slots)
		{
			if(slot_l->_isEffectMaker)
			{
				UEffectMaker const * maker_l = static_cast<UEffectMaker const *>(slot_l);
				if(maker_l->isBuffOnHit())
				{
					UBuffOnHit const * bufferOnHit_l = static_cast<UBuffOnHit const *>(maker_l);
					bufferOnHit_l->spawnEffectOnHit(logic, source, _mobTarget);
				}
			}
		}
	}

	over = true;
}
