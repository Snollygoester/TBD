// Fill out your copyright notice in the Description page of Project Settings.

#include "CluckTheChicken.h"
#include "Parents/ProjectileParent.h"
#include "Engine/World.h"
#include "SpecialActors/ShiledParent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "SpecialActors/SpecialEggParent.h"
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
	ASpecialEggParent * ChossenEgg;
	if (PickClosestEgg()->GetName() == EggF->GetName()) {
	ChossenEgg = GetWorld()->SpawnActor<ASpecialEggParent>(EggFSubClass, FTransform(FRotator(0, 0, 0), ArrowComponent1->GetComponentLocation() + GetActorForwardVector() * 100, FVector(1)));
	ChossenEgg->GetActorToIgnre(this);
	ChossenEgg->Thorw(EggSpeed, GetActorForwardVector());
	}
	else if (PickClosestEgg()->GetName() == EggL->GetName()) {
		ChossenEgg = GetWorld()->SpawnActor<ASpecialEggParent>(EggLSubClass, FTransform(FRotator(0, 0, 0), ArrowComponent1->GetComponentLocation() + GetActorForwardVector() * 100, FVector(1)));
		ChossenEgg->GetActorToIgnre(this);
		ChossenEgg->Thorw(EggSpeed, GetActorForwardVector());
	}
	else if (PickClosestEgg()->GetName() == EggI->GetName()) {
		ChossenEgg = GetWorld()->SpawnActor<ASpecialEggParent>(EggISubClass, FTransform(FRotator(0, 0, 0), ArrowComponent1->GetComponentLocation() + GetActorForwardVector() * 100, FVector(1)));
		ChossenEgg->GetActorToIgnre(this);
		ChossenEgg->Thorw(EggSpeed, GetActorForwardVector());
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
	
	return Eggs[i];
}
