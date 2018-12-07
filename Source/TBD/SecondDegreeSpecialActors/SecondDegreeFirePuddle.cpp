// Fill out your copyright notice in the Description page of Project Settings.

#include "SecondDegreeFirePuddle.h"
#include "Kismet/GameplayStatics.h"
#include "Parents/DamageTypeParent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Components/StaticMeshComponent.h"
void ASecondDegreeFirePuddle::OverlapDoYourThing(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!bIsOnFire) {
		Actor = OtherActor;
		FireDamageType.GetDefaultObject()->ActorToIgnre = ThisActorToIgnire;
		UGameplayStatics::ApplyDamage(OtherActor, SMALL_NUMBER, GetInstigatorController(), this, FireDamageType);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASecondDegreeFirePuddle::UpdateFire, FireDamageType.GetDefaultObject()->DamageUpdateTime * FireDamageType.GetDefaultObject()->DamageUpdateNumber, true);
		bIsOnFire = true;
	}
}

void ASecondDegreeFirePuddle::UpdateFire()
{
	if (Puddle->IsOverlappingActor(Actor))
	{
		bIsOnFire = true;
		UGameplayStatics::ApplyDamage(Actor, SMALL_NUMBER, GetInstigatorController(), this, FireDamageType);
		return;
	}
	bIsOnFire = false;
}

void ASecondDegreeFirePuddle::GetActorToIgnire(AActor * ActorToIgnire)
{
	ThisActorToIgnire = ActorToIgnire;
}
