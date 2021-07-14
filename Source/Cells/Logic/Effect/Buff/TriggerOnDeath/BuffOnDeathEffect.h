// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerOnDeathEffect.h"
#include "../../../../DmgType.h"
#include "BuffOnDeathEffect.generated.h"

UCLASS()
class CELLS_API UDmgBonusOnDeathEffect : public UTriggerOnDeathEffect
{
	GENERATED_BODY()
public:
	UDmgBonusOnDeathEffect();

	/// @brief spawn buff
	virtual void deathTrigger();

	/// @brief max stack for this buff (1 for not stackable)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DmgBonusOnDeathEffect")
		int _maxStackBuff;

	/// @brief duration for the buff (1 for not stackable)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBonusOnDeathEffect")
		float _durationBuff;

	/// @brief damage multplier (0.1 means 10% damage bonus)
	/// multiplier is _bonus * _stack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DmgBonusOnDeathEffect")
		float _bonus;

    UFUNCTION(BlueprintCallable, Category = "DmgBonusOnDeathEffect")
        void init(int maxStack, float durationBuff, float bonus);
};

UCLASS()
class CELLS_API USpeedBonusOnDeathEffect : public UTriggerOnDeathEffect
{
	GENERATED_BODY()
public:
	USpeedBonusOnDeathEffect();

	/// @brief spawn buff
	virtual void deathTrigger();

	/// @brief max stack for the buff (1 for not stackable)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBonusOnDeathEffect")
		int _maxStackBuff;

	/// @brief duration for the buff (1 for not stackable)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBonusOnDeathEffect")
		float _durationBuff;

	/// @brief attack speed multplier (0.1 means 10% attack speed bonus)
	/// multiplier is _bonus * _stack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBonusOnDeathEffect")
		float _bonus;

    UFUNCTION(BlueprintCallable, Category = "SpeedBonusOnDeathEffect")
        void init(int maxStack, float durationBuff, float bonus);
};
