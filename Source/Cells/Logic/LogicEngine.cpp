// Fill out your copyright notice in the Description page of Project Settings.


#include "LogicEngine.h"

#include "MapLayout.h"
#include "WaveEngine.h"
#include "Slot/Slot.h"
#include "../MobEntity.h"
#include "../TowerEntity.h"

ALogicEngine::ALogicEngine()
	: time(0.)
	, life(100.)
	, scraps(50.)
	, waveCount(0)
	, waveRunning(true)
	, onHold(false)
	, map(nullptr)
	, _waveEngine(nullptr)
	, _mapLayout(nullptr)
	, _waveLayouts()
{}

ALogicEngine::~ALogicEngine()
{
	delete _mapLayout;
}

void ALogicEngine::runlogic(float elapsedTime_p, float remainingTime_p)
{
	// if no map and map generator
	if (map != nullptr && !_mapLayout)
	{
		_mapLayout = new MapLayout(map->getMapLayout());
		_waveLayouts = map->getWaveLayouts();
		_itCurrentWave = _waveLayouts.begin();
		map->spawnMap(library);
		if (_itCurrentWave != _waveLayouts.end())
		{
			time = (*_itCurrentWave)->time;
		}
	}

	// on hold do nothing
	if (onHold)
	{
		return;
	}

	if (waveRunning)
	{
		// if in wave we count the time in an increasing matter
		time += elapsedTime_p;
	}
	else
	{
		// if waiting for a wave we count the time in an decreasing matter
		time -= elapsedTime_p;
	}

	// If wave is not running and time ran out
	if (!waveRunning && time <= 0. && _itCurrentWave != _waveLayouts.end())
	{
		waveRunning = true;
		// spawn next wave
		_waveEngine = NewObject<UWaveEngine>(this, UWaveEngine::StaticClass());
		_waveEngine->init(*this, library, ** _itCurrentWave, * _mapLayout);

		time = 0.;
		++waveCount;
	}
	// If wave is running
	if (waveRunning)
	{
		// no more mob we spawn endwave events
		// TODO

		// update wave engine
		_waveEngine->runlogic(elapsedTime_p);
	}
}

void ALogicEngine::despawnMob(AMobEntity* mob_p)
{
	life -= mob_p->damageLife;
}

void ALogicEngine::killMob(AMobEntity* mob_p)
{
	scraps += mob_p->scrapReward;
}

int ALogicEngine::getMobLeft()
{
	return _waveEngine ? _waveEngine->getMobSpawned() : 0;
}

TArray<AMobEntity*> ALogicEngine::getClosestMobFromPosition(FVector2D pos, float radius, TArray<AMobEntity*> ignored)
{
	TArray<AMobEntity*> array_l;
	if (_waveEngine)
	{
		std::unordered_set<AMobEntity*> ignored_l;
		for (AMobEntity* mob_l : ignored)
		{
			ignored_l.insert(mob_l);
		}
		AMobEntity * mob_l = _waveEngine->getTree().getClosestFromPosition({ pos.X , pos.Y }, radius, ignored_l);
		if (mob_l)
		{
			array_l.Push(mob_l);
		}
	}
	return array_l;
}

TArray<AMobEntity*> ALogicEngine::getAllMobWithinRadius(FVector2D pos, float radius)
{
	TArray<AMobEntity*> array_l;
	if (_waveEngine)
	{
		std::unordered_set<AMobEntity*> mobs_l = _waveEngine->getTree().getAllWithinRadius({ pos.X , pos.Y }, radius);
		for (AMobEntity* mob_l : mobs_l)
		{
			array_l.Push(mob_l);
		}
	}
	return array_l;
}

TArray<AMobEntity*> ALogicEngine::getAllMobWithinLine(FVector2D pos, FVector2D target, float range)
{
	TArray<AMobEntity*> array_l;
	if (_waveEngine)
	{
		std::unordered_set<AMobEntity*> mobs_l = _waveEngine->getTree().getAllWithinLine({ pos.X , pos.Y }, { target.X , target.Y }, range);
		for (AMobEntity* mob_l : mobs_l)
		{
			array_l.Push(mob_l);
		}
	}
	return array_l;
}

bool ALogicEngine::spawnTower(ATowerEntity* tower)
{
	if (scraps >= tower->cost)
	{
		towers.Add(tower);
		scraps -= tower->cost;
		return true;
	}
	return false;
}

void ALogicEngine::consumeSlots(TArray<ASlot*> const& slots)
{
	for (ASlot* slot_l : slots)
	{
		// gain scrap even if out of inventory (in case of tower consumption)
		scraps += slot_l->level;
	}
}

void ALogicEngine::removeSlotsFromInventory(TArray<ASlot*> const& slots)
{
	for (ASlot* slot_l : slots)
	{
		// remove from inventory
		invetory.Remove(slot_l);
	}
}