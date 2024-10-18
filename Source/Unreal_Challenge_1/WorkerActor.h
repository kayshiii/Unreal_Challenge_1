// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorkerActor.generated.h"

UENUM(BlueprintType)
enum class EWorkerState : uint8
{
    Gathering,
    Delivering
};

UCLASS()
class UNREAL_CHALLENGE_1_API AWorkerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorkerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void ActivateWorker();
    void GatherResources();
    bool LevelUp();
    float GetWoodGatherRate() const;
    float GetStoneGatherRate() const;

private:

    // Resource gathering rates
    TMap<int32, float> WoodGatherRates;
    TMap<int32, float> StoneGatherRates;
    TMap<int32, float> MovementSpeedRate;

    // Cost structure
    TMap<int32, TMap<FString, int32>> LevelCosts;

    int32 Level;
    bool bIsActive;

    EWorkerState CurrentState;

    UPROPERTY(EditAnywhere, Category = "Movement Speed")
    float MovementSpeed;

    // Root scene component
    UPROPERTY(VisibleAnywhere)
    USceneComponent* RootSceneComponent;

    UPROPERTY(VisibleAnywhere, Category = "Worker")
    UStaticMeshComponent* WorkerMesh;

    // Target actors for gathering and delivering resources
    UPROPERTY(EditAnywhere, Category = "Target Locations")
    AActor* ResourceTargetActor;  // Actor for resource gathering

    UPROPERTY(EditAnywhere, Category = "Target Locations")
    AActor* BaseTargetActor;   // Actor for resource delivery


    void MoveToTarget(FVector CurrentTarget);

    void InitializeStats();
};
