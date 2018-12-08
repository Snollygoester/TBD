// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpecialActors/SpecialEggParent.h"
#include "SpecialEggLSecondDegree.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API ASpecialEggLSecondDegree : public ASpecialEggParent
{
	GENERATED_BODY()
	

	
private:
void OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) override;
UPROPERTY(EditAnywhere)
TSubclassOf<class AElectricPuddleSecondDegree > ElectricPuddleSecondDegreeSubClass;


};
