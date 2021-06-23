// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MapLayout.h"

class UWaveEngine;
class ABluePrintLibrary;

/**
 * 
 */
class CELLS_API MobEntitySpawner
{
public:
	MobEntitySpawner(ABluePrintLibrary* library_p, UWaveEngine &engine_p, WaveLayout const& layout_p, MapLayout const& map_p);
	~MobEntitySpawner();

	bool spawn(float elapsedTime_p);

	int getMobSpawned() const;
protected:
	int _mobSpawned;

	ABluePrintLibrary* const _library;
	UWaveEngine& _engine;

	WaveLayout const _layout;
	MapLayout const& _map;

	/// @brief remaining time to spawn next mob
	float _timeToNext;
	/// @brief index of next mob in the current MobModelLayout
	/// 0 means no mob has been spawned from current layout
	int _indexNext;

	/// @brief iterator to the current layout to spawn
	std::list<MobEntityLayout>::const_iterator _currentLayout;

	/// @brief incerement current layout if necessary
	/// reset _indexNext when changing layout
	/// @return true if there is a layout to spawn left
	bool nextLayoutIfNecessary();
};
