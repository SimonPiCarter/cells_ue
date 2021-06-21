// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <array>
#include <list>

#include "MobEntityMover.h"
#include "MobEntitySpawner.h"
#include "PositionTree.h"

class ABluePrintLibrary;
class AMobEntity;
class ALogicEngine;
struct WaveLayout;
struct MapLayout;

/**
 * 
 */
class CELLS_API WaveEngine
{
public:
	WaveEngine(ALogicEngine&engine_p, ABluePrintLibrary* library_p, WaveLayout const& layout_p, MapLayout const& map_p);
	~WaveEngine();

	void runlogic(float elapsedTime_p);

	int getMobSpawned() const {
		return _spawner.getMobSpawned() - _despawnedMob;
	}

	void spawnMob(AMobEntity* mob_p);
	void despawnMob(AMobEntity* mob_p);
	void moveMob(AMobEntity* mob_p, std::array<double, 2> const& oldPos_p, std::array<double, 2> const& newPos_p);

	PositionalTree<AMobEntity>& getTree() {
		return _tree;
	}

protected:
	ALogicEngine& _engine;
	MobEntityMover _mover;
	MobEntitySpawner _spawner;

	bool _spawnOver;
	int _despawnedMob;

	std::list<AMobEntity*> _mobs;

	PositionalTree<AMobEntity> _tree;
};
