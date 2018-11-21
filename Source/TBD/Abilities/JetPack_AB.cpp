// Fill out your copyright notice in the Description page of Project Settings.

#include "JetPack_AB.h"
#include "Engine/World.h"
#include "Parents/CharacterParent.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Widgets/HealthWidget.h"
// Sets default values for this component's properties
UJetPack_AB::UJetPack_AB()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UJetPack_AB::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacterParent>(GetOwner());
	MovementComponent = Cast<UCharacterMovementComponent>(Owner->GetMovementComponent()); 
	Fuel = MaxFuel;
	// ...

}


// Called every frame
void UJetPack_AB::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	OwnerController = Cast<APlayerController>(Owner->GetController()); //TODO remove 
	UE_LOG(LogTemp, Warning, TEXT(" Fuel %f"), Fuel);
	if (OwnerController)
	{
		FHitResult Hit;
		FlyingTime = OwnerController->GetInputKeyTimeDown(FKey("Spacebar"));
		Owner->HealthWidget->SetFuelBarPercent(Fuel / MaxFuel);
		if (FlyingTime >= 0.25)
		{
			
			if (Fuel > 0 )
			{
				Fuel = Fuel - (FuelLostPerSec * DeltaTime) ;
				Owner->LaunchCharacter(FVector(0, 0, 14000 * DeltaTime), false, true);
				bCanRecharg = false;
				return;
			}
		}
		else if (FlyingTime == 0.f)
		{
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UJetPack_AB::StartRechargeing, ChargDelay);
			if (Fuel < MaxFuel && bCanRecharg)
			{
				Fuel = Fuel + (FuelAddtPerSec * DeltaTime);
			}
		
		}
		

	}
}

void UJetPack_AB::StartRechargeing()
{
	bCanRecharg = true;
}


