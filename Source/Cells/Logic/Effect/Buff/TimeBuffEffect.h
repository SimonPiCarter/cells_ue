// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffEffect.h"
#include "TimeBuffEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API UTimeBuffEffect : public UBuffEffect
{
	GENERATED_BODY()
public:
	UTimeBuffEffect();
	UTimeBuffEffect(float duration_p);

	/// should not be extended
	virtual void runEffect(float elapsedTime_p);

	// can be extended
	virtual void updateBuff(float elapsedTime_p) {}

	/// should not be extended
	// refresh the effect : reset timer and increase stack count
	virtual void refresh();

	/// @brief duration of the TimeBuff if set to 0 there is no time limit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeBuffEffect")
		float _duration;

	/// @brief max stack for this buff (1 for not stackable)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeBuffEffect")
		int _maxStack;

protected:
	/// @brief time elapsed since application of the buff
	float _fullElapsedTime;

	/// @brief current stack count
	int _stack;

	bool _registered;
};
