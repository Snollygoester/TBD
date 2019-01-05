// Fill out your copyright notice in the Description page of Project Settings.

#include "CluckTheChicken.h"
#include "Parents/ProjectileParent.h"
#include "Engine/World.h"
#include "SpecialActors/ShiledParent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SpecialActors/SpecialEggParent.h"
#include "SpecialActors/BeamParent.h"
#include "Engine/World.h"
#include "RangedWeapons/C4Parent.h"
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
	EggL->AttachToComponent(SpringArmL, FAttachmentTransformRules::KeepWorldTransform);
	EggI->AttachToComponent(SpringArmI, FAttachmentTransformRules::KeepWorldTransform);
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

bool ACluckTheChicken::Skill2YourThing()
{
	if (Super::Skill2YourThing()) {
		ASpecialEggParent * ChossenEgg;
		if (PickClosestEgg()->GetName() == EggF->GetName()) {
			ChossenEgg = GetWorld()->SpawnActor<ASpecialEggParent>(EggFSubClass, FTransform(FRotator(0, 0, 0), GetActorLocation() + GetActorForwardVector() * 150, FVector(1)));
			ChossenEgg->GetActorToIgnre(this);
			ChossenEgg->Thorw(EggSpeed, GetActorForwardVector());
		}
		else if (PickClosestEgg()->GetName() == EggL->GetName()) {
			ChossenEgg = GetWorld()->SpawnActor<ASpecialEggParent>(EggLSubClass, FTransform(FRotator(0, 0, 0), GetActorLocation() + GetActorForwardVector() * 150, FVector(1)));
			ChossenEgg->GetActorToIgnre(this);
			ChossenEgg->Thorw(EggSpeed, GetActorForwardVector());
		}
		else if (PickClosestEgg()->GetName() == EggI->GetName()) {
			ChossenEgg = GetWorld()->SpawnActor<ASpecialEggParent>(EggISubClass, FTransform(FRotator(0, 0, 0), GetActorLocation() + GetActorForwardVector() * 150, FVector(1)));
			ChossenEgg->GetActorToIgnre(this);
			ChossenEgg->Thorw(EggSpeed, GetActorForwardVector());
		}
		return true;
	}
	return true;
}
bool ACluckTheChicken::Skill1YourThing()
{
	if (Super::Skill1YourThing()) {
		ABeamParent *  ChossenBeam;
		if (PickClosestEgg()->GetName() == EggF->GetName()) {
			ChossenBeam = GetWorld()->SpawnActor<ABeamParent>(BeamFSubClass, FTransform(FRotator(0, 0, 0), GetActorLocation() + EggF->RelativeLocation, FVector(1)));
			ChossenBeam->SetActorRotation(GetActorForwardVector().Rotation());
			ChossenBeam->GetEggL(EggF->GetComponentLocation());
			ChossenBeam->SetActorToIgnire(this);
		}
		else if (PickClosestEgg()->GetName() == EggL->GetName()) {
			ChossenBeam = GetWorld()->SpawnActor<ABeamParent>(BeamLSubClass, FTransform(FRotator(0, 0, 0), GetActorLocation() + EggL->RelativeLocation, FVector(1)));
			ChossenBeam->SetActorRotation(GetActorForwardVector().Rotation());
			ChossenBeam->GetEggL(EggL->GetComponentLocation());
			ChossenBeam->SetActorToIgnire(this);

		}
		else if (PickClosestEgg()->GetName() == EggI->GetName()) {
			ChossenBeam = GetWorld()->SpawnActor<ABeamParent>(BeamISubClass, FTransform(FRotator(0, 0, 0), GetActorLocation() + EggI->RelativeLocation, FVector(1)));
			ChossenBeam->SetActorRotation(GetActorForwardVector().Rotation());
			ChossenBeam->GetEggL(EggI->GetComponentLocation());
			ChossenBeam->SetActorToIgnire(this);
		}
		return true;
	}
	return true;
}
bool ACluckTheChicken::RangedAttackdDoYourThing()
{
	if (Super::RangedAttackdDoYourThing()) {
		AC4Parent * C4 = GetWorld()->SpawnActor<AC4Parent>(C4PSubClass, FTransform(FRotator(GetActorForwardVector().Rotation()), GetActorLocation() + GetActorForwardVector() * 150, FVector(1)));
		C4->SetActorToIgnre(this);
		C4->Thorw(C4Speed, FVector::ForwardVector);
		if (IsThere2C4()) {
	
		}
		return true;
	}
	return true;
}
void ACluckTheChicken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpringArmF->AddLocalRotation(FQuat(FRotator(0, Multiplier *DeltaTime, 0)));
	SpringArmL->AddLocalRotation(FQuat(FRotator(0, Multiplier *DeltaTime, 0)));
	SpringArmI->AddLocalRotation(FQuat(FRotator(0, Multiplier *DeltaTime, 0)));
	
}
UStaticMeshComponent * ACluckTheChicken::PickClosestEgg()
{
	TArray<float> Numbers;
	float ChossenNum = BIG_NUMBER;
	float i = -1;
	Numbers.Add(SpringArmF->RelativeRotation.Yaw);
	Numbers.Add(SpringArmL->RelativeRotation.Yaw);
	Numbers.Add(SpringArmI->RelativeRotation.Yaw);
	for (float NUm : Numbers)
	{
		if (ChossenNum > (180 - FMath::Abs(NUm)))
		{
			ChossenNum = (180 - FMath::Abs(NUm));
			i++;
		}
	}
	return Eggs[i];
		

		
			
	

}

bool ACluckTheChicken::IsThere2C4()
{
	C4Num++;
	if (C4Num == 2)
	{
		C4Num = 0;
		return true;
	}
	return false;
}

void ACluckTheChicken::OnActorHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{

}