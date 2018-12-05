// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parents/ProjectileParent.h"
#include "SpecialEggParent.generated.h"

UCLASS()
class TBD_API ASpecialEggParent : public AProjectileParent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpecialEggParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) override;
	UPROPERTY(EditAnywhere)
	float HitDamage = 3;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	
};
