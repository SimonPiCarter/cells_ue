// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic.h"
#include <list>
#include "LogicEngine.generated.h"

class ABluePrintLibrary;
class AMapLayout;
class AMobEntity;
class ASlot;
class ATowerEntity;
class UWaveEngine;
struct MapLayout;
struct WaveLayout;

/**
 * 
 */
UCLASS()
class CELLS_API ALogicEngine : public ALogic
{
	GENERATED_BODY()
public:
	ALogicEngine();
	~ALogicEngine();

	// Called to consume a fixed amount of time
	// every logic component using time should inherit this
	virtual void runlogic(float elapsedTime_p);

	void despawnMob(AMobEntity* mob_p);
	void killMob(AMobEntity* mob_p);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LogicEngine")
		float time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LogicEngine")
		float life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LogicEngine")
		float scraps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LogicEngine")
		int waveCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LogicEngine")
		bool waveRunning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LogicEngine")
		bool onHold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LogicEngine")
		AMapLayout * map;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LogicEngine")
		ABluePrintLibrary* library;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LogicEngine")
		TArray<ASlot*> invetory;

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		int getMobLeft();

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		TArray<AMobEntity*> getClosestMobFromPosition(FVector2D pos, float radius, TArray<AMobEntity*> ignored);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		TArray<AMobEntity*> getAllMobWithinRadius(FVector2D pos, float radius);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		TArray<AMobEntity*> getAllMobWithinLine(FVector2D pos, FVector2D target, float range);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		void consumeSlots(TArray<ASlot*> const& slots);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		void removeSlotsFromInventory(TArray<ASlot*> const& slots);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		void spawnTower(ATowerEntity* tower);


	std::list<ATowerEntity*> const& getTowers() const { return _towers; }
	std::list<ATowerEntity*>& getTowers() { return _towers; }

protected:
	UPROPERTY()
		UWaveEngine* _waveEngine;

	MapLayout * _mapLayout;
	std::list<WaveLayout*> _waveLayouts;
	std::list<WaveLayout*>::iterator _itCurrentWave;

	/// @brief list of tower
	std::list<ATowerEntity*> _towers;
};
