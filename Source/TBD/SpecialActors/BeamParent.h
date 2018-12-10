// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeamParent.generated.h"

UCLASS()
class TBD_API ABeamParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeamParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Lunch(float DT);
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent * BeamCapsuleComponent;
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent * InnerBeamCapsuleComponent;
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* BeamSpringArm;
	void GetEggL(FVector EggL);
	FVector EggLBeam;
private:
	UPROPERTY(EditAnywhere)
		float LineTrachRange = 10000;
bool	bCanLunch = true;
 UPROPERTY(EditAnywhere)
float BaseDamageInOuterPart = 2;
 UPROPERTY(EditAnywhere)
 float TimeToUpdateDamageInOuterPart = 0.5;
 UPROPERTY()
	 AActor * OverlapingActor;
UFUNCTION()
void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
void AplayDOU();
};
