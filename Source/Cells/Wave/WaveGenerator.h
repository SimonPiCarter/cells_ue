// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Logic/Wave/WavePackage.h"
#include "../Logic/Slot/Generator/SlotGeneratorEngine.h"

#include "WaveGenerator.generated.h"

class ALogicEngine;

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
	UWaveGenerator();

	virtual UWavePackage* getNextWavePackage() final;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "WaveGenerator")
		UWavePackage* spawnNextWavePackage();

	UFUNCTION(BlueprintCallable, Category = "WaveGenerator")
		void generateSlots(UWavePackage* package, int count, ALogicEngine *logic, float minLevel, float maxLevel);

	SlotGeneratorEngine _generatorEngine;
};
