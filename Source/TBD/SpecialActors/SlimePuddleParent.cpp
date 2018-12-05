// Fill out your copyright notice in the Description page of Project Settings.

#include "SlimePuddleParent.h"
#include "Components/StaticMeshComponent.h"
#include "Parents/CharacterParent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TBDGameModeBase.h" 
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
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
			if (Character != nullptr)
			{
				if (Character->Tags[0] != Tags[0])
				{

					if (IsOverlappingActor(Character))
					{
						Cast<UCharacterMovementComponent>(Character->GetMovementComponent())->MaxWalkSpeed = (Character->DefaultMovementSpeed / MaxDist)  * FMath::Clamp(Character->GetDistanceTo(this) , 40.f, 120.f);
					}
					else
					{
						Cast<UCharacterMovementComponent>(Character->GetMovementComponent())->MaxWalkSpeed = Character->DefaultMovementSpeed;
					}
				}
			}
		}
	}

}

