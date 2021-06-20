// Fill out your copyright notice in the Description page of Project Settings.


#include "MobMover.h"

#include "MobEntity.h"

void AMobMover::addMob(AMobEntity* mob_l)
{
	_mobs.push_back(mob_l);
}

void AMobMover::runlogic(float elapsedTime_p)
{
	for (AMobEntity* mob_l : _mobs)
	{
		mob_l->move(elapsedTime_p);
	}
}
