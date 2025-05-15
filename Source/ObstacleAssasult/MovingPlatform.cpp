// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

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

	UE_LOG(LogTemp, Display, TEXT("Configured moved distance : %f") , MoveDistance);  //output logda mesaj yazar , kısaca ulog yazarak yazabiliriz

    FString Name= GetName();
	UE_LOG(LogTemp, Display, TEXT("Begin Play : %s") ,*Name);  //string yaparken %s ve değişkenin başına dönüştürmek için * işareti konulur
		
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

	/* FVector LocalVector= MyVector;    önceki kodlar

	LocalVector.Z=LocalVector.Z+100;

	MyVector.Y=MyVector.Y+1;

	SetActorLocation(LocalVector);
 */
	

}

void AMovingPlatform::MovePlatform(float DeltaTime)   //buradaki A Actor demek
{
	FVector CurrentLocation=GetActorLocation();
	CurrentLocation=CurrentLocation + (PlatformVelocity*DeltaTime);  //deltatime ile her bilgisayarda aynı frame ilerlemesi sağlanır
	SetActorLocation(CurrentLocation);
  

	if(ShouldPlatformReturn())
	{
		PlatformVelocity=-PlatformVelocity;
		StartLocation=CurrentLocation;
	}

}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation,GetActorLocation());
}

