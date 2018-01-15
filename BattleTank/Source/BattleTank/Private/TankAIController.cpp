// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("Il n'y a pas de joueur possédant un tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Le joueur controllant le tank est %s"), *(PlayerTank->GetName()))
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	FVector HitLocation = GetPlayerTank()->GetActorLocation();
	GetControlledTank()->AimAt(HitLocation);
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) { return nullptr; }
	return Cast<ATank>(PlayerTank);
}
