// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementComponent.h"

// Sets default values for this component's properties
UPlayerMovementComponent::UPlayerMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	this->mainBodyPawn->InputComponent->BindAxis(MOVE_X_AXIS_NAME, this, &UPlayerMovementComponent::MoveActorX);
	this->mainBodyPawn->InputComponent->BindAxis(MOVE_Y_AXIS_NAME, this, &UPlayerMovementComponent::MoveActorY);
	this->mainBodyPawn->InputComponent->BindAxis(ROTATE_Y_AXIS_NAME, this, &UPlayerMovementComponent::RotateAxisY);
}


// Called every frame
void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (0 != this->xMoveSpeed || 0 != this->yMoveSpeed) {
		FVector location = this->mainBodyPawn->GetTransform().GetLocation();
		location.X += this->xMoveSpeed * SPEED_MULTIPLIER;
		location.Y += this->yMoveSpeed * SPEED_MULTIPLIER;
		this->mainBodyPawn->SetActorLocation(location);
	}
	if (0 != this->xMoveSpeed) {
		this->xMoveSpeed *= (1 - DECELERATION_PERCENTAGE);
		if (abs(this->xMoveSpeed) < 0.1f) this->xMoveSpeed = 0;
	}
	if (0 != this->yMoveSpeed) {
		this->yMoveSpeed *= (1 - DECELERATION_PERCENTAGE);
		if (abs(this->yMoveSpeed) < 0.1f) this->yMoveSpeed = 0;
	}

	if (0 != this->rotateSpeed) {
		FRotator rotation = this->mainBodyPawn->GetActorRotation();
		rotation += FRotator(0.0f, rotateSpeed * ROTATE_MULTIPLIER, 0.0f);
		this->mainBodyPawn->SetActorRotation(rotation);
	}

	if (0 != this->rotateSpeed) {
		this->rotateSpeed *= (1 - DECELERATION_PERCENTAGE);
		if (abs(this->rotateSpeed) < 0.1f) this->rotateSpeed = 0;
	}

}

void UPlayerMovementComponent::MoveActorX(float axisValue)
{
	if (0 != axisValue) {
		this->xMoveSpeed = FMath::Clamp(axisValue, -1, 1);
	}
}

void UPlayerMovementComponent::MoveActorY(float axisValue)
{
	if (0 != axisValue) {
		this->yMoveSpeed = FMath::Clamp(axisValue, -1, 1);
	}
}

void UPlayerMovementComponent::RotateAxisY(float axisValue)
{
	if (0 != axisValue) {
		this->rotateSpeed = FMath::Clamp(axisValue, -1, 1);
	}
}

