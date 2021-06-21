// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveEngine.h"
#include "LogicEngine.h"

#include "../MobEntity.h"

WaveEngine::WaveEngine(ALogicEngine& engine_p, ABluePrintLibrary* library_p, WaveLayout const& layout_p, MapLayout const& map_p)
	: _engine(engine_p)
	, _mover(*this)
	, _spawner(library_p, *this, layout_p, map_p)
	, _spawnOver(false)
	, _despawnedMob(0)
	, _tree(map_p.boundingBox, 100, 0.)
{

}

WaveEngine::~WaveEngine()
{
}

void WaveEngine::runlogic(float elapsedTime_p)
{
	// Spawn mob
	if (!_spawnOver)
	{
		_spawnOver = _spawner.spawn(elapsedTime_p);
	}

	// Compute mob movement
	// Apply movement and update octrees
	_mover.moveEntities(_mobs, elapsedTime_p);
}

void WaveEngine::spawnMob(AMobEntity* mob_p)
{
	_mobs.push_back(mob_p);
	_tree.addContent(_mobs.back());
}

void WaveEngine::despawnMob(AMobEntity* mob_p)
{
	++_despawnedMob;
	_tree.removeContent(mob_p);
	// disable mob
	mob_p->disable();
	mob_p->despawn();
	_engine.despawnMob(mob_p);
}

void WaveEngine::moveMob(AMobEntity* mob_p, std::array<double, 2> const& oldPos_p, std::array<double, 2> const& newPos_p)
{
	if (mob_p->isAtLastCheckPoint() && mob_p->isEnabled())
	{
		despawnMob(mob_p);
	}
	_tree.updatePositionFromNode(*mob_p, oldPos_p, newPos_p);
}
