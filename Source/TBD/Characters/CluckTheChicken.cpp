// Fill out your copyright notice in the Description page of Project Settings.

#include "CluckTheChicken.h"
#include "Parents/ProjectileParent.h"
#include "Engine/World.h"
#include "SpecialActors/ShiledParent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
ACluckTheChicken::ACluckTheChicken()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArmF = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmF"));
	SpringArmI = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmI"));
	SpringArmL = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmL"));
	EggF = CreateDefaultSubobject< UStaticMeshComponent>(FName("EggF"));
	EggL = CreateDefaultSubobject< UStaticMeshComponent>(FName("EggL"));
	EggI = CreateDefaultSubobject< UStaticMeshComponent>(FName("EggI"));
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
	Eggs.Add(EggF);
	Eggs.Add(EggL);
	Eggs.Add(EggI);
}

void ACluckTheChicken::Skill2YourThing()
{
	if (PickClosestEgg()->GetName() == EggF->GetName()) {

	}
	else if (PickClosestEgg()->GetName() == EggL->GetName()) {

	}
	else if (PickClosestEgg()->GetName() == EggI->GetName()) {

	}
}
void ACluckTheChicken::Tick(float DeltaTime)
{
	SpringArmF->AddLocalRotation(FQuat(FRotator(0, Multiplier *DeltaTime, 0)));
	SpringArmL->AddLocalRotation(FQuat(FRotator(0, Multiplier *DeltaTime, 0)));
	SpringArmI->AddLocalRotation(FQuat(FRotator(0, Multiplier *DeltaTime, 0)));
	
}
UStaticMeshComponent * ACluckTheChicken::PickClosestEgg()
{
	float EggsChossenNum = BIG_NUMBER;
	int i = -1;
	for (UStaticMeshComponent * Egg : Eggs)
	{
		if (EggsChossenNum > (ArrowComponent1->GetComponentLocation() - Egg->GetComponentLocation()).Size())
		{
			EggsChossenNum = (ArrowComponent1->GetComponentLocation() - Egg->GetComponentLocation()).Size();
			i++;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Eggs[i]->GetName());
	return Eggs[i];
}
