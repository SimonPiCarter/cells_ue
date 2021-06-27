// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerEntity.h"

#include <cassert>

#include "Logic/Slot/AttackModifier.h"

// Sets default values
ATowerEntity::ATowerEntity()
	: multAttackSpeed(1.)
	, multDamage(1.)
	, bonusRange(1.)
	, maxSlots(2)
	, cost(20)
	, attackModifier(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

TArray<USlot*> ATowerEntity::updateSlots(UAttackModifier* newAttackModifier, TArray<USlot*> newSlots)
{
	TArray<USlot*> removedSlots_l;
	if (attackModifier != newAttackModifier)
	{
		removedSlots_l.Add(attackModifier);
	}
	attackModifier = newAttackModifier;

	for (long i = 0; i < slots.Num() && i < newSlots.Num(); ++i)
	{
		if (newSlots[i] != slots[i])
		{
			removedSlots_l.Add(slots[i]);
		}
		slots[i] = newSlots[i];
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
	return (attackModifier ? attackModifier->damage : 1.) * multDamage;
}
/// @brief get full ranges (taking multiplier into account)
float ATowerEntity::getRange() const
{
	return (attackModifier ? attackModifier->range : 0.) + + bonusRange;
}
