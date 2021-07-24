// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EffectMaker.h"
#include "BuffOnEquip.generated.h"

class ALogicEngine;
class ATowerEntity;
class UBuffEquipEffect;

/**
 *
 */
UCLASS()
class CELLS_API UBuffOnEquip : public UEffectMaker
{
	GENERATED_BODY()

public:
	UBuffOnEquip();

	virtual bool isBuffOnEquip() const { return true; }

	// called when equiped
	virtual void equip(ALogicEngine* engine, ATowerEntity* tower);
	// called when un-equiped
	virtual void unequip(ALogicEngine* engine, ATowerEntity* tower);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "BuffOnEquip")
		UBuffEquipEffect * spawnEffectOnEquipImpl(ALogicEngine* engine, ATowerEntity* tower) const;

protected:
	// pointer to the buff (to apply and revert buff)
	UPROPERTY()
		UBuffEquipEffect * _buff;
};
