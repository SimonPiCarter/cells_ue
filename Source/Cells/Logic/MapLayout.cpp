// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLayout.h"

// Sets default values
AMapLayout::AMapLayout()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMapLayout::~AMapLayout()
{
	for (auto const& pair_l : _waves)
	{
		delete pair_l.second;
	}
}

// Called when the game starts or when spawned
void AMapLayout::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapLayout::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

MapLayout AMapLayout::getMapLayout()
{
	MapLayout layout_l;
	layout_l._spawnPoint[0] = spawnpoint.X;
	layout_l._spawnPoint[1] = spawnpoint.Y;

	layout_l.boundingBox.position[0] = pos.X;
	layout_l.boundingBox.position[1] = pos.Y;

	layout_l.boundingBox.size[0] = size.X;
	layout_l.boundingBox.size[1] = size.Y;

	for (FVector2D const &pos_l : checkpoints)
	{
		layout_l._checkPoints.push_back({ pos_l.X, pos_l.Y });
	}
	return layout_l;
}

std::list<WaveLayout *> AMapLayout::getWaveLayouts()
{
	std::list<WaveLayout *> waves_l;
	for (std::pair<int, WaveLayout*> wave_l : _waves)
	{
		waves_l.push_back(wave_l.second);
	}
	return waves_l;
}

void AMapLayout::addMobEntityLayout(int wave_p, FString const& cat_p, FString const& name_p, int qty_p, float delay_p)
{
	if (!_waves[wave_p])
	{
		_waves[wave_p] = new WaveLayout();
	}
	MobEntityLayout layout_l;
	layout_l.mob_category = TCHAR_TO_UTF8(*cat_p);
	layout_l.mob_name = TCHAR_TO_UTF8(*name_p);
	layout_l.quantity = qty_p;
	layout_l.delay = delay_p;

	_waves[wave_p]->mobLayout.push_back(layout_l);
}

void AMapLayout::setWaveTimeToPrepare(int wave_p, float delay_p)
{
	if (!_waves[wave_p])
	{
		_waves[wave_p] = new WaveLayout();
	}
	_waves[wave_p]->time = delay_p;
}