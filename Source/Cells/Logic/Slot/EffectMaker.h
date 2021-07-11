// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slot.h"
#include "EffectMaker.generated.h"

class ALogicEngine;
class ATowerEntity;

/**
 * 
 */
UCLASS()
class CELLS_API UEffectMaker : public USlot
{
	GENERATED_BODY()

public:
	UEffectMaker();
	UEffectMaker(bool buffOnAttack_p, bool buffOnHit_p, bool buffOnEquip_p);

	bool isBuffOnAttack() const { return _buffOnAttack; }
	bool isBuffOnHit() const { return _buffOnHit; }
	bool isBuffOnEquip() const { return _buffOnEquip; }

private:
	bool _buffOnAttack;
	bool _buffOnHit;
	bool _buffOnEquip;
};