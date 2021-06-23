// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <list>

#include "CoreMinimal.h"

class ATowerEntity;
class AMobEntity;
class UWaveEngine;

struct AttackInfo
{
	/// @brief pointer to the tower
	ATowerEntity* tower;
	/// @brief time to next attack
	float reload;
	/// @brief current target of the tower
	AMobEntity* target;
};

/**
 * 
 */
class CELLS_API AttackBuilder
{
public:
	AttackBuilder(UWaveEngine& waveEngine_p);
	~AttackBuilder();

	void buildAttacks(float elapsedTime_p);
protected:
	UWaveEngine& _waveEngine;

	std::list<AttackInfo> _attackInfos;
};
