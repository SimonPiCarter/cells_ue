// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BuffOnEquip.h"
#include "../BuffOnLastHit.h"
#include "BuffDmgLastHit.generated.h"

/**
 *
 */
UCLASS()
class CELLS_API UBuffDmgLastHit : public UBuffOnEquip
{
	GENERATED_BODY()

public:
	UBuffDmgLastHit();

	virtual bool isBuffOnLastHit() const { return true; }
	virtual bool isBuffOnEquip() const { return true; }

    virtual void spawnEffectOnLastHit(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target);

	UFUNCTION(BlueprintCallable, Category = "BuffDmgLastHit")
		FString buildBasicDesc();

	/// @brief damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuffDmgLastHit")
		float _factor;
};
