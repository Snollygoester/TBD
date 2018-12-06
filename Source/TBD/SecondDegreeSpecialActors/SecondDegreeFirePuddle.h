// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpecialActors/PuddleParent.h"
#include "SecondDegreeFirePuddle.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API ASecondDegreeFirePuddle : public APuddleParent
{
	GENERATED_BODY()

private:
void OverlapDoYourThing(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
UPROPERTY(EditAnywhere)
TSubclassOf<class UDamageTypeParent > FireDamageType;
UPROPERTY()
AActor * Actor;
void UpdateFire();
bool bIsOnFire = false;
};
