// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <array>
#include <list>

#include "MobEntityMover.h"
#include "MobEntitySpawner.h"
#include "AttackBuilder.h"
#include "PositionTree.h"

#include "WaveEngine.generated.h"

class ABluePrintLibrary;
class AMobEntity;
class ALogicEngine;
struct WaveLayout;
struct MapLayout;

/**
 * 
 */
UCLASS()
class CELLS_API UWaveEngine : public UObject
{
	GENERATED_BODY()
public:
	UWaveEngine();
	~UWaveEngine();

	void init(ALogicEngine& engine_p, ABluePrintLibrary* library_p, WaveLayout const& layout_p, MapLayout const& map_p);
	void runlogic(float elapsedTime_p);

	int getMobSpawned() const {
		return _spawner->getMobSpawned() - _despawnedMob;
	}

	void spawnMob(AMobEntity* mob_p);
	void despawnMob(AMobEntity* mob_p);
	void killMob(AMobEntity* mob_p);
	void moveMob(AMobEntity* mob_p, std::array<double, 2> const& oldPos_p, std::array<double, 2> const& newPos_p);

	PositionalTree<AMobEntity>& getTree() {
		return *_tree;
	}

	ALogicEngine& getLogic() { return *_engine; }

	bool isWaveOver() const { return _spawnOver && getMobSpawned() == 0; }

protected:
	ALogicEngine* _engine;
	MobEntityMover* _mover;
	MobEntitySpawner* _spawner;
	AttackBuilder* _atkBuilder;

	bool _spawnOver;
	int _despawnedMob;

	UPROPERTY()
		TArray<AMobEntity*> _mobs;

	PositionalTree<AMobEntity> * _tree;
};
