// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Logic/Wave/WavePackage.h"

#include "WaveGenerator.generated.h"

class CELLS_API AbstractWaveGenerator
{
public:
	virtual UWavePackage * getNextWavePackage() = 0;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CELLS_API UWaveGenerator : public UObject, public AbstractWaveGenerator
{
	GENERATED_BODY()
public:

	virtual UWavePackage* getNextWavePackage() final;
	 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "WaveGenerator")
		UWavePackage* spawnNextWavePackage();
};
