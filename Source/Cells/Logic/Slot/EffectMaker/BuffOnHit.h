// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EffectMaker.h"
#include "BuffOnHit.generated.h"

class ALogicEngine;
class AMobEntity;
class ATowerEntity;

class InterfaceBuffOnHit : public InterfaceEffectMaker
{
public:
	virtual bool isBuffOnHit() const { return true; }

    virtual void spawnEffectOnHit(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target) const = 0;
};

/**
 * 
 */
UCLASS()
class CELLS_API UBuffOnHit : public UEffectMaker, public InterfaceBuffOnHit
{
	GENERATED_BODY()

public:
	UBuffOnHit();

    virtual void spawnEffectOnHit(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target) const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "BuffOnHit")
		void spawnEffectImpl(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target) const;

protected:
};
