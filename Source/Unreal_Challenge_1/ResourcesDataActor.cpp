// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourcesDataActor.h"

// Sets default values
AResourcesDataActor::AResourcesDataActor()
{
	StoneAmount = 0; 
	WoodAmount = 100; 
}

// Called when the game starts or when spawned
void AResourcesDataActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResourcesDataActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResourcesDataActor::SetStoneAmount(int Amount)
{
	StoneAmount = Amount;
}

int AResourcesDataActor::GetStoneAmount() const
{
	return StoneAmount;
}

void AResourcesDataActor::SetWoodAmount(int Amount)
{
	WoodAmount = Amount;
}

int AResourcesDataActor::GetWoodAmount() const
{
	return WoodAmount;
}

