// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceData.h"

UResourceData::UResourceData()
    : WoodAmount(0), StoneAmount(0) // Initialize amounts to zero
{
}

void UResourceData::SetWoodAmount(int32 Amount)
{
    WoodAmount = Amount;
}

void UResourceData::SetStoneAmount(int32 Amount)
{
    StoneAmount = Amount;
}

int32 UResourceData::GetWoodAmount() const
{
    return WoodAmount;
}

int32 UResourceData::GetStoneAmount() const
{
    return StoneAmount;
}