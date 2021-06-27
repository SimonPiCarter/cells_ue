// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectList.h"

UEffectNode::UEffectNode()
	: prev(nullptr)
	, next(nullptr)
	, val(nullptr)
{
}

UEffectNode::~UEffectNode()
{
}

UEffectList::UEffectList()
	: tail(nullptr)
	, head(nullptr)
{
}

UEffectList::~UEffectList()
{
}

// add to tail
void UEffectList::Add(UEffect* effect)
{
	UEffectNode* newnode_l = NewObject<UEffectNode>(this);
	newnode_l->val = effect;
	if (nullptr != tail)
	{
		// add link at end
		tail->next = newnode_l;
		newnode_l->prev = tail;
		// update tail
		tail = newnode_l;
	}
	else
	{
		// new List
		head = newnode_l;
		tail = newnode_l;
	}
}

void UEffectList::Remove(UEffectNode* node)
{
	// update links
	if(nullptr != node->prev)
		node->prev->next = node->next;
	if (nullptr != node->next)
		node->next->prev = node->prev;
	// update head or tail
	if (head == node)
	{
		head = node->next;
	}
	if (tail == node)
	{
		tail = node->prev;
	}
	// unlink (to avoid cyclic linkage)
	node->next = nullptr;
	node->prev = nullptr;
}
