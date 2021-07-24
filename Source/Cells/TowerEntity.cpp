// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerEntity.h"

#include <cassert>

#include "Logic/Slot/AttackModifier.h"
#include "Logic/Effect/Buff/BuffEffect.h"
#include "Logic/Slot/EffectMaker/BuffOnEquip.h"

// Sets default values
ATowerEntity::ATowerEntity()
	: multAttackSpeed(1.)
	, multDamage(1.)
	, bonusRange(0.)
	, maxSlots(2)
	, cost(20)
	, attackModifier(nullptr)
	, _currentTarget(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	slots.Add(nullptr);

}

// Called when the game starts or when spawned
void ATowerEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<USlot*> ATowerEntity::updateSlots(ALogicEngine * logic, UAttackModifier* newAttackModifier, TArray<USlot*> newSlots)
{
	TArray<USlot*> newSlots_l;
	TArray<USlot*> removedSlots_l;
	if (attackModifier != newAttackModifier)
	{
		if (attackModifier)
		{
			removedSlots_l.Add(attackModifier);
		}
		newSlots_l.Add(newAttackModifier);
	}
	attackModifier = newAttackModifier;

	for (long i = 0; i < slots.Num() && i < newSlots.Num(); ++i)
	{
		if (newSlots[i] != slots[i])
		{
			if (slots[i])
			{
				removedSlots_l.Add(slots[i]);
			}
			newSlots_l.Add(newSlots[i]);
		}
		slots[i] = newSlots[i];
	}

	for(USlot * slot_l : newSlots_l)
	{
		if(slot_l->_isEffectMaker)
		{
			UEffectMaker * maker_l = static_cast<UEffectMaker *>(slot_l);
			if(maker_l->isBuffOnEquip())
			{
				maker_l->equip(logic, this);
			}
		}
	}

	for(USlot * slot_l : removedSlots_l)
	{
		if(slot_l->_isEffectMaker)
		{
			UEffectMaker * maker_l = static_cast<UEffectMaker *>(slot_l);
			if(maker_l->isBuffOnEquip())
			{
				maker_l->unequip(logic, this);
			}
		}
	}

	return removedSlots_l;
}

/// @brief get full attack speed (taking multiplier into account)
float ATowerEntity::getAttackSpeed() const
{
	return (attackModifier ? attackModifier->speed : 1.) * multAttackSpeed;
}

/// @brief get full damages (taking multiplier into account)
float ATowerEntity::getDamage() const
{
	return (attackModifier ? attackModifier->damage : 1.) * std::max(0.f, multDamage);
}
/// @brief get full ranges (taking multiplier into account)
float ATowerEntity::getRange() const
{
	return (attackModifier ? attackModifier->range : 0.) + bonusRange;
}

void ATowerEntity::registerBuff(UBuffEffect * buff_p) { _buffs[buff_p->getId()] = buff_p; }
void ATowerEntity::unregisterBuff(UBuffEffect * buff_p) { _buffs.erase(buff_p->getId()); }
bool ATowerEntity::isRegistered(UBuffEffect * buff_p) { return _buffs.find(buff_p->getId()) != _buffs.end(); }
UBuffEffect * ATowerEntity::getRegisteredBuff(std::string const & id_p) { return _buffs.find(id_p) != _buffs.end() ? _buffs.find(id_p)->second : nullptr; }
