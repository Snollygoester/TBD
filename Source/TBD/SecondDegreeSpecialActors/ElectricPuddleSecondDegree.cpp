// Fill out your copyright notice in the Description page of Project Settings.

#include "ElectricPuddleSecondDegree.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
void AElectricPuddleSecondDegree::OverlapDoYourThing(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != ThisActorToIgnire)
	{
		chart = Cast<ACharacter>(OtherActor);
		if (chart != nullptr)
		{
			 chartM =	Cast<UCharacterMovementComponent>(chart->GetMovementComponent());
			if (chartM != nullptr)
			{
				chartM->DisableMovement();
				chart->DisableInput(Cast< APlayerController >(chart->GetController()));
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AElectricPuddleSecondDegree::UpdateElectric, StunTime, true);
			}
		}
  
	}	
}

void AElectricPuddleSecondDegree::UpdateElectric()
{
	if (chart != nullptr && chartM != nullptr)
	{
		chartM->SetMovementMode(EMovementMode::MOVE_Walking);
		chart->EnableInput(Cast< APlayerController >(chart->GetController()));
	}
}


