#include "WorkerActor.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWorkerActor::AWorkerActor()
{
    PrimaryActorTick.bCanEverTick = true;

    Level = 1;
    bIsActive = false;
    
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent;

    WorkerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WorkerMesh"));
    WorkerMesh->SetupAttachment(RootSceneComponent); 

    //InitializeStats();
}

// Called when the game starts or when spawned
void AWorkerActor::BeginPlay()
{
    Super::BeginPlay();

    ActivateWorker();
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

// Function to set reference to ResourcesDataActor
void AWorkerActor::SetResourcesDataActor(AResourcesDataActor* ResourcesActor)
{
    if (ResourcesActor)
    {
        ResourcesDataActorRef = ResourcesActor;
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
    CurrentTarget = BasePoint;
}

void AWorkerActor::GatherResources()
{
    FVector CurrentLocation = GetActorLocation();
    FVector Distance = CurrentTarget - CurrentLocation;
    FVector NewLocation = CurrentLocation;
    float DistanceToTarget = Distance.Size();

    Distance.Normalize();

    NewLocation.Z = CurrentLocation.Z;
    NewLocation = CurrentLocation + Distance * MovementSpeed;
    SetActorLocation(NewLocation);

    if (DistanceToTarget <= 10.0f)
    {
        SetActorLocation(CurrentTarget);
        if (CurrentTarget == BasePoint)
        {
            CurrentTarget = ResourcePoint;
        }
        else
        {
            CurrentTarget = BasePoint;
        }
    }
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
    if (ResourcesDataActorRef)
    {
        TMap<FString, int32> LevelCost = LevelCosts[Level + 1];
        if (ResourcesDataActorRef->GetWoodAmount() >= LevelCost["Wood"] && ResourcesDataActorRef->GetStoneAmount() >= LevelCost["Stone"])
        {
            ResourcesDataActorRef->SetWoodAmount(ResourcesDataActorRef->GetWoodAmount() - LevelCost["Wood"]);
            ResourcesDataActorRef->SetStoneAmount(ResourcesDataActorRef->GetStoneAmount() - LevelCost["Stone"]);
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
        ResourcesDataActorRef->SetWoodAmount(ResourcesDataActorRef->GetWoodAmount() + WoodGathered);
    }

    // Add stone
    else
    {
        ResourcesDataActorRef->SetWoodAmount(ResourcesDataActorRef->GetStoneAmount() + StoneGathered);
    }
}