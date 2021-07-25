// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotDescriptor.h"
#include "Slot.generated.h"

class ALogicEngine;

UCLASS(BlueprintType, Blueprintable)
class CELLS_API USlot : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	USlot();
	USlot(bool attackModifier_p, bool effectMaker_p);
	~USlot();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		int level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		UTexture2D * icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		FString description;

	UPROPERTY(BlueprintReadOnly, Category = "Slot")
		bool _isAttackModifier;

	UPROPERTY(BlueprintReadOnly, Category = "Slot")
		bool _isEffectMaker;

	UFUNCTION(BlueprintCallable, Category = "Slot")
	/// @brief round with two digit maximum
		float cround(float val);

	UFUNCTION(BlueprintCallable, Category = "Slot")
	/// @brief update description using descriptor
		void updateDescription();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Slot")
	/// @brief setup slot with random generation (based on level and logic random genertor)
		void setup(ALogicEngine * logic, float baselevel);

	void setSlotDescriptor(SlotDescriptor * descriptor_p);

protected:
	/// @brief crée la description du slot
	SlotDescriptor * _descriptor;
};
