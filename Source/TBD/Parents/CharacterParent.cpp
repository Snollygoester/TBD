// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterParent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Abilities/CliffHangAB.h"
#include "PickUpParent.h"
#include "PickUpDataParent.h"
#include "Widgets/PickUpItemWidget.h"
#include "Widgets/HealthWidget.h"
#include "Public/TimerManager.h"
#include "SpecialActors/SpawnPointParent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"
#include "DamageTypeParent.h"
#include "Particles/ParticleSystemComponent.h"
#include "RangedWeapons/C4Parent.h"
#include "TBDGameModeBase.h"

FTimerDelegate TimerDel;
FTimerDelegate IceBeamDel;
// Sets default values
ACharacterParent::ACharacterParent()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComponent"));
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		// set our turn rates for input
	ArrowComponent1 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowComponent1"));
	WidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ArrowComponent1->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	FireParticles = CreateDefaultSubobject< UParticleSystemComponent>(FName("FireParticles"));
	FireParticles->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FireParticles->bAutoActivate = false;

}

// Called when the game starts or when spawned
void ACharacterParent::BeginPlay()
{
	Super::BeginPlay();
	Gamemode = Cast< ATBDGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACharacterParent::OnOverlapBegin);
	OnActorHit.AddDynamic(this, &ACharacterParent::OnHitActor);
	PickUpWidget = CreateWidget<UPickUpItemWidget>(GetWorld(), UserWidget);
	PickUpWidget->AddToViewport();
	CurrentHealth = Health;
	NonSpawnMaterials = GetMesh()->GetMaterials();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACharacterParent::StopImmortality, ImmortalityTime);
	CliffHangABCpp = FindComponentByClass<UCliffHangAB>();
}



float ACharacterParent::TakeDamage(float DamageAmount,  FDamageEvent const& DamageEvent,  AController* EventInstigator, AActor* DamageCauser)
{
		Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		if (bIsBlocking)
		{
			bIsBlocking = false;
			UDamageTypeParent * TypeDamage = Cast<UDamageTypeParent>(DamageEvent.DamageTypeClass.GetDefaultObject());
			CurrentHealth = CurrentHealth - CalculateBlock(TypeDamage, DamageAmount);
			return 0.f;
		}
		if (!bIsImmortal)
		{
			 UDamageTypeParent * TypeDamage = Cast<UDamageTypeParent>(DamageEvent.DamageTypeClass.GetDefaultObject());
			if (TypeDamage == nullptr)
			{
				CurrentHealth = CurrentHealth - DamageAmount;
			}
			else
			{
				if (TypeDamage->ActorToIgnre == this) {
					
					return 0.f;
					
				}
				if (DamageAmount > KINDA_SMALL_NUMBER)
				{
					CurrentHealth = CurrentHealth - DamageAmount;
				}
				
				if (TypeDamage->bIsDamageOverTime)
				{
					TimerDel.BindUFunction(this, FName("TakeDOT"), TypeDamage, TypeDamage->DamageUpdateNumber);
					FTimerHandle TimerHandle;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, TypeDamage->DamageUpdateTime, false);
					if (TypeDamage->DamageTyep == EDamageTyeps::Fire)
					{
						FireParticles->Activate();
						
					}
				}
			}
			HealthWidget->SetHealthBarPercent(CurrentHealth / Health);
			if (CurrentHealth <= 0)
			{
				Death();
			}
		
		}
		return 0.f;
}

// Called every frame
void ACharacterParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterParent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
		//PlayerInputComponent->BindAction("PickUp", IE_Released, this, &ACharacterParent::PickUpObj);
		PlayerInputComponent->BindAction("UsePickUp", IE_Pressed, this, &ACharacterParent::UsePickUp);
	
		PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &ACharacterParent::RangedAttackdDoYourThingInput);
		PlayerInputComponent->BindAction("Cliff", IE_Pressed, this, &ACharacterParent::GrabWall);
		PlayerInputComponent->BindAction("Cliff", IE_Released, this, &ACharacterParent::letGoOffWall);
		PlayerInputComponent->BindAction("Block", IE_Pressed, this, &ACharacterParent::BlockDoYourThingInput);
		PlayerInputComponent->BindAction("Skill2", IE_Pressed, this, &ACharacterParent::Skill2YourThingInput);
		PlayerInputComponent->BindAction("Skill1", IE_Pressed, this, &ACharacterParent::Skill1YourThingInput);
		PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterParent::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterParent::MoveRight);

		// We have 2 versions of the rotation bindings to handle different kinds of devices differently
		// "turn" handles devices that provide an absolute delta, such as a mouse.
		// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("TurnRate", this, &ACharacterParent::TurnAtRate);
		PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("LookUpRate", this, &ACharacterParent::LookUpAtRate);
	}


