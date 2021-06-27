// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EffectList.generated.h"

class UEffect;

/**
 *
 */
UCLASS()
class CELLS_API UEffectNode : public UObject
{
	GENERATED_BODY()
public:
	UEffectNode();
	~UEffectNode();

	UPROPERTY(BlueprintReadOnly, Category = "EffectNode")
		UEffectNode* prev;

	UPROPERTY(BlueprintReadOnly, Category = "EffectNode")
		UEffectNode* next;

	UPROPERTY(BlueprintReadOnly, Category = "EffectNode")
		UEffect* val;
};

/**
 * 
 */
UCLASS()
class CELLS_API UEffectList : public UObject
{
	GENERATED_BODY()
public:
	UEffectList();
	~UEffectList();

	UFUNCTION(BlueprintCallable, Category = "EffectList")
		void Add(UEffect* effect);

	UFUNCTION(BlueprintCallable, Category = "EffectList")
		void Remove(UEffectNode* node);

	UPROPERTY(BlueprintReadOnly, Category = "EffectList")
		UEffectNode* tail;

	UPROPERTY(BlueprintReadOnly, Category = "EffectList")
		UEffectNode* head;
};
