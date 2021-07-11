// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TimeBuffEffect.h"
#include "SlowEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API USlowEffect : public UTimeBuffEffect
{
	GENERATED_BODY()
public:
	USlowEffect();
	USlowEffect(float duration_p, float slow_p);

	/// to be extended
	// apply effect
	virtual void apply();
	/// to be extended
	// revert effect
	virtual void revert();

protected:
	bool _applied;

	/// @brief slow factor (between 0 and 1 : 0.1 means slowed speed will reduced by 10% per stack)
    /// is capped to 0.99
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlowEffect")
		float _slow;
};
