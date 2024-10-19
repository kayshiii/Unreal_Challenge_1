#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourcesDataActor.h"
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

    void SetResourcesDataActor(AResourcesDataActor* ResourcesActor);

    void InitializeStats();

    void ActivateWorker();

    void GatherResources();

    bool LevelUp();

    float GetWoodGatherRate();

    float GetStoneGatherRate();

private:
    AResourcesDataActor* ResourcesDataActorRef;

    // Gathering rates and costs
    TMap<int32, float> WoodGatherRates;
    TMap<int32, float> StoneGatherRates;
    TMap<int32, TMap<FString, int32>> LevelCosts;

    UPROPERTY(EditAnywhere, Category = "RootSceneComponent")
    USceneComponent* RootSceneComponent;

    UPROPERTY(EditAnywhere, Category = "WorkerMesh")
    USkeletalMeshComponent* WorkerMesh;

    UPROPERTY(EditAnywhere, Category = "ResourceTarget")
    FVector ResourcePoint; 

    UPROPERTY(EditAnywhere, Category = "BaseTarget")
    FVector BasePoint;

    FVector CurrentTarget;

    UPROPERTY(EditAnywhere, Category = "MovementSpeed");
    float MovementSpeed;

    // Worker stats
    int32 Level;
    bool bIsActive;

    UPROPERTY(EditAnywhere, Category = "ResourceType") // 0 = Wood, 1 = Stone
    bool bResourceType;

    void AddResources(bool bType);
};