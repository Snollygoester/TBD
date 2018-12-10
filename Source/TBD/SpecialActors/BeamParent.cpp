// Fill out your copyright notice in the Description page of Project Settings.

#include "BeamParent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TimerManager.h"
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
		FHitResult Hit;
		FVector Startl = EggLBeam;
		FVector Endl = GetActorLocation() + GetActorForwardVector() * LineTrachRange;
		if (GetWorld()->LineTraceSingleByObjectType(Hit, Startl, Endl, FCollisionObjectQueryParams::AllStaticObjects)) {
			BeamCapsuleComponent->SetCapsuleHalfHeight(((FVector::Distance(Hit.Location, Startl) / 2)));
			InnerBeamCapsuleComponent->SetCapsuleHalfHeight(((FVector::Distance(Hit.Location, Startl) / 2)));
			BeamSpringArm->TargetArmLength = FVector::Distance( Hit.Location , Startl )  / -2;
			
		}
		else
		{
			BeamCapsuleComponent->SetCapsuleHalfHeight(LineTrachRange /2);
			InnerBeamCapsuleComponent->SetCapsuleHalfHeight(LineTrachRange / 2);
			BeamSpringArm->TargetArmLength = LineTrachRange / -2;
		}
	}
}

void ABeamParent::GetEggL(FVector EggL)
{
	EggLBeam = EggL;
}

void ABeamParent::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OverlapingActor = OtherActor;
	UGameplayStatics::ApplyDamage(OtherActor, BaseDamageInOuterPart, GetInstigatorController(), this, UDamageType::StaticClass());
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABeamParent::AplayDOU, TimeToUpdateDamageInOuterPart);
	UE_LOG(LogTemp, Warning, TEXT("hi"));
}

void ABeamParent::AplayDOU()
{
	if (IsOverlappingActor(OverlapingActor))
	{
		UGameplayStatics::ApplyDamage(OverlapingActor, BaseDamageInOuterPart, GetInstigatorController(), this, UDamageType::StaticClass());
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABeamParent::AplayDOU, TimeToUpdateDamageInOuterPart);
	}
}

