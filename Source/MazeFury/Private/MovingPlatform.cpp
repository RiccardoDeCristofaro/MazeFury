// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "Math/UnitConversion.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	PlatformStartPosition = GetActorLocation();
	ActorCurrentPosition = PlatformStartPosition;
	const FString MyString = GetName();
	UE_LOG(LogTemp, Display, TEXT("%f"), DistanceMoved);
	UE_LOG(LogTemp, Display, TEXT("%s"), *MyString);
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if(PlatformReturn())
	{
		const FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		PlatformStartPosition += MoveDirection * DistanceMoved;
		SetActorLocation(PlatformStartPosition);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		ActorCurrentPosition += PlatformVelocity * DeltaTime;
		SetActorLocation(ActorCurrentPosition);	
	}
}
void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation = PlatformRotation * DeltaTime;uoiyu
	AddActorLocalRotation(CurrentRotation);
	SetActorRelativeRotation(PlatformRotation);
}
bool AMovingPlatform::PlatformReturn() const
{
	const float OverShoot = GetDistanceMoved() - DistanceMoved;
	UE_LOG(LogTemp, Display, TEXT("%f"), OverShoot);
	return GetDistanceMoved() > DistanceMoved;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(PlatformStartPosition, GetActorLocation()); // RETURN FLOAT
}





