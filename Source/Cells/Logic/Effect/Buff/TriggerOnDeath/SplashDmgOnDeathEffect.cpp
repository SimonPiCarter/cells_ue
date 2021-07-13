// Fill out your copyright notice in the Description page of Project Settings.


#include "SplashDmgOnDeathEffect.h"
#include "../../../../MobEntity.h"
#include "../../../LogicEngine.h"
#include "../../AttackEffect.h"

USplashDmgOnDeathEffect::USplashDmgOnDeathEffect() : UTriggerOnDeathEffect()
{
	setId("SplashDmgOnDeathEffect");
}

void USplashDmgOnDeathEffect::deathTrigger()
{
	FVector2D pos_l(_mobTarget->GetActorLocation().X, _mobTarget->GetActorLocation().Y);
	TArray<AMobEntity*> targets_l = logic->getAllMobWithinRadius(pos_l, _splash);
	for(AMobEntity* target_l : targets_l)
	{
		// add attack effect
		UAttackEffect * attackEffect_l = NewObject<UAttackEffect>(logic);
		attackEffect_l->_damage = _dmg * _stack;
		attackEffect_l->_dmgType = _dmgType;
		attackEffect_l->_mobTarget = target_l;
		attackEffect_l->source = source;
		logic->registerEffect(attackEffect_l);
	}
}
