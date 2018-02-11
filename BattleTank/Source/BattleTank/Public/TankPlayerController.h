// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintImplementableEvent)
	void FoundAimingComponent(UTankAimingComponent *AimingComponent);

private:

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

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
