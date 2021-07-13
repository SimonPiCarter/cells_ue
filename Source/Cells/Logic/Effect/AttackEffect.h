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
	UAttackEffect();

	virtual void runEffect(float elapsedTime_p) final;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackEffect")
		float _damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackEffect")
		DmgType _dmgType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackEffect")
		bool _lethal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackEffect")
	/// @brief must only be true if effect on hit should be trigger
		bool _primary;
};
