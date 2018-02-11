// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	auto AITank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	//Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim towards the player
	FVector HitLocation = PlayerTank->GetActorLocation();
	AimingComponent->AimAt(HitLocation);
	AimingComponent->Fire();
}