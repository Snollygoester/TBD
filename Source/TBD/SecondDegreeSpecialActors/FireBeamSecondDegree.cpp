// Fill out your copyright notice in the Description page of Project Settings.

#include "FireBeamSecondDegree.h"
#include "Kismet/GameplayStatics.h"
#include "Parents/DamageTypeParent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Components/CapsuleComponent.h"

void AFireBeamSecondDegree::OverlappDoYourThing(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

		if (!bIsOnFire) {
			Actor = OtherActor;
			UE_LOG(LogTemp, Warning, TEXT("Hi"));
			FireDamageType.GetDefaultObject()->ActorToIgnre = ThisActorToIgnire;
			UGameplayStatics::ApplyDamage(OtherActor, SMALL_NUMBER, GetInstigatorController(), this, FireDamageType);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFireBeamSecondDegree::UpdateFire, FireDamageType.GetDefaultObject()->DamageUpdateTime * FireDamageType.GetDefaultObject()->DamageUpdateNumber, true);
			bIsOnFire = true;
		}
}



void AFireBeamSecondDegree::UpdateFire()
{
	if (InnerBeamCapsuleComponent->IsOverlappingActor(Actor))
	{
		bIsOnFire = true;
		UGameplayStatics::ApplyDamage(Actor, SMALL_NUMBER, GetInstigatorController(), this, FireDamageType);
		return;
	}
	bIsOnFire = false;
}
