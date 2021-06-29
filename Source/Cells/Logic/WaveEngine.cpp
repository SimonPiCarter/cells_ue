// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveEngine.h"
#include "LogicEngine.h"

#include "../MobEntity.h"

UWaveEngine::UWaveEngine()
	: _engine(nullptr)
	, _mover(nullptr)
	, _spawner(nullptr)
	, _atkBuilder(nullptr)
	, _spawnOver(false)
	, _despawnedMob(0)
	, _tree(nullptr)
{

}

UWaveEngine::~UWaveEngine()
{
	delete _mover;
	delete _spawner;
	delete _atkBuilder;
	delete _tree;
}

void UWaveEngine::init(ALogicEngine& engine_p, ABluePrintLibrary* library_p, WaveLayout const& layout_p, MapLayout const& map_p)
{
	_engine = &engine_p;
	_mover = new MobEntityMover(*this);
	_spawner = new MobEntitySpawner(library_p, *this, layout_p, map_p);
	_atkBuilder = new AttackBuilder(*this);
	_tree = new PositionalTree<AMobEntity>(map_p.boundingBox, 100, 0.);


	_mobLeft = 0;
	for (MobEntityLayout const& mobLayout_l : layout_p.mobLayout)
	{
		_mobLeft += mobLayout_l.quantity;
	}
}

void UWaveEngine::runlogic(float elapsedTime_p)
{
	// Spawn mob
	if (!_spawnOver)
	{
		_spawnOver = _spawner->spawn(elapsedTime_p);
	}

	// Compute mob movement
	// Apply movement and update octrees
	_mover->moveEntities(_mobs, elapsedTime_p);

	_atkBuilder->buildAttacks(elapsedTime_p);

	for (AMobEntity* mob_l : _mobs)
	{
		if (mob_l->isEnabled() && mob_l->hitpoint <= 0)
		{
			killMob(mob_l);
		}
	}
}

void UWaveEngine::spawnMob(AMobEntity* mob_p)
{
	_mobs.Add(mob_p);
	_tree->addContent(mob_p);
}

void UWaveEngine::despawnMob(AMobEntity* mob_p)
{
	++_despawnedMob;
	_tree->removeContent(mob_p);
	// disable mob
	mob_p->disable();
	mob_p->despawn();
	_engine->despawnMob(mob_p);
}

void UWaveEngine::killMob(AMobEntity* mob_p)
{
	++_despawnedMob;
	_tree->removeContent(mob_p);
	// disable mob
	mob_p->disable();
	mob_p->despawn();
	_engine->killMob(mob_p);
}

void UWaveEngine::moveMob(AMobEntity* mob_p, std::array<double, 2> const& oldPos_p, std::array<double, 2> const& newPos_p)
{
	if (mob_p->isAtLastCheckPoint() && mob_p->isEnabled())
	{
		despawnMob(mob_p);
	}
	_tree->updatePositionFromNode(*mob_p, oldPos_p, newPos_p);
}
