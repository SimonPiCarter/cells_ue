// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArmorType.h"
#include "Logic/StorageInfo.h"

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

	void disable();
	bool isEnabled() const;

	std::array<double, 2> getPosition() const;
	std::array<double, 2> getSize() const;
	std::list<StorageInfo<AMobEntity> > const& getPositionNodes() const;
	std::list<StorageInfo<AMobEntity> >& getPositionNodes();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool _first;
	std::list<std::array<double, 2> >::iterator _currentCheckPoint;

	bool _enabled;

	std::list<StorageInfo<AMobEntity> > _storageInfo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	std::list<std::array<double, 2> > _checkPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobEntity")
		float hitpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobEntity")
		float maxHitpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobEntity")
		float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobEntity")
		float damageMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobEntity")
		float damageLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobEntity")
		float scrapReward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobEntity")
		float size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobEntity")
		ArmorType armorType;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "MobEntity")
		void despawn();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "MobEntity")
		void damage(float val);

	bool isAtLastCheckPoint();
	void incrementCheckPoint();
	std::array<double, 2> const& getCurrentCheckPoint();

	ArmorType getArmorType() { return armorType;  }
};
