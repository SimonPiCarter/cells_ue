// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Slot.generated.h"

UCLASS()
class CELLS_API ASlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlot();
	ASlot(bool attackModifier_p);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		int level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		UTexture2D * icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
		FString description;

	UPROPERTY(BlueprintReadOnly, Category = "Slot")
		bool isAttackModifier;
};
