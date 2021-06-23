// Fill out your copyright notice in the Description page of Project Settings.


#include "MobEntity.h"

// Sets default values
AMobEntity::AMobEntity()
	: armorType(ArmorType::Standard)
	, _first(true)
	, _currentCheckPoint()
	, _enabled(true)
	, hitpoint(3.)
	, maxHitpoint(3.)
	, speed(10)
	, damageMultiplier(1.)
	, damageLife(1.)
	, scrapReward(1.)
	, size(1.)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AMobEntity::disable()
{
	_enabled = false;
}

bool AMobEntity::isEnabled() const
{
	return _enabled;
}

std::array<double, 2> AMobEntity::getPosition() const
{
	FVector currentLocation_l = this->GetActorLocation();
	return  { currentLocation_l.X, currentLocation_l.Y };
}
std::array<double, 2> AMobEntity::getSize() const
{
	return { size , size };
}
std::list<StorageInfo<AMobEntity> > const& AMobEntity::getPositionNodes() const
{
	return _storageInfo;
}
std::list<StorageInfo<AMobEntity> >& AMobEntity::getPositionNodes()
{
	return _storageInfo;
}

// Called when the game starts or when spawned
void AMobEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMobEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMobEntity::isAtLastCheckPoint()
{
	return _currentCheckPoint == _checkPoints.end();
}

void AMobEntity::incrementCheckPoint()
{
	if (_first)
	{
		_currentCheckPoint = _checkPoints.begin();
		_first = false;
	}
	++_currentCheckPoint;
}

std::array<double, 2> const& AMobEntity::getCurrentCheckPoint()
{
	if (_first)
	{
		_currentCheckPoint = _checkPoints.begin();
		_first = false;
	}
	return *_currentCheckPoint;
}
