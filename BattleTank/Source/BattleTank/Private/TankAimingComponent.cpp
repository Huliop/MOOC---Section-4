// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"


UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

EFireStatus UTankAimingComponent::GetFireStatus() const
{
	return FireStatus;
}

int UTankAimingComponent::GetAmmoLeft() const
{
	return AmmoLeft;
}

// Renvoie les coordonnées de l'endroit où on vise
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		LaunchVelocity,
		StartLocation,
		HitLocation,
		FiringVelocity,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
}

void UTankAimingComponent::Initialize(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (AmmoLeft <= 0)
	{
		FireStatus = EFireStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		FireStatus = EFireStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FireStatus = EFireStatus::Aiming;
	}
	else
	{
		FireStatus = EFireStatus::Locked;
	}
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelDirection = Barrel->GetForwardVector().GetSafeNormal();

	return (!BarrelDirection.Equals(AimDirection, 0.05));
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator DeltaRotator = AimAsRotator - TurretRotator;

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{ 
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::Fire()
{
	if (FireStatus != EFireStatus::Reloading)
	{
		if (Barrel)
		{
			if (AmmoLeft > 0)
			{
				auto Projectile = GetWorld()->SpawnActor<AProjectile>(
					Projectile_BP,
					Barrel->GetSocketLocation(FName("Projectile")),
					Barrel->GetSocketRotation(FName("Projectile"))
					);
				Projectile->LaunchProjectile(FiringVelocity);
				LastFireTime = FPlatformTime::Seconds();
				AmmoLeft--;
			}
		}
	}
}
