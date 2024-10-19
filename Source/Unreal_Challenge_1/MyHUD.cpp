// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "ResourceWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AMyHUD::AMyHUD()
{
    // Load the Widget Blueprint class
    static ConstructorHelpers::FClassFinder<UUserWidget> ResourceWidgetBPClass(TEXT("/Content/HUD/WBP_UI.WBP_UI"));
    if (ResourceWidgetBPClass.Class != nullptr)
    {
        ResourceWidgetClass = ResourceWidgetBPClass.Class;
    }
}

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

    if (ResourceWidgetClass)
    {
        // Create the widget and add it to the viewport
        ResourceWidget = CreateWidget<UResourceWidget>(GetWorld(), ResourceWidgetClass);
        if (ResourceWidget)
        {
            ResourceWidget->AddToViewport();
        }
    }
}

void AMyHUD::UpdateResources(int32 Wood, int32 Stone, int32 ActiveWorkers)
{
    if (ResourceWidget)
    {
        ResourceWidget->UpdateResourceCounts(Wood, Stone);
        ResourceWidget->SetActiveWorkers(ActiveWorkers);
    }
}