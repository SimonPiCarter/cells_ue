// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EffectMaker.h"
#include "BuffOnLastHit.generated.h"

class ALogicEngine;
class AMobEntity;
class ATowerEntity;

/**
 * 
 */
UCLASS()
class CELLS_API UBuffOnLastHit : public UEffectMaker
{
	GENERATED_BODY()

public:
	UBuffOnLastHit();

	virtual bool isBuffOnLastHit() const { return true; }

    virtual void spawnEffectOnLastHit(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "BuffOnLastHit")
		void spawnEffectOnLastHitImpl(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target) const;

protected:
};
