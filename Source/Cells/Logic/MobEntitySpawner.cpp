// Fill out your copyright notice in the Description page of Project Settings.


#include "MobEntitySpawner.h"

#include "Engine/World.h"

#include "BluePrintLibrary.h"
#include "WaveEngine.h"
#include "../MobEntity.h"

MobEntitySpawner::MobEntitySpawner(ABluePrintLibrary* library_p, UWaveEngine& engine_p, WaveLayout const& layout_p, MapLayout const& map_p)
    : _mobSpawned(0)
    , _library(library_p)
    , _engine(engine_p)
    , _layout(layout_p)
    , _map(map_p)
	, _timeToNext(0)
	, _indexNext(0)
	, _currentLayout(_layout.mobLayout.cbegin())
{
}

MobEntitySpawner::~MobEntitySpawner()
{
}

bool MobEntitySpawner::spawn(float elapsedTime_p)
{
	// if current layout is done skip to next
	bool done_l = !nextLayoutIfNecessary();
	if (done_l) { return true; }

	// keep track of remaining time while we spawn
	float remainingTime_l = elapsedTime_p;
	UWorld* const world_l = _library->GetWorld();

	// While time is sufficient to spawn something
	while (remainingTime_l >= _timeToNext)
	{
		UBlueprint* spawnedBlueprint_l = _library->getBluePrint(_currentLayout->mob_category, _currentLayout->mob_name);
		// spawn
		FActorSpawnParameters SpawnParams;
		AMobEntity* mob_l = world_l->SpawnActor<AMobEntity>((UClass*)spawnedBlueprint_l->GeneratedClass, FVector(_map._spawnPoint[0], _map._spawnPoint[1], 0), FRotator(0, 0, 0), SpawnParams);
		mob_l->_checkPoints = _map._checkPoints;
		_engine.spawnMob(mob_l);
		++_mobSpawned;

		mob_l->hitpoint = _currentLayout->maxHitpoint;
		mob_l->maxHitpoint = _currentLayout->maxHitpoint;
		mob_l->speed = _currentLayout->speed;
		mob_l->damageLife = _currentLayout->damageLife;
		mob_l->scrapReward = _currentLayout->scrapReward;

		// increment index
		++_indexNext;

		// update remaining time
		remainingTime_l -= _timeToNext;

		// change layout if necessary
		done_l = !nextLayoutIfNecessary();
		if (done_l) { return true; }

		// update time to next from layout
		_timeToNext = _currentLayout->delay;
	}

	// reduce time to next according to remaining time
	_timeToNext -= remainingTime_l;

	return done_l;
}

int MobEntitySpawner::getMobSpawned() const
{
    return _mobSpawned;
}

/// @brief incerement current layout if necessary
/// reset _indexNext when changing layout
/// @return true if there is a layout to spawn left
bool MobEntitySpawner::nextLayoutIfNecessary()
{
    // increment layout iterator if necessary
    while (_currentLayout != _layout.mobLayout.cend()
        && _indexNext >= _currentLayout->quantity)
    {
        ++_currentLayout;
        // reset index next if we change layout
        _indexNext = 0;
    }
    return _currentLayout != _layout.mobLayout.cend();
}
