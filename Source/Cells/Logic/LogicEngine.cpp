// Fill out your copyright notice in the Description page of Project Settings.


#include "LogicEngine.h"

#include "MapLayout.h"
#include "WaveEngine.h"
#include "Effect/Effect.h"
#include "Effect/EffectList.h"
#include "Slot/Slot.h"
#include "../MobEntity.h"
#include "../TowerEntity.h"
#include "../Wave/WaveGenerator.h"

ALogicEngine::ALogicEngine()
	: time(0.)
	, life(100.)
	, scraps(50.)
	, waveCount(0)
	, waveRunning(true)
	, onHold(false)
	, map(nullptr)
	, effects(nullptr)
	, _waveEngine(nullptr)
	, _waveGenerator(nullptr)
	, _curWave(nullptr)
	, _mapLayout(nullptr)
	, _random(new std::mt19937(42))
{}

ALogicEngine::~ALogicEngine()
{
	delete _mapLayout;
	delete _random;
}

void ALogicEngine::initSeed(unsigned long seed_p)
{
	delete _random;
	_random = new std::mt19937(seed_p);
}

void ALogicEngine::runlogic(float elapsedTime_p, float remainingTime_p)
{
	if (nullptr == effects)
	{
		effects = NewObject<UEffectList>(this);
	}
	// if no map and map generator
	if (map != nullptr && !_mapLayout && nullptr != _waveGenerator)
	{
		_mapLayout = new MapLayout(map->getMapLayout());
		_curWave = _waveGenerator->getNextWavePackage();
		map->spawnMap(library);
		if (_curWave)
		{
			time = _curWave->getWaveLayout().time;
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
	if (!waveRunning && time <= 0. && _curWave)
	{
		waveRunning = true;
		// spawn next wave
		_waveEngine = NewObject<UWaveEngine>(this, UWaveEngine::StaticClass());
		_waveEngine->init(*this, library, _curWave->getWaveLayout(), *_mapLayout);

		time = 0.;
		++waveCount;
	}
	// If wave is running
	if (waveRunning)
	{
		// update wave engine
		_waveEngine->runlogic(elapsedTime_p);

		// no more mob we spawn endwave events
		if (_waveEngine->isWaveOver())
		{
			waveRunning = false;

			// pop loots and event
			showLootScreen(_curWave->getRewards());
			onHold = true;
			invetory.Append(_curWave->getRewards());

			// next wave
			_curWave = _waveGenerator->getNextWavePackage();
			if (_curWave)
			{
				time = _curWave->getWaveLayout().time;
			}
		}
	}

	// handle effect
	UEffectNode * node_l = effects->head;
	while (nullptr != node_l)
	{
		node_l->val->runlogic(elapsedTime_p);

		UEffectNode* next_l = node_l->next;
		// if effect is over remove from list
		if (node_l->val->isOver())
		{
			effects->Remove(node_l);
		}
		node_l = next_l;
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
	return _waveEngine ? _waveEngine->getMobLeft() : 0;
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

bool ALogicEngine::spawnTower(ATowerEntity* tower, int x, int y)
{
	if (scraps >= tower->cost && _mapLayout->isConstructible(x,y))
	{
		towers.Add(tower);
		scraps -= tower->cost;
		return true;
	}
	return false;
}

void ALogicEngine::consumeSlots(TArray<USlot*> const& slots)
{
	for (USlot* slot_l : slots)
	{
		// gain scrap even if out of inventory (in case of tower consumption)
		scraps += slot_l->level;
	}
}

void ALogicEngine::removeSlotsFromInventory(TArray<USlot*> const& slots)
{
	for (USlot* slot_l : slots)
	{
		// remove from inventory
		invetory.Remove(slot_l);
	}
}

void ALogicEngine::registerEffect(UEffect* effect)
{
	effect->setLogic(this);
	effects->Add(effect);
}

float ALogicEngine::genUniform(float min, float max)
{
	std::uniform_real_distribution<double> distribution_l(min, max);
	return distribution_l(*_random);
}

float ALogicEngine::genNormal(float avg, float width, float width_max)
{
	std::normal_distribution<double> distribution_l(0.f, 0.2f);
	float deviation_l = distribution_l(*_random) * width;
	deviation_l = std::min(width_max, std::max(-width_max, deviation_l));

	return avg + deviation_l;
}
