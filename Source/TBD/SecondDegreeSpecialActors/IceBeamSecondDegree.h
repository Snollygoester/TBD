// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpecialActors/BeamParent.h"
#include "IceBeamSecondDegree.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API AIceBeamSecondDegree : public ABeamParent
{
	GENERATED_BODY()
public:	
void OverlappDoYourThing(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
private:
UPROPERTY(EditAnywhere)
	float MaxSpeedPracnet = 0.4;
UPROPERTY(EditAnywhere)
float TimeUntilSpeedReset = 2;
};
