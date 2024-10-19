// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UResourceWidget;
/**
 * 
 */
UCLASS()
class UNREAL_CHALLENGE_1_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    AMyHUD();

    virtual void BeginPlay() override;

    // Function to update resources (call this from your game logic)
    void UpdateResources(int32 Wood, int32 Stone, int32 ActiveWorkers);

private:
    UPROPERTY()
    UResourceWidget* ResourceWidget;

    // Store the Widget Blueprint class
    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    TSubclassOf<UUserWidget> ResourceWidgetClass;
};
