// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterParent.generated.h"

UCLASS()
class TBD_API ACharacterParent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
	UPROPERTY(EditAnywhere)
		TSubclassOf< class UPickUpItemWidget > UserWidget;
	UPROPERTY(EditAnywhere)
		TSubclassOf< class ACharacterParent > CharacterParentSub;
	UPROPERTY(EditAnywhere)
		class UPickUpItemWidget * PickUpWidget;
	float DefaultMovementSpeed;
	FString PlayerUniqueTag;
	class UHealthWidget * HealthWidget;
	void SetHealthWidget(class UHealthWidget * HealthWidgetToSet);
	UPROPERTY(EditAnywhere)
		float Health = 100;
		float CurrentHealth;
		bool bIsDead = false;
		UPROPERTY()
			class ATBDGameModeBase * Gamemode;
		bool BisGameStarted = false;
		bool bIsImmortal = false;
		UPROPERTY(EditAnywhere)
			float ImmortalityTime =2;
		void StopImmortality();
		UPROPERTY(VisibleAnywhere)
			class UWidgetComponent * WidgetComponent;
		UPROPERTY(VisibleAnywhere)
			class UArrowComponent * ArrowComponent1;
	protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);
	void GrabWall();
	void letGoOffWall();
	/** Called for side to side input */
	void MoveRight(float Value);
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void UsePickUp();
	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	void Death();

	void FullDeath();
	virtual void BlockDoYourThing();
	virtual void Skill2YourThing();
private:
	class	UCliffHangAB * CliffHangABCpp;
	class UPickUpDataParent * PickUpData;
	void ThrowGrenade();
	UPROPERTY(EditAnywhere)
		TSubclassOf< class AGrenadeParent > GrenadeParentTSubClass;
	UPROPERTY(EditAnywhere)
		float ThorwSpeed = 1500;
	UPROPERTY(EditAnywhere)
		float RespawnTime = 5;
	UPROPERTY(EditAnywhere)
	class UMaterialInterface * SpawnMaterial;
	UPROPERTY()
	TArray <class UMaterialInterface *> NonSpawnMaterials;
	UFUNCTION()
	void TakeDOT(class UDamageTypeParent * TypeDamage, int CallNum);
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent * FireParticles;
};
