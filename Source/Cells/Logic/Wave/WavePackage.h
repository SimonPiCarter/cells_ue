// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../MapLayout.h"

#include "WavePackage.generated.h"

class USlot;

/**
 * 
 */
UCLASS(BlueprintType)
class CELLS_API UWavePackage : public UObject
{
	GENERATED_BODY()
	
public:
	UWavePackage();

	UFUNCTION(BlueprintCallable, Category = "WavePackage")
		void addMobEntityLayout(FString const& cat, FString const& name, int qty, float delay
			, float maxHitpoint=20, float speed=10, float damageLife=1, float scrapReward=1);

	UFUNCTION(BlueprintCallable, Category = "WavePackage")
		void setWaveTimeToPrepare(float delay);

	TArray<USlot*>& getRewards() { return _rewards; }
	WaveLayout& getWaveLayout() { return _wave;  }
protected:
	WaveLayout _wave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WavePackage")
		TArray<USlot*> _rewards;
};
