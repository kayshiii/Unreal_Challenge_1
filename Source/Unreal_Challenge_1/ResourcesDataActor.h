// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourcesDataActor.generated.h"

UCLASS()
class UNREAL_CHALLENGE_1_API AResourcesDataActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourcesDataActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void SetStoneAmount(int Amount);

    int GetStoneAmount() const;

    void SetWoodAmount(int Amount);

    int GetWoodAmount() const;

    int StoneAmount;

    int WoodAmount;
};
