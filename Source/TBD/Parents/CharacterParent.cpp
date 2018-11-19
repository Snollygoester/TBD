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
#include "SpecialActors/GrenadeParent.h"
#include "Widgets/HealthWidget.h"
// Sets default values
ACharacterParent::ACharacterParent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
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


}

// Called when the game starts or when spawned
void ACharacterParent::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACharacterParent::OnOverlapBegin);
	PickUpWidget = CreateWidget<UPickUpItemWidget>(GetWorld(), UserWidget);
	PickUpWidget->AddToViewport();
	CurrentHealth = Health;
	UCharacterMovementComponent * CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	if (CharacterMovementComponent != nullptr)
	{
		DefaultMovementSpeed =	CharacterMovementComponent->MaxWalkSpeed;
	}
}

float ACharacterParent::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth = CurrentHealth - DamageAmount;
	HealthWidget->SetHealthBarPercent(CurrentHealth / Health);
	return DamageAmount;
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
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &ACharacterParent::ThrowGrenade);
CliffHangABCpp = FindComponentByClass<UCliffHangAB>();
	if (CliffHangABCpp != nullptr)
	{
		PlayerInputComponent->BindAction("Cliff", IE_Pressed, this, &ACharacterParent::GrabWall);
		PlayerInputComponent->BindAction("Cliff", IE_Released, this, &ACharacterParent::letGoOffWall);
	}
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
}

void ACharacterParent::MoveForward(float Value)
{

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

void ACharacterParent::MoveRight(float Value)
{
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
void ACharacterParent::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACharacterParent::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACharacterParent::GrabWall()
{
	CliffHangABCpp->hang();
}

void ACharacterParent::letGoOffWall()
{
	CliffHangABCpp->Release();
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

void ACharacterParent::UsePickUp()
{
	if (PickUpData != nullptr) {
		PickUpData->PickUpDoYourThing();
	}
}
void ACharacterParent::ThrowGrenade()
{
	AGrenadeParent * Grenade=  GetWorld()->SpawnActor<AGrenadeParent>(GrenadeParentTSubClass, FTransform(FRotator(0, 0, 0), GetActorLocation() + GetActorForwardVector() * 60, FVector(1)));
	if (Grenade != nullptr)
	{
		Grenade->Thorw(ThorwSpeed, GetActorForwardVector());
	}
}