// Fill out your copyright notice in the Description page of Project Settings.


#include "MobEntityMover.h"

#include "../MobEntity.h"
#include "WaveEngine.h"

MobEntityMover::MobEntityMover(WaveEngine& waveEngine_p) : _waveEngine(waveEngine_p)
{
}

MobEntityMover::~MobEntityMover()
{
}

void MobEntityMover::moveEntities(std::list<AMobEntity*> mobs_p, float elapsedTime_p)
{
	for (AMobEntity* mob_l : mobs_p)
	{
		FVector currentLocation_l = mob_l->GetActorLocation();
		float remaining_l = elapsedTime_p;
		// skip if at last checkpoint
		while (!mob_l->isAtLastCheckPoint() && remaining_l > 1e-7)
		{
			// direction to next checkpoint
			std::array<double, 2> const& checkpoint_l = mob_l->getCurrentCheckPoint();
			FVector target_l = FVector(checkpoint_l[0], checkpoint_l[1], currentLocation_l.Z);
			FVector direction_l = target_l - currentLocation_l;
			// normalize direction
			float length_l = direction_l.Size();
			direction_l /= length_l;
			// reached checkpoint
			if (length_l < remaining_l * mob_l->speed)
			{
				currentLocation_l = target_l;
				remaining_l -= length_l / mob_l->speed;
				mob_l->incrementCheckPoint();
			}
			else
			{
				currentLocation_l += remaining_l * mob_l->speed * direction_l;
				remaining_l = 0;
			}

		}
		std::array<double, 2> oldPos_l = { mob_l->GetActorLocation().X, mob_l->GetActorLocation().Y };
		std::array<double, 2> newPos_l = { currentLocation_l.X, currentLocation_l.Y };
		_waveEngine.moveMob(mob_l, oldPos_l, newPos_l);
		mob_l->SetActorLocation(currentLocation_l);
	}
}
