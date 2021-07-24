// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EffectMaker.h"
#include "BuffOnAttack.generated.h"

class ALogicEngine;
class ATowerEntity;


/**
 * 
 */
UCLASS()
class CELLS_API UBuffOnAttack : public UEffectMaker
{
	GENERATED_BODY()

public:
	UBuffOnAttack();

	virtual bool isBuffOnAttack() const { return true; }

protected:
};
