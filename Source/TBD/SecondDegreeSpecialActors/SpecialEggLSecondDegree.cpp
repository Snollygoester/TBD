// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecialEggLSecondDegree.h"
#include "ElectricPuddleSecondDegree.h"
#include "SpecialActors/PuddleParent.h"
#include "Engine/World.h"
void ASpecialEggLSecondDegree::OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
	Super::OnHitDoYourThing(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
	GetWorld()->SpawnActor<APuddleParent>(ElectricPuddleSecondDegreeSubClass, FTransform(FRotator(0, 0, 0), GetActorLocation(), FVector(1)))->GetActorToIgnire(ThisActorToIgnre);
}


