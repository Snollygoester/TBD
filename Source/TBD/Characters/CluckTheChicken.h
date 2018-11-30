// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parents/CharacterParent.h"
#include "CluckTheChicken.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API ACluckTheChicken : public ACharacterParent
{
	GENERATED_BODY()
	
private:
	void BlockDoYourThing() override;
	void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		TSubclassOf< class AShiledParent > ShiledParentTsubClass;
	bool bIsShiledActive = false;
	UPROPERTY()
		class AShiledParent * Shiled;
};
