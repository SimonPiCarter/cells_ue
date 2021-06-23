// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>

#include "TowerEntity.generated.h"

class AAttackModifier;
class ASlot;

UCLASS()
class CELLS_API ATowerEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerEntity")
		float multAttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerEntity")
		float multDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerEntity")
		float bonusRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerEntity")
		int maxSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerEntity")
		TArray<ASlot*> slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerEntity")
		AAttackModifier * attackModifier;

	/// @brief get full attack speed (taking multiplier into account)
	UFUNCTION(BlueprintCallable, Category = "TowerEntity")
		float getAttackSpeed() const;
	/// @brief get full damages (taking multiplier into account)
	UFUNCTION(BlueprintCallable, Category = "TowerEntity")
		float getDamage() const;
	/// @brief get full ranges (taking multiplier into account)
	UFUNCTION(BlueprintCallable, Category = "TowerEntity")
		float getRange() const;
};
