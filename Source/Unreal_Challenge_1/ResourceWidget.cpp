// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceWidget.h"
#include "Components/TextBlock.h"

void UResourceWidget::UpdateResourceCounts(int32 Wood, int32 Stone)
{
    if(WoodCountText)
        WoodCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Wood)));
    if (StoneCountText)
        StoneCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Stone)));
}

void UResourceWidget::UpdateMaxResources(int32 MaxWood, int32 MaxStone)
{
    SetMaxWood(MaxWood);
    SetMaxStone(MaxStone);
}

void UResourceWidget::SetWoodCount(int32 Wood)
{
    if (WoodCountText)
    {
        WoodCountText->SetText(FText::FromString(FString::Printf(TEXT("Wood: %d"), Wood)));
    }
}

void UResourceWidget::SetStoneCount(int32 Stone)
{
    if (StoneCountText)
    {
        StoneCountText->SetText(FText::FromString(FString::Printf(TEXT("Stone: %d"), Stone)));
    }
}

void UResourceWidget::SetMaxWood(int32 MaxWood)
{
    if (MaxWoodText)
    {
        MaxWoodText->SetText(FText::FromString(FString::Printf(TEXT("Max Wood: %d"), MaxWood)));
    }
}

void UResourceWidget::SetMaxStone(int32 MaxStone)
{
    if (MaxStoneText)
    {
        MaxStoneText->SetText(FText::FromString(FString::Printf(TEXT("Max Stone: %d"), MaxStone)));
    }
}

void UResourceWidget::SetActiveWorkers(int32 ActiveWorkers)
{
    if (ActiveWorkersText)
        ActiveWorkersText->SetText(FText::FromString(FString::Printf(TEXT("%d"), ActiveWorkers)));
}
