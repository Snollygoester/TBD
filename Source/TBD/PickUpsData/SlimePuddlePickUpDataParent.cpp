// Fill out your copyright notice in the Description page of Project Settings.

#include "SlimePuddlePickUpDataParent.h"
#include "Parents/CharacterParent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widgets/PickUpItemWidget.h"
#include "Engine/World.h"
#include "SpecialActors/SlimePuddleParent.h"
#include "Public/TimerManager.h"

void USlimePuddlePickUpDataParent::PickUpDoYourThing()
{
	if (!bIwasCalled)
	{
		
		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + (GetOwner()->GetActorUpVector() * -10000), ECollisionChannel::ECC_Visibility)) {
			bIwasCalled = true;
			SlimePuddle = GetWorld()->SpawnActor<ASlimePuddleParent>(SlimePuddleParentSubClass, FTransform(FRotator(0, 0, 0), Hit.Location));
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USlimePuddlePickUpDataParent::DestroyComp, AbilityTime);
			FTimerHandle TimerHandle1;
			RTime = AbilityTime;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &USlimePuddlePickUpDataParent::UpdetaTimer, UpdateTime, true);
			RScale = SlimePuddle->GetActorScale3D();
			StartScale = SlimePuddle->GetActorScale3D();
			SlimePuddle->Tags.Add(FName(*Owner->PlayerUniqueTag));
		}
	}
}

void USlimePuddlePickUpDataParent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacterParent>(GetOwner());
	PickUpItemWidget = Owner->PickUpWidget;
	PickUpItemWidget->SetProgressBarImage(Image);
	PickUpItemWidget->SetProgressBarPercent(1);
}

void USlimePuddlePickUpDataParent::UpdetaTimer()
{
	RScale = RScale - StartScale / AbilityTime * UpdateTime;
	SlimePuddle->SetActorScale3D(RScale);
	RTime = RTime - UpdateTime;
	PickUpItemWidget->SetProgressBarPercent(RTime / AbilityTime);
}
void USlimePuddlePickUpDataParent::DestroyComp()
{
	PickUpItemWidget->SetProgressBarPercent(0);
	SlimePuddle->Destroy();
	DestroyComponent();
}
