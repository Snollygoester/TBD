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
	 void Skill2YourThing() override;
	UPROPERTY(EditAnywhere)
		TSubclassOf< class AShiledParent > ShiledParentTsubClass;
	bool bIsShiledActive;
	UPROPERTY()
		class AShiledParent * Shiled;
	UPROPERTY()
	TArray< class UStaticMeshComponent * > Eggs;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * EggF;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * EggL;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * EggI;
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArmF;
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArmL;
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArmI;

	UPROPERTY(EditAnywhere, Category = Movement)
		float Multiplier = 100;
	UPROPERTY(EditAnywhere, Category = Eggs)
		float EggSpeed = 1000;
	UPROPERTY(EditAnywhere, Category = Eggs)
		TSubclassOf<class AProjectileParent> EggFSubClass;
	UPROPERTY(EditAnywhere, Category = Eggs)
		TSubclassOf<class AProjectileParent> EggLSubClass;
	UPROPERTY(EditAnywhere, Category = Eggs)
		TSubclassOf<class AProjectileParent> EggISubClass;
	UStaticMeshComponent *  PickClosestEgg();
};
