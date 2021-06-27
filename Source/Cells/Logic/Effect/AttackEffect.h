// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "../../DmgType.h"
#include "AttackEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API UAttackEffect : public UEffect
{
	GENERATED_BODY()
public:
	virtual void runEffect(float elapsedTime_p) final;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackEffect")
		float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackEffect")
		DmgType dmgType;
};
