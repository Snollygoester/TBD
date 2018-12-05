// Fill out your copyright notice in the Description page of Project Settings.

#include "SecondDegreeSpecialEggParentF.h"
#include "Kismet/GameplayStatics.h"
#include "Parents/DamageTypeParent.h"
void ASecondDegreeSpecialEggParentF::OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Super::OnHitDoYourThing(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
	UGameplayStatics::ApplyDamage(OtherActor, HitDamage, GetInstigatorController(), this, FireDamageType);
}


