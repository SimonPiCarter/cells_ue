// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerOnDeathEffect.h"
#include "../../../../DmgType.h"
#include "SplashDmgOnDeathEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API USplashDmgOnDeathEffect : public UTriggerOnDeathEffect
{
	GENERATED_BODY()
public:
	USplashDmgOnDeathEffect();

	/// @brief to be extended
	/// will be called on first tick when target mob is dead
	virtual void deathTrigger();

protected:

	/// @brief damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplashDmgOnDeathEffect")
		float _splash;

	/// @brief damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplashDmgOnDeathEffect")
		float _dmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplashDmgOnDeathEffect")
		DmgType _dmgType;
};
