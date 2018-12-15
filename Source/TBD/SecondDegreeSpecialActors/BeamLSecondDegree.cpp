// Fill out your copyright notice in the Description page of Project Settings.

#include "BeamLSecondDegree.h"
#include "Parents/CharacterParent.h"
void ABeamLSecondDegree::OverlappDoYourThing(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != ThisActorToIgnire)
	{
		ACharacterParent * Character = Cast<ACharacterParent>(OtherActor);
		if (Character != nullptr)
		{
			Character->SilenceFromBeam(TimOfSilence);

		}
	}
}




