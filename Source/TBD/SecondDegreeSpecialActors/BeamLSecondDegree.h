// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpecialActors/BeamParent.h"
#include "BeamLSecondDegree.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API ABeamLSecondDegree : public ABeamParent
{
	GENERATED_BODY()
public:
	void OverlappDoYourThing(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
private:
	UPROPERTY(EditAnywhere)
		float TimOfSilence = 2;
	
	
	
};