void ACharacterParent::SetHealthWidget(UHealthWidget * HealthWidgetToSet)
{
	HealthWidget = HealthWidgetToSet;
	HealthWidget->SetHealthBarPercent(1);
}

void ACharacterParent::StopImmortality()
{
	bIsImmortal = false;
	int i = 0;
	for (UMaterialInterface* m : NonSpawnMaterials )
	{
		GetMesh()->SetMaterial(i, m);
		i++;
	}
	GetMesh()->CustomDepthStencilValue = FCString::Atoi(*PlayerUniqueTag);
	GetMesh()->MarkRenderStateDirty();
}

void ACharacterParent::MoveForward(float Value)
{
	if (BisGameStarted && !bIsDead) {
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void ACharacterParent::MoveRight(float Value)
{
	if (BisGameStarted && !bIsDead) {
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}
void ACharacterParent::TurnAtRate(float Rate)
{
	if (BisGameStarted && !bIsDead) {
		// calculate delta for this frame from the rate information
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void ACharacterParent::LookUpAtRate(float Rate)
{
	if (BisGameStarted && !bIsDead) {
		// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void ACharacterParent::Death()
{
	SetActorScale3D(FVector(1, 1, 0.1));
	FTimerHandle TimerHandle;
	bIsDead = true;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACharacterParent::FullDeath, RespawnTime);
}

void ACharacterParent::FullDeath()
{
	TArray < AActor *> AActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPointParent::StaticClass(), AActors);
	if (AActors[0] != nullptr)
	{
		AController *	Controller = GetController();
		UnPossessed();
		ASpawnPointParent * SpawnPoint = Cast < ASpawnPointParent > (AActors[0]);
		ACharacterParent * CharacterParent = 	GetWorld()->SpawnActor<ACharacterParent>(CharacterParentSub, FTransform(FRotator(0, 0, 0), SpawnPoint->FindPointToSpawn()));
		Controller->Possess(CharacterParent);
		Gamemode->Players.Remove(this);
		Gamemode->Players.Add(CharacterParent);
		CharacterParent->SetHealthWidget(HealthWidget);
		CharacterParent->ArrowComponent1->SetArrowColor(ArrowComponent1->ArrowColor);
		CharacterParent->WidgetComponent->GetUserWidgetObject()->SetColorAndOpacity(WidgetComponent->GetUserWidgetObject()->ColorAndOpacity);
		CharacterParent->BisGameStarted = true;
		HealthWidget->SetXimage();
		CharacterParent->bIsImmortal = true;
		CharacterParent->GetMesh()->SetMaterial(0, SpawnMaterial);
	}
	
	Destroy();
}


void ACharacterParent::Skill2YourThingInput()
{
	if (BisGameStarted && !bIsImmortal) {
		Skill2YourThing();
	}
}

void ACharacterParent::Skill1YourThingInput()
{
	if (BisGameStarted && !bIsImmortal) {
		Skill1YourThing();
	}
}

void ACharacterParent::BlockDoYourThingInput()
{
	BlockDoYourThing();
}

bool ACharacterParent::Skill2YourThing()
{
	if (bIsSilence)
	{
		return false;
	}
	return true;
}

bool ACharacterParent::Skill1YourThing()
{
	if (bIsSilence)
	{
		return false;
	}
	return true;
}
bool ACharacterParent::BlockDoYourThing()
{
	if (bIsBlocking)
	{
		bIsBlocking = false;
		return true;
	}
	return true;
}

bool ACharacterParent::RangedAttackdDoYourThing()
{
	return true;
}
float ACharacterParent::CalculateBlock(UDamageTypeParent * TypeDamage, float DamageAmount)
{
	return 0.0f;
}
void ACharacterParent::RangedAttackdDoYourThingInput()
{
	if (BisGameStarted  && !bIsImmortal) {
		RangedAttackdDoYourThing();
	}
}


void ACharacterParent::IceFromBeam(float Time, float P)
{
	ChangeSpeed(P);
	IceBeamDel.BindUFunction(this, FName("StopIce"), P);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, IceBeamDel, Time, false);
}
void ACharacterParent::SilenceFromBeam(float Time) {
	bIsSilence = true;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACharacterParent::StopSilence, Time);
}

void ACharacterParent::ChangeSpeed(float SpeedMultiplayerP)
{
	SpeedMultiplayer = SpeedMultiplayer * SpeedMultiplayerP;
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed * SpeedMultiplayer ;
}


void ACharacterParent::GrabWall()
{
	if (CliffHangABCpp != nullptr)
	{
		CliffHangABCpp->hang();
	}
}

void ACharacterParent::letGoOffWall()
{
	if (CliffHangABCpp != nullptr)
	{
		CliffHangABCpp->Release();
	}
}
void ACharacterParent::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	APickUpParent * PickUp = Cast<APickUpParent>(OtherActor);

		if (PickUp != nullptr && PickUpData == nullptr )
		{
			UClass * PickupClass = PickUp->PickUpData;
			PickUpData = NewObject<UPickUpDataParent>(this, PickupClass);
			PickUpData->RegisterComponent();
			PickUp->Destroy();
			
		}
		else if (PickUp != nullptr && PickUpData->IsPendingKill()) {
			UClass * PickupClass = PickUp->PickUpData;
			PickUpData = NewObject<UPickUpDataParent>(this, PickupClass);
			PickUpData->RegisterComponent();
			PickUp->Destroy();
		}
}
void ACharacterParent::OnHitActor(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT(" %s "), *OtherActor->GetName());
	AC4Parent * C4 = Cast<AC4Parent>(OtherActor);
	if (C4 != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" 1 "));
		OC4 = NC4;
		NC4 = C4;
		if (OC4 != nullptr && NC4 != nullptr)
		{
			TArray<AActor *>  AActors;
			GetAttachedActors(AActors);
			UE_LOG(LogTemp, Warning, TEXT(" yay "));
			int i;
			if (AActors.Num() != 0 && AActors.Find(OC4, i) && AActors.Find(NC4, i))
			{
				OC4->Exploded();
				NC4->ExplodedAndStun();
				DisableInput(Cast< APlayerController >(GetController()));
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACharacterParent::StopStunC4, C4StunTime);
				UE_LOG(LogTemp, Warning, TEXT(" 2 "));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT(" nop "));
			}

		}
	}
}

void ACharacterParent::UsePickUp()
{
	if (bIsSilence) {
		return;
	}
	if (BisGameStarted && !bIsDead) {
		if (PickUpData != nullptr) {
			PickUpData->PickUpDoYourThing();
		}
	}

}
void ACharacterParent::TakeDOT(UDamageTypeParent * TypeDamage, int CallNum)
{
	if (CallNum == 0)
	{
		if (TypeDamage->DamageTyep == EDamageTyeps::Fire)
		{
			FireParticles->Deactivate();
		}
		return;
	}
	UGameplayStatics::ApplyDamage(this, TypeDamage->DamageOverTimeDamage, GetInstigatorController(), this, NormalDamage);
	TimerDel.BindUFunction(this, FName("TakeDOT"), TypeDamage, (CallNum - 1));
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, TypeDamage->DamageUpdateTime, false);
}

void ACharacterParent::StopIce(float P)
{
	ChangeSpeed(1 / P);
}
void ACharacterParent::StopSilence() {
	bIsSilence = false;
}

void ACharacterParent::StopStunC4()
{
	EnableInput(Cast< APlayerController >(GetController()));
}


