// Fill out your copyright notice in the Description page of Project Settings.

#include "CluckTheChicken.h"
#include "Engine/World.h"
#include "SpecialActors/ShiledParent.h"
#include "Components/StaticMeshComponent.h"
ACluckTheChicken::ACluckTheChicken()
{
	PrimaryActorTick.bCanEverTick = true;
	EggF = CreateDefaultSubobject< UStaticMeshComponent>(FName("EggF"));
	EggL = CreateDefaultSubobject< UStaticMeshComponent>(FName("EggL"));
	EggI = CreateDefaultSubobject< UStaticMeshComponent>(FName("EggI"));
	EggF->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	EggL->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	EggI->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}
void ACluckTheChicken::BlockDoYourThing() {
	if (bIsShiledActive)
	{
		bIsShiledActive = false;
		Shiled->Dactive();
		return;
	}
	if (!bIsShiledActive)
	{
		bIsShiledActive = true;
		Shiled->Active();
		return;
	}
}

void ACluckTheChicken::BeginPlay()
{
	Super::BeginPlay();
	 Shiled = GetWorld()->SpawnActor<AShiledParent>(ShiledParentTsubClass, FTransform(FRotator(0, 0, 0), GetActorLocation() + (GetActorForwardVector() * 100), FVector(1)));
	Shiled->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	Shiled->Dactive();
}

void ACluckTheChicken::Tick(float DeltaTime)
{
	FVector NewLocationF = GetActorLocation();
	AngleAxisF += DeltaTime * MultiplierF;

	if (AngleAxisF >= 360.0f)
	{
		AngleAxisF = 0;
		MultiplierF = 50;
	}

	FVector RotateValueF = Dimensions.RotateAngleAxis(AngleAxisF, AxisVector);

	NewLocationF.X += RotateValueF.X;
	NewLocationF.Y += RotateValueF.Y;
	NewLocationF.Z += RotateValueF.Z;

	FRotator NewRotationF = FRotator(0, AngleAxisF, 0);

	FQuat QuatRotationF = FQuat(NewRotationF);
	EggF->SetWorldLocationAndRotation(NewLocationF, QuatRotationF, false, 0, ETeleportType::None);
	
	FVector NewIocationL = GetActorLocation();
	AngleAxisL += DeltaTime * MultiplierL;

	if (AngleAxisL >=   360.0f)
	{
		AngleAxisL = 0;
		MultiplierL = 50;
	}

	FVector RotateValueL = Dimensions.RotateAngleAxis(AngleAxisL, AxisVector);

	NewIocationL.X += RotateValueL.X;
	NewIocationL.Y += RotateValueL.Y;
	NewIocationL.Z += RotateValueL.Z;

	FRotator NewRotationL = FRotator(0, AngleAxisL, 0);

	FQuat QuatRotationL = FQuat(NewRotationL);
	EggL->SetWorldLocationAndRotation(NewIocationL, QuatRotationL, false, 0, ETeleportType::None);
	
	FVector NewIocationI = GetActorLocation();
	AngleAxisI += DeltaTime * MultiplierI;

	if (AngleAxisI >= 360.0f)
	{
		AngleAxisI = 0;
		MultiplierI = 50;
	}

	FVector RotateValueI = Dimensions.RotateAngleAxis(AngleAxisI, AxisVector);

	NewIocationI.X += RotateValueI.X;
	NewIocationI.Y += RotateValueI.Y;
	NewIocationI.Z += RotateValueI.Z;

	FRotator NewRotationI = FRotator(0, AngleAxisI, 0);

	FQuat QuatRotationI = FQuat(NewRotationI);
	EggI->SetWorldLocationAndRotation(NewIocationI, QuatRotationI, false, 0, ETeleportType::None);
	
}