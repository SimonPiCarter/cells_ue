// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Logic.h"
#include "MobMover.h"
#include "MobSpawner.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API AMobSpawner : public ALogic
{
	GENERATED_BODY()
public:
	AMobSpawner();

	UFUNCTION(BlueprintCallable, Category = "MobSpawner")
		int getMobLeft();

protected:
	virtual void runlogic(float elapsedTime_p);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobSpawner")
		UBlueprint* test;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobSpawner")
		AMobMover* mobMover;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobSpawner")
		int mobSpawned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobSpawner")
		int mobDespawned;

	float storedTime;
};
