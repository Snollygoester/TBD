// Fill out your copyright notice in the Description page of Project Settings.

#include "CluckTheChicken.h"
#include "Engine/World.h"
#include "SpecialActors/ShiledParent.h"

void ACluckTheChicken::BlockDoYourThing() {
	if (bIsShiledActive)
	{
		bIsShiledActive = false;
		Shiled->Dactive();
	}
	if (!bIsShiledActive)
	{
		bIsShiledActive = true;
		Shiled->Active();
	}
}

void ACluckTheChicken::BeginPlay()
{
	Super::BeginPlay();
	 Shiled = GetWorld()->SpawnActor<AShiledParent>(ShiledParentTsubClass, FTransform(FRotator(0, 0, 0), GetActorLocation() + (GetActorForwardVector() * 100), FVector(1)));
	Shiled->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	Shiled->Dactive();
}
