// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TimeBuffEffect.h"
#include "SpeedBonusEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API USpeedBonusEffect : public UTimeBuffEffect
{
	GENERATED_BODY()
public:
	USpeedBonusEffect();

	/// to be extended
	// apply effect
	virtual void apply();
	/// to be extended
	// revert effect
	virtual void revert();

	/// @brief attack speed multplier (0.1 means 10% attack speed bonus)
	/// multiplier is _bonus * _stack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBonusEffect")
		float _bonus;
};
