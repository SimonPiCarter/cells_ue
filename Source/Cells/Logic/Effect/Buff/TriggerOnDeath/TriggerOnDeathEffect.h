// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TimeBuffEffect.h"
#include "TriggerOnDeathEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API UTriggerOnDeathEffect : public UTimeBuffEffect
{
	GENERATED_BODY()
public:
	UTriggerOnDeathEffect();

	virtual void updateBuff(float elapsedTime_p);

	/// @brief to be extended
	/// will be called on first tick when target mob is dead
	virtual void deathTrigger() {}

protected:
	/// @brief boolean to track if death has already trigger the effect
	bool _triggered;
};
