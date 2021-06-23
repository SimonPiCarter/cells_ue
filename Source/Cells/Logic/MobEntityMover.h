// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <list>

class AMobEntity;
class UWaveEngine;

/**
 * 
 */
class CELLS_API MobEntityMover
{
public:
	MobEntityMover(UWaveEngine& waveEngine_p);
	~MobEntityMover();

	void moveEntities(TArray< AMobEntity*> const & mobs_p, float elapsedTime_p);

protected:
	UWaveEngine& _waveEngine;
};
