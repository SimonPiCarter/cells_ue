// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <list>

class AMobEntity;
class WaveEngine;

/**
 * 
 */
class CELLS_API MobEntityMover
{
public:
	MobEntityMover(WaveEngine& waveEngine_p);
	~MobEntityMover();

	void moveEntities(std::list<AMobEntity*> mobs_p, float elapsedTime_p);

protected:
	WaveEngine& _waveEngine;
};
