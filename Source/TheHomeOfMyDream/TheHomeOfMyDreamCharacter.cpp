// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TheHomeOfMyDreamCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

#define g(x) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 12.f, FColor::Cyan, x);

//////////////////////////////////////////////////////////////////////////
// ATheHomeOfMyDreamCharacter

ATheHomeOfMyDreamCharacter::ATheHomeOfMyDreamCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	FurnitureMonitorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FurnitureMonitor"));
	FurnitureMonitorComponent->SetVisibility(false);
}

void ATheHomeOfMyDreamCharacter::OpenInteriorMode(FInteriorInfo FurnitureMonitor)
{
	BuildingMode = true;

	this->FurnitureMonitor = FurnitureMonitor;

	FurnitureMonitorComponent->SetStaticMesh(FurnitureMonitor.Mesh);
	FurnitureMonitorComponent->SetVisibility(true);

	if (FurnitureMonitor.Mesh)
	g(TEXT("ok"));

}

void ATheHomeOfMyDreamCharacter::CloseInteriorMode()
{
	BuildingMode = false;

	this->FurnitureMonitor = FInteriorInfo();
	
	FurnitureMonitorComponent->SetVisibility(false);
}

void ATheHomeOfMyDreamCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATheHomeOfMyDreamCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);



	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ATheHomeOfMyDreamCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATheHomeOfMyDreamCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATheHomeOfMyDreamCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATheHomeOfMyDreamCharacter::LookUpAtRate);
}

void ATheHomeOfMyDreamCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATheHomeOfMyDreamCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATheHomeOfMyDreamCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATheHomeOfMyDreamCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

