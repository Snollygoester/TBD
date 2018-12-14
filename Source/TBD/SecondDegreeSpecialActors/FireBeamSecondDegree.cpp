// Fill out your copyright notice in the Description page of Project Settings.

#include "FireBeamSecondDegree.h"
#include "Kismet/GameplayStatics.h"
#include "Parents/DamageTypeParent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Components/CapsuleComponent.h"
FTimerDelegate BeamFTimerDel;
void AFireBeamSecondDegree::OverlappDoYourThing(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!bIsOnFire && Cast<APawn>(OtherActor)) {
			FireDamageType.GetDefaultObject()->ActorToIgnre = ThisActorToIgnire;
			UGameplayStatics::ApplyDamage(OtherActor, SMALL_NUMBER, GetInstigatorController(), this, FireDamageType);
			BeamFTimerDel.BindUFunction(this, FName("UpdateFire"), OtherActor);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, BeamFTimerDel,  FireDamageType.GetDefaultObject()->DamageUpdateTime * FireDamageType.GetDefaultObject()->DamageUpdateNumber, false);
			bIsOnFire = true;
		}
}



void AFireBeamSecondDegree::UpdateFire(AActor * OtherActor)
{
	if (InnerBeamCapsuleComponent->IsOverlappingActor(OtherActor))
	{
		bIsOnFire = true;
		UGameplayStatics::ApplyDamage(OtherActor, SMALL_NUMBER, GetInstigatorController(), this, FireDamageType);
		BeamFTimerDel.BindUFunction(this, FName("UpdateFire"), OtherActor);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, BeamFTimerDel, FireDamageType.GetDefaultObject()->DamageUpdateTime * FireDamageType.GetDefaultObject()->DamageUpdateNumber, false);
		return;
	}
	bIsOnFire = false;
}
