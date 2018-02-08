// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;

	/// Pour choper l'endroit ou on regarde
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	FVector2D GetPixelOfScreenThroughCrosshair() const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;
	int32 LineTraceRange = 1000000;

};
