// Fill out your copyright notice in the Description page of Project Settings.

#include "BeamParent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
// Sets default values
ABeamParent::ABeamParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BeamMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>(FName("BeamMeshComponent"));
}

// Called when the game starts or when spawned
void ABeamParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABeamParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABeamParent::Lunch()
{
	FHitResult Hit;
	FVector Startl = GetActorLocation();
	FVector Endl = GetActorLocation() + GetActorForwardVector() * LineTrachRange;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Startl, Endl, ECollisionChannel::ECC_Visibility)) {
		
		SetActorScale3D(FVector((Endl - Startl).Size() / 100, GetActorScale().Y, GetActorScale().Z));
	}
}

