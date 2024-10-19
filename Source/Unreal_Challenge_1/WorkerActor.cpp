#include "WorkerActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWorkerActor::AWorkerActor()
{
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
    FVector CurrentTarget;
    if (CurrentState == EWorkerState::Gathering && ResourceTargetActor)
    {
        MoveToTarget(ResourceTargetActor->GetActorLocation());

        // Check if the worker has reached the resource target
        if (FVector::Dist(GetActorLocation(), ResourceTargetActor->GetActorLocation()) <= 1.0f)
        {
            // Switch to delivering state
            CurrentTarget = BaseTargetActor->GetActorLocation();
            CurrentState = EWorkerState::Delivering; // Update state
        }
    }
    else if (CurrentState == EWorkerState::Delivering && BaseTargetActor)
    {
        MoveToTarget(BaseTargetActor->GetActorLocation());

        // Check if the worker has reached the base target
        if (FVector::Dist(GetActorLocation(), BaseTargetActor->GetActorLocation()) <= 1.0f)
        {
            AddResources(bResourceType);
            CurrentTarget = ResourceTargetActor->GetActorLocation();
            CurrentState = EWorkerState::Gathering; // Update state
        }
    }
}

void AWorkerActor::MoveToTarget(FVector CurrentTarget)
{
    // Move the worker towards the target
    FVector Direction = (CurrentTarget - GetActorLocation()).GetSafeNormal();
    AddActorLocalOffset(Direction * MovementSpeed);
}

float AWorkerActor::GetWoodGatherRate()
{
    return WoodGatherRates[Level];
}

float AWorkerActor::GetStoneGatherRate()
{
    return StoneGatherRates[Level];
}

bool AWorkerActor::LevelUp()
{
    if (ResourceData)
    {
        TMap<FString, int32> LevelCost = LevelCosts[Level + 1];
        if (ResourceData->GetWoodAmount() >= LevelCost["Wood"] && ResourceData->GetStoneAmount() >= LevelCost["Stone"])
        {
            ResourceData->SetWoodAmount(ResourceData->GetWoodAmount() - LevelCost["Wood"]);
            ResourceData->SetStoneAmount(ResourceData->GetStoneAmount() - LevelCost["Stone"]);
            Level++;
            return true;
        }
    }
    return false;
}

void AWorkerActor::AddResources(bool bType)
{
    float WoodGathered = GetWoodGatherRate();
    float StoneGathered = GetStoneGatherRate();

    if (bType)
    {
        ResourceData->SetWoodAmount(ResourceData->GetWoodAmount() + WoodGathered);
    }

    // Add stone
    else
    {
        ResourceData->SetWoodAmount(ResourceData->GetStoneAmount() + StoneGathered);
    }
}