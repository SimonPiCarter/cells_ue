// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveGenerator.h"

UWaveGenerator::UWaveGenerator()
{
	// set up all slot generator
	_generatorEngine.addGenerator(5, 0, "direct_attack");
	_generatorEngine.addGenerator(5, 0, "slow_effect");
	_generatorEngine.addGenerator(5, 0, "mult_dmg");
	_generatorEngine.addGenerator(5, 0, "dot_effect");
	_generatorEngine.addGenerator(5, 0, "splash_on_death_effect");
	_generatorEngine.addGenerator(5, 0, "speed_on_death_effect");
	_generatorEngine.addGenerator(5, 0, "dmg_bonus_on_death_effect");
	_generatorEngine.addGenerator(5, 0, "combo_effect");
	_generatorEngine.addGenerator(1, 50, "buff_dmg_last_hit");
}

UWavePackage* UWaveGenerator::getNextWavePackage()
{
	return spawnNextWavePackage();
}

void UWaveGenerator::generateSlots(UWavePackage* package, int count, ALogicEngine *logic, float minLevel, float maxLevel)
{
	std::list<USlot *> slots_l = _generatorEngine.generateSlots(count, logic, minLevel, maxLevel);

	for(USlot * slot_l : slots_l)
	{
		package->getRewards().Add(slot_l);
	}
}
