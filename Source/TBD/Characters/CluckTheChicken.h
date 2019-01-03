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
	bool Skill2YourThing() override;
	 bool Skill1YourThing() override;
	 bool RangedAttackdDoYourThing() override;
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
		TSubclassOf<class ASpecialEggParent> EggFSubClass;
	UPROPERTY(EditAnywhere, Category = Eggs)
		TSubclassOf<class ASpecialEggParent> EggLSubClass;
	UPROPERTY(EditAnywhere, Category = Eggs)
		TSubclassOf<class ASpecialEggParent> EggISubClass;
	UStaticMeshComponent *  PickClosestEgg();
	UPROPERTY(EditAnywhere, Category = Beams)
		TSubclassOf<class ABeamParent> BeamFSubClass;
	UPROPERTY(EditAnywhere, Category = Beams)
		TSubclassOf<class ABeamParent> BeamISubClass;
	UPROPERTY(EditAnywhere, Category = Beams)
		TSubclassOf<class ABeamParent> BeamLSubClass;
	UPROPERTY(EditAnywhere, Category = Beams)
		TSubclassOf<class AC4Parent> C4PSubClass;
	UPROPERTY(EditAnywhere, Category = C4)
		float C4Speed = 500;
	bool IsThere2C4();
	int8 C4Num = 0;
	UPROPERTY()
	class AC4Parent * OldC4;
	UPROPERTY()
		class AC4Parent * RealOldC4;
	UFUNCTION()
	void OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	float StunTime = 1.5;
};
