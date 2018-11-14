// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraParent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Public/TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

#include "TBDGameModeBase.h"
// Sets default values
ACameraParent::ACameraParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SetRootComponent(SpringArm);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ACameraParent::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACameraParent::SetUp, 0.1);
}

// Called every frame
void ACameraParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraParent::SetUp()
{
	PlayersRef = Cast<ATBDGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->Players;
	TArray<AActor*> PlayerControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), PlayerControllers);
	for (AActor * PlayerController : PlayerControllers)
	{
		Cast<APlayerController>(PlayerController)->SetViewTargetWithBlend(this);
	}
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACameraParent::UpdateCameraDist, 0.01, true);
}

void ACameraParent::UpdateCameraDist()
{
	switch (PlayersRef.Num())
	{
	case 2:
		SpringArm->TargetArmLength = PlayersRef[0]->GetDistanceTo(PlayersRef[1]);
		break;
	case 3: {
		TArray<float> Distances;
		float FarestDistance;
		int FarestDistanceIndex;
		Distances.Add(PlayersRef[0]->GetDistanceTo(PlayersRef[1]));
		Distances.Add(PlayersRef[0]->GetDistanceTo(PlayersRef[2]));
		Distances.Add(PlayersRef[1]->GetDistanceTo(PlayersRef[2]));
		UKismetMathLibrary::MaxOfFloatArray(Distances, FarestDistanceIndex, FarestDistance);
		SpringArm->TargetArmLength = FarestDistance;
	}
		break;
	case 4: {
		TArray<float> DistancesP4;
		float FarestDistanceP4;
		int FarestDistanceIndexP4;
		DistancesP4.Add(PlayersRef[0]->GetDistanceTo(PlayersRef[1]));
		DistancesP4.Add(PlayersRef[0]->GetDistanceTo(PlayersRef[2]));
		DistancesP4.Add(PlayersRef[0]->GetDistanceTo(PlayersRef[3]));
		DistancesP4.Add(PlayersRef[1]->GetDistanceTo(PlayersRef[2]));
		DistancesP4.Add(PlayersRef[1]->GetDistanceTo(PlayersRef[3]));
		DistancesP4.Add(PlayersRef[2]->GetDistanceTo(PlayersRef[3]));
		UKismetMathLibrary::MaxOfFloatArray(DistancesP4, FarestDistanceIndexP4, FarestDistanceP4);
		SpringArm->TargetArmLength = FarestDistanceP4;
	}
		break;

	}
}

