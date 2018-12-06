// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpecialActors/SpecialEggParent.h"
#include "SecondDegreeSpecialEggParentF.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API ASecondDegreeSpecialEggParentF : public ASpecialEggParent
{
	GENERATED_BODY()
	
private:
	void OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASecondDegreeFirePuddle > SecondDegreeFirePuddleSubClass;
};
