// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parents/ProjectileParent.h"
#include "C4Parent.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API AC4Parent : public AProjectileParent
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AC4Parent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetActorToIgnre(class AActor * ToIgner);
	UPROPERTY()
		class AActor * ThisActorToIgnre;
	UPROPERTY()
		class AActor * HitActor;
	UFUNCTION()
	void Exploded(class AActor * Other);
	UFUNCTION()
	void ExplodedAndStun(class AActor * Other);
private:
	bool bHitShiled = false;
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent * ParticleSystemComponent;
	UPROPERTY(EditAnywhere)
		float TimeEntilExplosion = 2;
	UPROPERTY(EditAnywhere)
		float BaseDamage = 4;
	UPROPERTY(EditAnywhere)
		float MaxDamagep = 1.2;
	UPROPERTY(EditAnywhere)
		float ExplosionDamage = 5;
	UPROPERTY(EditAnywhere)
		float ExplosionRadius = 200;
	void TimerEndDestroy();
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UDamageTypeParent > C4DamageTyep;
	bool bCanAttach = true;
	
};
