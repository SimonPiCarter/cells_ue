// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EffectMaker.h"
#include "BuffOnAttack.generated.h"

class ALogicEngine;
class ATowerEntity;

class InterfaceBuffOnAttack : public InterfaceEffectMaker
{
public:
	virtual bool isBuffOnAttack() const { return true; }
};

/**
 * 
 */
UCLASS()
class CELLS_API UBuffOnAttack : public UEffectMaker, public InterfaceBuffOnAttack
{
	GENERATED_BODY()

public:
	UBuffOnAttack();

protected:
};
