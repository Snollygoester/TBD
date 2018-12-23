// Fill out your copyright notice in the Description page of Project Settings.

#include "WallClimbAB.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
// Sets default values for this component's properties
UWallClimbAB::UWallClimbAB()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	 
	// ...
}


// Called when the game starts
void UWallClimbAB::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());
	// ...
	
}


// Called every frame
void UWallClimbAB::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * ClimbRange, ECollisionChannel::ECC_Visibility)) {
		if (Hit.Actor != nullptr) {
			if (OwnerController == nullptr)
			{
				OwnerController = Cast<APlayerController>(Owner->GetController());
			}
			if (OwnerController != nullptr)
			{
				if (Hit.Actor->ActorHasTag("Wall")) {
					ClimbTime = OwnerController->GetInputKeyTimeDown(FKey("Spacebar"));
					if (ClimbTime >= TimeUtileYpuCanStartClimbing)
					{
						if (ClimbTime <= TimeYouCanClimb) {
							Owner->LaunchCharacter(FVector(0, 0, 350), false, true);
						}
					}
				}
			}
		}
	}
	else
	{
		ClimbTime = 0;
	}
		
	
}

