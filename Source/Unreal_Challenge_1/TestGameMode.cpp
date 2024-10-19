// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameMode.h"
#include "MyHUD.h"

ATestGameMode::ATestGameMode()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set default HUD class
    HUDClass = AMyHUD::StaticClass();

    // Initialize game variables
    WoodCount = 100;
    StoneCount = 0;
    ActiveWorkers = 0;
    WorkerLevel = 1;
    SiloCount = 1;
    MaxWood = 100;
    MaxStone = 25;
}

void ATestGameMode::BeginPlay()
{
    Super::BeginPlay();
    UpdateHUD();
}

void ATestGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Implement resource gathering logic here if needed
}

void ATestGameMode::AddWood(int32 Amount)
{
    WoodCount = FMath::Min(WoodCount + Amount, MaxWood);
    UpdateHUD();
}

void ATestGameMode::AddStone(int32 Amount)
{
    StoneCount = FMath::Min(StoneCount + Amount, MaxStone);
    UpdateHUD();
}

void ATestGameMode::ActivateWorker()
{
    if (ActiveWorkers < 21 && WoodCount >= 20)
    {
        WoodCount -= 20;
        ActiveWorkers++;
        UpdateHUD();
    }
}

void ATestGameMode::UpgradeWorkers()
{
    // Implement worker upgrade logic
    // This will depend on your specific upgrade costs and effects
}

void ATestGameMode::BuildSilo()
{
    if (SiloCount < 6 && WoodCount >= 50)
    {
        WoodCount -= 50;
        SiloCount++;
        MaxWood += 100;
        MaxStone += 25;
        UpdateHUD();
    }
}

void ATestGameMode::UpdateHUD()
{
    AMyHUD* HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
    if (HUD)
    {
        HUD->UpdateResources(WoodCount, StoneCount, ActiveWorkers);
    }
}

void ATestGameMode::CheckResourceLimits()
{
    WoodCount = FMath::Min(WoodCount, MaxWood);
    StoneCount = FMath::Min(StoneCount, MaxStone);
}