// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <vector>
#include <unordered_map>

#include "TowerEntity.generated.h"

class UAttackModifier;
class UBuffEffect;
class USlot;

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

	/// @brief container for buff
	std::unordered_map<std::string, UBuffEffect *> _buffs;

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
		int cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerEntity")
		TArray<USlot*> slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TowerEntity")
		UAttackModifier* attackModifier;

	/// @brief update slots and return all removed slots
	UFUNCTION(BlueprintCallable, Category = "TowerEntity")
		TArray<USlot*> updateSlots(UAttackModifier* newAttackModifier, TArray<USlot*> newSlots);

	/// @brief get full attack speed (taking multiplier into account)
	UFUNCTION(BlueprintCallable, Category = "TowerEntity")
		float getAttackSpeed() const;
	/// @brief get full damages (taking multiplier into account)
	UFUNCTION(BlueprintCallable, Category = "TowerEntity")
		float getDamage() const;
	/// @brief get full ranges (taking multiplier into account)
	UFUNCTION(BlueprintCallable, Category = "TowerEntity")
		float getRange() const;

	void registerBuff(UBuffEffect * buff_p);
	void unregisterBuff(UBuffEffect * buff_p);
	bool isRegistered(UBuffEffect * buff_p);
	UBuffEffect * getRegisteredBuff(std::string const & id_p);
};
