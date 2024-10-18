// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWorkerActor::AWorkerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Level = 1;
	bIsActive = true;

    // Create a Scene Component as the root
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent;

    WorkerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WorkerMesh"));
    WorkerMesh->SetupAttachment(RootSceneComponent); // Attach the WorkerMesh to the root scene component

    InitializeStats();
}

// Called when the game starts or when spawned
void AWorkerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorkerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsActive)
	{
		GatherResources();
	}
}

void AWorkerActor::InitializeStats()
{
    // Initialize gathering rates
    WoodGatherRates.Add(1, 10);
    WoodGatherRates.Add(2, 15);
    WoodGatherRates.Add(3, 20);
    WoodGatherRates.Add(4, 25);
    WoodGatherRates.Add(5, 30);

    StoneGatherRates.Add(1, 4);
    StoneGatherRates.Add(2, 8);
    StoneGatherRates.Add(3, 12);
    StoneGatherRates.Add(4, 16);
    StoneGatherRates.Add(5, 20);

    // Initialize costs
    LevelCosts.Add(2, { {"Wood", 10}, {"Stone", 10} });
    LevelCosts.Add(3, { {"Wood", 15}, {"Stone", 10} });
    LevelCosts.Add(4, { {"Wood", 20}, {"Stone", 15} });
    LevelCosts.Add(5, { {"Wood", 30}, {"Stone", 20} });
}

void AWorkerActor::ActivateWorker()
{
    bIsActive = true;
    CurrentState = EWorkerState::Gathering;
}

void AWorkerActor::GatherResources()
{
    if (CurrentState == EWorkerState::Gathering && ResourceTargetActor)
    {
        MoveToTarget(ResourceTargetActor->GetActorLocation());
    }
    else if (CurrentState == EWorkerState::Delivering && BaseTargetActor)
    {
        MoveToTarget(BaseTargetActor->GetActorLocation());
    }
}

void AWorkerActor::MoveToTarget(FVector CurrentTarget)
{
    // Get the current location of the worker
    FVector CurrentLocation = GetActorLocation();
    FVector Distance = CurrentTarget - CurrentLocation;
    float DistanceToTarget = Distance.Size();

    // Normalize the distance vector to get the direction
    Distance.Normalize();

    // Maintain the Z position
    FVector NewLocation = CurrentLocation;
    NewLocation.Z = CurrentLocation.Z; // Keep the same height

    // Move the worker towards the target
    NewLocation += Distance * MovementSpeed * GetWorld()->DeltaTimeSeconds;
    SetActorLocation(NewLocation);

    // Check if the worker has reached the target
    if (DistanceToTarget <= 1.0f || (MovementSpeed * GetWorld()->DeltaTimeSeconds) >= DistanceToTarget)
    {
        // Snap to the target location
        SetActorLocation(CurrentTarget);

        // Switch targets
        if (CurrentTarget == ResourceTargetActor->GetActorLocation())
        {
            CurrentTarget = BaseTargetActor->GetActorLocation();
            CurrentState = EWorkerState::Delivering; // Update state
        }
        else
        {
            CurrentTarget = ResourceTargetActor->GetActorLocation();
            CurrentState = EWorkerState::Gathering; // Update state
        }
    }
}

bool AWorkerActor::LevelUp()
{
    if (Level < 5)
    {
        Level++;

        // Increase movement speed based on the new level
        switch (Level)
        {
        case 3:
            MovementSpeed *= 1.05f; // Increase by 5%
            break;
        case 4:
            MovementSpeed *= 1.10f; // Increase by 10%
            break;
        case 5:
            MovementSpeed *= 1.15f; // Increase by 15%
            break;
        default:
            break;
        }

        return true; // Level up successful
    }


    return false; // Already at max level
}

float AWorkerActor::GetWoodGatherRate() const
{
    return WoodGatherRates[Level];
}

float AWorkerActor::GetStoneGatherRate() const
{
    return StoneGatherRates[Level];
}

