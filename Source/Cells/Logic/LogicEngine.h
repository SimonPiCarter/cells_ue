// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic.h"
#include <list>

#include <Containers/List.h>
#include "LogicEngine.generated.h"

class ABluePrintLibrary;
class AMapLayout;
class AMobEntity;
class USlot;
class ATowerEntity;
class UEffect;
class UWaveGenerator;
class UWavePackage;
class UEffectList;
class UWaveEngine;
struct MapLayout;
struct WaveLayout;

/**
 * 
 */
UCLASS()
class CELLS_API ALogicEngine : public ALogicActor
{
	GENERATED_BODY()
public:
	ALogicEngine();
	~ALogicEngine();

	// Called to consume a fixed amount of time
	// every logic component using time should inherit this
	virtual void runlogic(float elapsedTime_p, float remainingTime_p);

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
		TArray<USlot*> invetory;

	UPROPERTY(BlueprintReadOnly, Category = "LogicEngine")
		TArray<ATowerEntity*> towers;

	UPROPERTY(BlueprintReadOnly, Category = "LogicEngine")
		UEffectList* effects;

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		int getMobLeft();

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		TArray<AMobEntity*> getClosestMobFromPosition(FVector2D pos, float radius, TArray<AMobEntity*> ignored);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		TArray<AMobEntity*> getAllMobWithinRadius(FVector2D pos, float radius);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		TArray<AMobEntity*> getAllMobWithinLine(FVector2D pos, FVector2D target, float range);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		void consumeSlots(TArray<USlot*> const& slots);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		void removeSlotsFromInventory(TArray<USlot*> const& slots);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		bool spawnTower(ATowerEntity* tower);

	UFUNCTION(BlueprintCallable, Category = "LogicEngine")
		void registerEffect(UEffect * effect);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "LogicEngine")
		void showLootScreen(TArray<USlot*> const& slots);

protected:
	UPROPERTY()
		UWaveEngine* _waveEngine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LogicEngine")
		UWaveGenerator* _waveGenerator;

	UPROPERTY()
		UWavePackage* _curWave;

	MapLayout * _mapLayout;
};
