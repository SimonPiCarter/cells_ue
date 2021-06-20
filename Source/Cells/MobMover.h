// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Logic.h"

#include <list>

#include "MobMover.generated.h"

class AMobEntity;

/**
 * 
 */
UCLASS()
class CELLS_API AMobMover : public ALogic
{
	GENERATED_BODY()

public:
	
	void addMob(AMobEntity* mob_l);

protected:
	virtual void runlogic(float elapsedTime_p);

	std::list<AMobEntity*> _mobs;
};
