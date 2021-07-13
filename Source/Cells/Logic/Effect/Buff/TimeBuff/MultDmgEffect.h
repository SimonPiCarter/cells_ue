// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TimeBuffEffect.h"
#include "MultDmgEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API UMultDmgEffect : public UTimeBuffEffect
{
	GENERATED_BODY()
public:
	UMultDmgEffect();
	UMultDmgEffect(float duration_p, float mult_p);

	/// to be extended
	// apply effect
	virtual void apply();
	/// to be extended
	// revert effect
	virtual void revert();

protected:
	bool _applied;

	/// @brief multiplication factor for every stack (1 means + 100 %)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MultDmgEffect")
		float _mult;
};
