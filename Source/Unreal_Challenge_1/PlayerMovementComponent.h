// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_CHALLENGE_1_API UPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveActorX(float axisValue);
	void MoveActorY(float axisValue);
	void RotateAxisY(float axisValue);

	UPROPERTY(EditAnywhere)
	APawn* mainBodyPawn;

	UPROPERTY(EditAnywhere)
	float ROTATE_MULTIPLIER = 5.0f;

	UPROPERTY(EditAnywhere)
	float SPEED_MULTIPLIER = 20.0f;

	UPROPERTY(EditAnywhere)
	float DECELERATION_PERCENTAGE = 0.2f;

	const FName MOVE_X_AXIS_NAME = FName("MOVE_X");
	const FName MOVE_Y_AXIS_NAME = FName("MOVE_Y");
	const FName ROTATE_Y_AXIS_NAME = FName("ROTATE_Y");

	float xMoveSpeed = 0.0f;
	float yMoveSpeed = 0.0f;
	float rotateSpeed = 0.0f;
};
