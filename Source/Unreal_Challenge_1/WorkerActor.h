#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceData.h" // Include the ResourceData header
#include "WorkerActor.generated.h"

UCLASS()
class UNREAL_CHALLENGE_1_API AWorkerActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AWorkerActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void InitializeStats();
    void ActivateWorker();
    void GatherResources();
    void MoveToTarget(FVector CurrentTarget);
    bool LevelUp();
    void SetResourceData(UResourceData* NewResourceData) { ResourceData = NewResourceData; }

    float GetWoodGatherRate();
    float GetStoneGatherRate();

private:
    UPROPERTY()
    UResourceData* ResourceData; // Reference to the player's ResourceData

    // Gathering rates and costs
    TMap<int32, float> WoodGatherRates;
    TMap<int32, float> StoneGatherRates;
    TMap<int32, TMap<FString, int32>> LevelCosts;

    // Worker state and targets
    enum class EWorkerState { Gathering, Delivering };
    EWorkerState CurrentState;

    UPROPERTY(EditAnywhere, Category = "RootSceneComponent")
    USceneComponent* RootSceneComponent;

    UPROPERTY(EditAnywhere, Category = "WorkerMesh")
    UStaticMeshComponent* WorkerMesh;

    UPROPERTY(EditAnywhere, Category = "ResourceTarget")
    AActor* ResourceTargetActor; // The resource the worker is gathering from

    UPROPERTY(EditAnywhere, Category = "BaseTarget")
    AActor* BaseTargetActor; // The base where resources are delivered

    UPROPERTY(EditAnywhere, Category = "MovementSpeed");
    float MovementSpeed;

    // Worker stats
    int32 Level;
    bool bIsActive;

    UPROPERTY(EditAnywhere, Category = "ResourceType") // 0 = Wood, 1 = Stone
    bool bResourceType;

    void AddResources(bool bType);
};