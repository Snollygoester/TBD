// Fill out your copyright notice in the Description page of Project Settings.

#include "CluckTheChicken.h"
#include "Parents/ProjectileParent.h"
#include "Engine/World.h"
#include "SpecialActors/ShiledParent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"
ACluckTheChicken::ACluckTheChicken()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArmF = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmF"));
	SpringArmI = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmI"));
	SpringArmL = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmL"));
	EggF = CreateDefaultSubobject< UChildActorComponent>(FName("EggF"));
	EggL = CreateDefaultSubobject< UChildActorComponent>(FName("EggL"));
	EggI = CreateDefaultSubobject< UChildActorComponent>(FName("EggI"));
	SpringArmF->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	SpringArmL->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	SpringArmI->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	EggF->AttachToComponent(SpringArmF, FAttachmentTransformRules::KeepWorldTransform);
	EggL->AttachToComponent(SpringArmI, FAttachmentTransformRules::KeepWorldTransform);
	EggI->AttachToComponent(SpringArmL, FAttachmentTransformRules::KeepWorldTransform);
}
void ACluckTheChicken::BlockDoYourThing() {
	bIsShiledActive = Shiled->bIsShiledActive;
	if (bIsShiledActive)
	{
		Shiled->Dactive();
		return;
	}
	if (!bIsShiledActive)
	{
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
	SpringArmF->AddLocalRotation(FQuat(FRotator(0, Multiplier *DeltaTime, 0)));
	SpringArmL->AddLocalRotation(FQuat(FRotator(0, Multiplier *DeltaTime, 0)));
	SpringArmI->AddLocalRotation(FQuat(FRotator(0, Multiplier *DeltaTime, 0)));
	
}