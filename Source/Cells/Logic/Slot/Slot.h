// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Slot.generated.h"

UCLASS(BlueprintType, Blueprintable)
class CELLS_API USlot : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	USlot();
	USlot(bool attackModifier_p);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		int level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		UTexture2D * icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		FString description;

	UPROPERTY(BlueprintReadOnly, Category = "Slot")
		bool isAttackModifier;
};
