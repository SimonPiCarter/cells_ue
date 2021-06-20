// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArmorType.h"

#include <array>
#include <list>
#include <string>

#include "MobEntity.generated.h"

UCLASS()
class CELLS_API AMobEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMobEntity();

	void move(float time_p);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	ArmorType armorType;

	size_t _currentCheckPoint;

	bool isAtLastCheckPoint();
	FVector2D const& getCurrentCheckPoint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "MobEntity")
		TArray<FVector2D> checkpoints;

	UPROPERTY(BlueprintReadWrite, Category = "MobEntity")
		float hitpoint;

	UPROPERTY(BlueprintReadWrite, Category = "MobEntity")
		float maxHitpoint;

	UPROPERTY(BlueprintReadWrite, Category = "MobEntity")
		float speed;

	UPROPERTY(BlueprintReadWrite, Category = "MobEntity")
		float damageMultiplier;

	UPROPERTY(BlueprintReadWrite, Category = "MobEntity")
		float damageLife;

	UPROPERTY(BlueprintReadWrite, Category = "MobEntity")
		float scrapReward;

	UPROPERTY(BlueprintReadWrite, Category = "MobEntity")
		float size;

	UFUNCTION(BlueprintCallable, Category = "MobEntity")
		void setArmorType(FString const& str_p);

};
