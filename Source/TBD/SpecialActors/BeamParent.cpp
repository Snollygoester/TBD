// Fill out your copyright notice in the Description page of Project Settings.

#include "BeamParent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TimerManager.h"
#include "Parents/DamageTypeParent.h"
FTimerDelegate BeamTimerDel;
// Sets default values
ABeamParent::ABeamParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BeamSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BeamSpringArm"));
	SetRootComponent(BeamSpringArm);
	BeamCapsuleComponent = CreateDefaultSubobject< UCapsuleComponent>(FName("BeamCapsuleComponent "));
	InnerBeamCapsuleComponent = CreateDefaultSubobject< UCapsuleComponent>(FName("InnerBeamCapsuleComponent "));
	BeamCapsuleComponent->SetupAttachment(BeamSpringArm);
	InnerBeamCapsuleComponent->SetupAttachment(BeamSpringArm);
	
	
}

// Called when the game starts or when spawned
void ABeamParent::BeginPlay()
{
	Super::BeginPlay();
	InnerBeamCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABeamParent::OnInnerOverlapBegin);
     BeamCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABeamParent::OnOverlapBegin);
	
}

// Called every frame
void ABeamParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Lunch(DeltaTime);
}

void ABeamParent::Lunch(float DT)
{
	if (bCanLunch && !EggLBeam.IsZero()) {
		UDT += DT;
		if (UDT <= 1)
	{
				BeamCapsuleComponent->SetCapsuleHalfHeight(LineTrachRange * UDT / 2);
				InnerBeamCapsuleComponent->SetCapsuleHalfHeight(LineTrachRange * UDT / 2);
				BeamSpringArm->TargetArmLength = LineTrachRange * UDT / -2 ;
		}
	}
}

void ABeamParent::GetEggL(FVector EggL)
{
	EggLBeam = EggL;
}

void ABeamParent::OverlappDoYourThing(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

void ABeamParent::SetActorToIgnire(AActor * ActorToIgnire)
{
	ThisActorToIgnire = ActorToIgnire;
}

void ABeamParent::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!Cast<APawn>(OtherActor) && !Cast<ABeamParent>(OtherActor))
	{
		bCanLunch = false;
	}
	if (OtherActor != ThisActorToIgnire && Cast<APawn>(OtherActor) && ThisActorToIgnire != nullptr)
	{
		
		
		UGameplayStatics::ApplyDamage(OtherActor, BaseDamageInOuterPart, GetInstigatorController(), this, OuterBeamDamageType);
		BeamTimerDel.BindUFunction(this, FName("AplayDOU"), OtherActor);
		FTimerHandle BeamTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(BeamTimerHandle, BeamTimerDel, TimeToUpdateDamageInOuterPart, false);
	}
}

void ABeamParent::OnInnerOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (ThisActorToIgnire != nullptr)
	{
		OverlappDoYourThing(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void ABeamParent::AplayDOU(AActor * OtherActor)
{
		if (IsOverlappingActor(OtherActor))
		{

			UGameplayStatics::ApplyDamage(OtherActor, BaseDamageInOuterPart, GetInstigatorController(), this, OuterBeamDamageType);
			BeamTimerDel.BindUFunction(this, FName("AplayDOU"), OtherActor);
			FTimerHandle BeamTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(BeamTimerHandle, BeamTimerDel, TimeToUpdateDamageInOuterPart, false);
		}
}

