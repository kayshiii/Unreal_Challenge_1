// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResourceWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CHALLENGE_1_API UResourceWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateResourceCounts(int32 Wood, int32 Stone);
	void UpdateMaxResources(int32 MaxWood, int32 MaxStone);
	void SetActiveWorkers(int32 ActiveWorkers);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WoodCountText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StoneCountText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxWoodText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxStoneText;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ActiveWorkersText;

	UFUNCTION(BlueprintCallable, Category = "Resource Widget")
	void SetWoodCount(int32 Wood);

	UFUNCTION(BlueprintCallable, Category = "Resource Widget")
	void SetStoneCount(int32 Stone);

	UFUNCTION(BlueprintCallable, Category = "Resource Widget")
	void SetMaxWood(int32 MaxWood);

	UFUNCTION(BlueprintCallable, Category = "Resource Widget")
	void SetMaxStone(int32 MaxStone);
};
