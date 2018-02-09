// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	ATank* AITank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (PlayerTank) {
		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim towards the player
		FVector HitLocation = PlayerTank->GetActorLocation();
		AITank->AimAt(HitLocation);
		AITank->Fire();
	}
}