// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TimeBuffEffect.h"
#include "../../../../DmgType.h"
#include "DotEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API UDotEffect : public UTimeBuffEffect
{
	GENERATED_BODY()
public:
	UDotEffect();
	UDotEffect(float duration_p, float dmg_p);

	/// to be extended
	// apply effect
	virtual void apply() {}

	void updateBuff(float elapsedTime_p);

protected:
	/// @brief time elapsed since application of the buff
	/// used to compute damage
	float _dotTime;

	/// @brief damage every second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DotEffect")
		float _dmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DotEffect")
		DmgType _dmgType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DotEffect")
		bool _lethal;
};
