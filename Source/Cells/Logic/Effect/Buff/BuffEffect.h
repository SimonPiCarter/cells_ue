// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Effect.h"
#include "BuffEffect.generated.h"

/**
 * 
 */
UCLASS()
class CELLS_API UBuffEffect : public UEffect
{
	GENERATED_BODY()
public:
	UBuffEffect();

	void setId(std::string const & id_p) { _id = id_p; }
	std::string const &getId() const { return _id; }

	/// to be extended
	virtual void runEffect(float elapsedTime_p);

	/// to be extended
	// apply effect
	virtual void apply() {}
	/// to be extended
	// revert effect
	virtual void revert() {}
	/// to be extended
	// refresh the effect (eg : reset timer)
	virtual void refresh() {}

	/// to be extended
	virtual bool isBuffOver(float elapsedTime_p) { return false; }

	/// @brief to be called to register the buff in the target
	/// MUST BE CALLED when buff is applied
	void registerBuff();
	/// @brief unregister the buff from the target
	/// MUST BE CALLED when buff is reverted
	void unregisterBuff();
	/// @brief check if buff is already registered in target
	bool isRegistered();
	/// @brief return ref to buff with same id registered in the target
	/// @throw if none
	UBuffEffect & getRegisteredBuff();

	UFUNCTION(BlueprintCallable, Category = "BuffEffect")
		void setIdImpl(FString const &id_p);
protected:
	bool _applied;
private:
	/// @brief unique id used to know if the buff is already applied to the target or not
	std::string _id;
};
