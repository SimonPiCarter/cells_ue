// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TimeBuffEffect.h"
#include "DmgBonusEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API UDmgBonusEffect : public UTimeBuffEffect
{
	GENERATED_BODY()
public:
	UDmgBonusEffect();

	/// to be extended
	// apply effect
	virtual void apply();
	/// to be extended
	// revert effect
	virtual void revert();

	/// @brief damage multplier (0.1 means 10% damage bonus)
	/// multiplier is _bonus * _stack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DmgBonusEffect")
		float _bonus;
};
