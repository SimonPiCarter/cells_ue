// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

template<typename T>
class PositionalNode;

template<typename T>
struct StorageInfo
{
	/// @brief node containing the content
	PositionalNode<T>* node;
	/// @brief index in the node where the content is stored
	unsigned long index;
};
