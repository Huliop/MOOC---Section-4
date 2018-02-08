// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"

// Permet le mouvement horizontal de la Turret
void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	FRotator RelativeRotation = FRotator(0, Rotation, 0);

	SetRelativeRotation(RelativeRotation);
}