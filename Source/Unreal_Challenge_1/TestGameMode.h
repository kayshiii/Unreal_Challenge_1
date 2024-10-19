// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CHALLENGE_1_API ATestGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    ATestGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Resources")
    void AddWood(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Resources")
    void AddStone(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Workers")
    void ActivateWorker();

    UFUNCTION(BlueprintCallable, Category = "Upgrades")
    void UpgradeWorkers();

    UFUNCTION(BlueprintCallable, Category = "Construction")
    void BuildSilo();

private:
    UPROPERTY()
    int32 WoodCount;

    UPROPERTY()
    int32 StoneCount;

    UPROPERTY()
    int32 ActiveWorkers;

    UPROPERTY()
    int32 WorkerLevel;

    UPROPERTY()
    int32 SiloCount;

    UPROPERTY()
    int32 MaxWood;

    UPROPERTY()
    int32 MaxStone;

    void UpdateHUD();
    void CheckResourceLimits();
};
