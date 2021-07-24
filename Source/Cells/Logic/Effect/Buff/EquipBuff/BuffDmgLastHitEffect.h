// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BuffEquipEffect.h"
#include "BuffDmgLastHitEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API UBuffDmgLastHitEffect : public UBuffEquipEffect
{
	GENERATED_BODY()

public:
	UBuffDmgLastHitEffect();

	/// to be extended
	// apply effect
	virtual void apply();

	/// to be extended
	// revert effect
	virtual void revert();

	// increase count and update buff
	void increaseCount();

	/// debuf becomes a buff
	void switchBuff();

	size_t getCount() const { return _count; }
	float getFactor() const { return _factor; }

protected:
	size_t _count;
	bool _switched;

	/// @brief damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuffDmgLastHitEffect")
		float _factor;
};
