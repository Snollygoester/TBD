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

public:
	// Sets default values for this character's properties
	ACluckTheChicken();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void BlockDoYourThing() override;
	void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		TSubclassOf< class AShiledParent > ShiledParentTsubClass;
	bool bIsShiledActive = false;
	UPROPERTY()
		class AShiledParent * Shiled;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * EggF;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * EggL;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * EggI;
	UPROPERTY(EditAnywhere, Category = Movement)
		float AngleAxisF;
	UPROPERTY(EditAnywhere, Category = Movement)
		float AngleAxisL;
	UPROPERTY(EditAnywhere, Category = Movement)
		float AngleAxisI;

	UPROPERTY(EditAnywhere, Category = Movement)
		FVector Dimensions = FVector(150,0,0);

	UPROPERTY(EditAnywhere, Category = Movement)
		FVector AxisVector = FVector(0,0,1) ;

	UPROPERTY(EditAnywhere, Category = Movement)
		float MultiplierF = 50;
	UPROPERTY(EditAnywhere, Category = Movement)
		float MultiplierL = 300;
	UPROPERTY(EditAnywhere, Category = Movement)
		float MultiplierI = 500;
};
