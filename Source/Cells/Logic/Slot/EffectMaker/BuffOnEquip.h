// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EffectMaker.h"
#include "BuffOnEquip.generated.h"

class ALogicEngine;
class ATowerEntity;
class UBuffEquipEffect;

class InterfaceBuffOnEquip : public InterfaceEffectMaker
{
public:
	virtual bool isBuffOnEquip() const { return true; }

    virtual void equip(ALogicEngine* engine, ATowerEntity* tower) = 0;
    virtual void unequip(ALogicEngine* engine, ATowerEntity* tower) = 0;
};

/**
 * 
 */
UCLASS()
class CELLS_API UBuffOnEquip : public UEffectMaker, public InterfaceBuffOnEquip
{
	GENERATED_BODY()

public:
	UBuffOnEquip();

	// called when equiped
	void equip(ALogicEngine* engine, ATowerEntity* tower);
	// called when un-equiped
	void unequip(ALogicEngine* engine, ATowerEntity* tower);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "BuffOnEquip")
		UBuffEquipEffect * spawnEffectOnEquipImpl(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target) const;

protected:
	// pointer to the buff (to apply and revert buff)
	UBuffEquipEffect * _buff;
};
