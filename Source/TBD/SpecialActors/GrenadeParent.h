// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parents/ProjectileParent.h"
#include "GrenadeParent.generated.h"

UCLASS()
class TBD_API AGrenadeParent : public AProjectileParent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenadeParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bHitShiled = false;
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent * ParticleSystemComponent;
	void Exploded();
	UPROPERTY(EditAnywhere)
	float TimeEntilExplosion = 3;
	UPROPERTY(EditAnywhere)
		float HitDamage = 3;
	UPROPERTY(EditAnywhere)
		float MaxExplosionDamage = 10;
	UPROPERTY(EditAnywhere)
		float MinExplosionDamage = 5;
	UPROPERTY(EditAnywhere)
		float ExplosionRadius  = 200;
	void TimerEndDestroy();
	
};
