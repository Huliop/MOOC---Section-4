// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"

// Permet le mouvement vertical du Barrel
void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	
	auto Elevation = FMath::Clamp<float>(
		RawNewElevation,
		MinElevationDegrees,
		MaxElevationDegrees
	);
	FRotator RelativeRotation = FRotator(Elevation, 0, 0);

	SetRelativeRotation(RelativeRotation);
}