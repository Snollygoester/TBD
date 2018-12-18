// Fill out your copyright notice in the Description page of Project Settings.

#include "SlimePuddleParent.h"
#include "Components/StaticMeshComponent.h"
#include "Parents/CharacterParent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TBDGameModeBase.h" 
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
// waiting for dount 
// Sets default values
ASlimePuddleParent::ASlimePuddleParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ASlimePuddleParent::BeginPlay()
{
	Super::BeginPlay();
	for (APawn * Pawn : Cast<ATBDGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->Players)
	{
		ACharacterParent * Character =	Cast<ACharacterParent>(Pawn);
		if (Character != nullptr)
		{
			Characters.Add(Character);
		}
	}
	
}



// Called every frame
void ASlimePuddleParent::Tick(float DeltaTime)
{


	Super::Tick(DeltaTime);

	if (Characters.Num() > 0)
	{
		for (ACharacterParent * Character : Characters)
		{
			if (ThisActorToIgnire != nullptr  && ThisActorToIgnire != Character) {
				if (IsOverlappingActor(Character))
				{
					if (Character->GetDistanceTo(this) <= 100 && bIsIce)
					{
						Character->bIsIced = true;
					}
					else
					{
						Character->CharacterMovementComponent->MaxWalkSpeed = (Character->DefaultMovementSpeed / MaxDist)  * FMath::Clamp(Character->GetDistanceTo(this), Min, Max);
					}

				}
			}
		}
	}
}
void ASlimePuddleParent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	Super::EndPlay(EndPlayReason);
	if (Characters.Num() > 0)
	{
		for (ACharacterParent * Character : Characters)
		{

			if (Character != nullptr)
			{
				if (Character->bIsIced)
				{
					Character->bIsIced = false;
				}
			Character->CharacterMovementComponent->MaxWalkSpeed = Character->DefaultMovementSpeed;
			}
		}
	}
	
}

