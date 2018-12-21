// Fill out your copyright notice in the Description page of Project Settings.

#include "SlimePuddleParent.h"
#include "Components/StaticMeshComponent.h"
#include "Parents/CharacterParent.h"
#include "GameFramework/CharacterMovementComponent.h"
// waiting for dount 
// Sets default values
ASlimePuddleParent::ASlimePuddleParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Slower = CreateDefaultSubobject< UStaticMeshComponent>(FName("Slower"));
	Slower1 = CreateDefaultSubobject< UStaticMeshComponent>(FName("Slower1"));
	Slower2 = CreateDefaultSubobject< UStaticMeshComponent>(FName("Slower2"));
	Slower3 = CreateDefaultSubobject< UStaticMeshComponent>(FName("Slower3"));
	Slower4 = CreateDefaultSubobject< UStaticMeshComponent>(FName("Slower4"));
	Slower5 = CreateDefaultSubobject< UStaticMeshComponent>(FName("Slower5"));
	Slower6 = CreateDefaultSubobject< UStaticMeshComponent>(FName("Slower6"));
	Slower7 = CreateDefaultSubobject< UStaticMeshComponent>(FName("Slower7"));
	Slower8 = CreateDefaultSubobject< UStaticMeshComponent>(FName("Slower8"));
	Slower9 = CreateDefaultSubobject< UStaticMeshComponent>(FName("Slower9"));
	Slower->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	Slower1->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	Slower2->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	Slower3->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	Slower4->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	Slower5->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	Slower6->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	Slower7->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	Slower8->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	Slower9->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	
}

// Called when the game starts or when spawned
void ASlimePuddleParent::BeginPlay()
{
	Super::BeginPlay();
	Slowers.Add(Slower);
	Slowers.Add(Slower1);
	Slowers.Add(Slower2);
	Slowers.Add(Slower3);
	Slowers.Add(Slower4);
	Slowers.Add(Slower5);
	Slowers.Add(Slower6);
	Slowers.Add(Slower7);
	Slowers.Add(Slower8);
	Slowers.Add(Slower9);
	for (UStaticMeshComponent * Slowe : Slowers)
	{
		Slowe->OnComponentBeginOverlap.AddDynamic(this, &ASlimePuddleParent::OnOverlapBegin);
		Slowe->OnComponentEndOverlap.AddDynamic(this, &ASlimePuddleParent::OnOverlapEnd);
	}
}



// Called every frame
void ASlimePuddleParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlimePuddleParent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	Super::EndPlay(EndPlayReason);
	
}

void ASlimePuddleParent::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != ThisActorToIgnire)
	{
		ACharacterParent * Character = Cast< ACharacterParent>(OtherActor);
		if (Character != nullptr && bIsIce && Slowers.Find(Cast<UStaticMeshComponent>(OverlappedComp)) >= 7) {
			Character->GetCharacterMovement()->DisableMovement();
			return;
		}
		if (Character != nullptr)
		{
			Character->ChangeSpeed( 1 / (Slowers.Find(Cast<UStaticMeshComponent>(OverlappedComp)) + 1.25));
		}
		
	}
}

void ASlimePuddleParent::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != ThisActorToIgnire)
	{
		ACharacterParent * Character = Cast< ACharacterParent>(OtherActor);
		if (Character != nullptr && bIsIce && Slowers.Find(Cast<UStaticMeshComponent>(OverlappedComp)) >= 7) {
			Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			return;
		}
		if (Character != nullptr)
		{
			Character->ChangeSpeed((Slowers.Find(Cast<UStaticMeshComponent>(OverlappedComp)) + 1.25));

		}
		
	}
}


