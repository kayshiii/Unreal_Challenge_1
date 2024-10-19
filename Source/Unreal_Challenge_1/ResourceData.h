// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ResourceData.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CHALLENGE_1_API UResourceData : public UObject
{
	GENERATED_BODY()
	
public:
    // Constructor
    UResourceData();

    // Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
    int32 WoodAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
    int32 StoneAmount;

    // Function to set wood amount
    void SetWoodAmount(int32 Amount);

    // Function to set stone amount
    void SetStoneAmount(int32 Amount);

    // Function to get wood amount
    int32 GetWoodAmount() const;

    // Function to get stone amount
    int32 GetStoneAmount() const;
};
