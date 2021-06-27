// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackBuilder.h"

#include "LogicEngine.h"
#include "WaveEngine.h"
#include "Slot/AttackModifier.h"
#include "../TowerEntity.h"

AttackBuilder::AttackBuilder(UWaveEngine& waveEngine_p)
	: _waveEngine(waveEngine_p)
{
	// Create AttackInfos
	for (ATowerEntity* tower_l : _waveEngine.getLogic().towers)
	{
		_attackInfos.push_back({ tower_l, 0., nullptr });
	}
}

AttackBuilder::~AttackBuilder()
{
}

void AttackBuilder::buildAttacks(float elapsedTime_p)
{
	for (AttackInfo& info_l : _attackInfos)
	{
		float remainingTime_l = elapsedTime_p;
		while (remainingTime_l > 0.)
		{
			// time consumed is minimum between reload time and elapsed time
			float consumed_l = std::min(info_l.reload, remainingTime_l);

			float speed_l = info_l.tower->getAttackSpeed();
			// if consumed >= reload we fire
			if (consumed_l >= info_l.reload
				&& speed_l > 0.)
			{
				// build attack with time stamp
				bool hasAttacked_l = false;
				info_l.tower->attackModifier->spawnAttack(&_waveEngine.getLogic(), info_l.tower, hasAttacked_l);
				// reset reload time
				if (hasAttacked_l)
				{
					info_l.reload = 1. / speed_l;
				}
				// else break loop there is no need to loop another time
				else
				{
					break;
				}
			}
			else
			{
				info_l.reload -= consumed_l;
			}

			remainingTime_l -= consumed_l;
		}
	}
}
