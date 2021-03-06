// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


// Effectu� au lancement du jeu
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

// Effectu� tous les tick
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

// D�but le mouvement de la tour et du canon du tank vers le r�ticule (crosshair) de vis�e
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

// Renvoie true si on touche l'environnement dans notre r�ticule, false sinon
// Change �galement la valeur de HitLocation pour la valeur o� on regarde � travers le r�ticule
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	FVector2D ScreenLocation = GetPixelOfScreenThroughCrosshair();
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	
	return false;
}

// Renvoie le pixel correspondant au r�ticule
FVector2D ATankPlayerController::GetPixelOfScreenThroughCrosshair() const
{
	// On chope le nombre de pixels de l'ecran en largeur et hauteur
	int32 SizeX, SizeY;
	GetViewportSize(SizeX, SizeY);

	// On chope le pixel correspondant a notre r�ticule
	FVector2D ScreenLocation = FVector2D(SizeX * CrosshairXLocation, SizeY * CrosshairYLocation);

	return ScreenLocation;
}

// On chope la direction dans laquelle on regarde � travers le r�ticule et renvoie true, false si impossible/endroit inexistant
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

// On chope la location de l'endroit ou on regarde � travers le r�ticule et renvoie true, false si impossible/endroit inexistant
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
