// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slot.h"
#include "EffectMaker.generated.h"

class ALogicEngine;
class ATowerEntity;

class InterfaceEffectMaker
{
public:
	virtual bool isBuffOnAttack() const { return false; }
	virtual bool isBuffOnHit() const { return false; }
	virtual bool isBuffOnLastHit() const { return false; }
	virtual bool isBuffOnEquip() const { return false; }
};

/**
 * 
 */
UCLASS()
class CELLS_API UEffectMaker : public USlot, public InterfaceEffectMaker
{
	GENERATED_BODY()

public:
	UEffectMaker();
};
