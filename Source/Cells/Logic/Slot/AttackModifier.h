// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slot.h"
#include "../../DmgType.h"
#include "../../AttackType.h"
#include "AttackModifier.generated.h"

class ALogicEngine;
class ATowerEntity;

/**
 * 
 */
UCLASS()
class CELLS_API AAttackModifier : public ASlot
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackModifier")
		float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackModifier")
		float range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackModifier")
		float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackModifier")
		DmgType _damageType;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "AttackModifier")
		void spawnAttack(ALogicEngine* engine, ATowerEntity* source, bool& hasAttacked);

	UFUNCTION(BlueprintCallable, Category = "AttackModifier")
		FString buildBasicDesc();
};
