// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


// Effectué au lancement du jeu
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
}

// Effectué tous les tick
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

// Renvoie le tank que l'on possède
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

// Début le mouvement de la tour et du canon du tank vers le réticule (crosshair) de visée
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

// Renvoie true si on touche l'environnement dans notre réticule, false sinon
// Change également la valeur de HitLocation pour la valeur où on regarde à travers le réticule
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	FVector2D ScreenLocation = GetPixelOfScreenThroughCrosshair();
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	
	return true;
}

// Renvoie le pixel correspondant au réticule
FVector2D ATankPlayerController::GetPixelOfScreenThroughCrosshair() const
{
	// On chope le nombre de pixels de l'ecran en largeur et hauteur
	int32 SizeX, SizeY;
	GetViewportSize(SizeX, SizeY);

	// On chope le pixel correspondant a notre réticule
	FVector2D ScreenLocation = FVector2D(SizeX * CrosshairXLocation, SizeY * CrosshairYLocation);

	return ScreenLocation;
}

// On chope la direction dans laquelle on regarde à travers le réticule et renvoie true, false si impossible/endroit inexistant
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const
{
	FVector WorldLocation;

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		WorldDirection
	);
}

// On chope la location de l'endroit ou on regarde à travers le réticule et renvoie true, false si impossible/endroit inexistant
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FVector TankLocation = PlayerCameraManager->GetCameraLocation();

	FVector LineTraceEnd = TankLocation + (LineTraceRange * LookDirection);
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			TankLocation,
			LineTraceEnd,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0.0);
	return false;
}
