// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpecialActors/BeamParent.h"
#include "FireBeamSecondDegree.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API AFireBeamSecondDegree : public ABeamParent
{
	GENERATED_BODY()
	
public:
 void OverlappDoYourThing(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
private:
UPROPERTY(EditAnywhere)
TSubclassOf<class UDamageTypeParent > FireDamageType;
UPROPERTY()
AActor * Actor;
void UpdateFire();
bool bIsOnFire = false;

	
};
