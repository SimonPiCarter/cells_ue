// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffEffect.h"
#include "BuffEquipEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API UBuffEquipEffect : public UBuffEffect
{
	GENERATED_BODY()
public:
	UBuffEquipEffect();

	/// should not be extended
	virtual void runEffect(float elapsedTime_p);

	// We only need to implement apply and revert
	// as they will be called when adding new slots and remvoing old ones

	/// to be extended
	// apply effect
	virtual void apply() {}

	/// to be extended
	// revert effect
	virtual void revert() {}
protected:

};
