// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ConstructorHelpers.h"
#include "Interior.h"
#include "TheHomeOfMyDreamCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class ATheHomeOfMyDreamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	ATheHomeOfMyDreamCharacter();
	
	UFUNCTION(BlueprintCallable)
	void OpenInteriorMode(FInteriorInfo FurnitureMonitor);

	UFUNCTION(BlueprintCallable)
	void CloseInteriorMode();

protected:
	virtual void BeginPlay();

	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Building")
	bool BuildingMode = false;

	UPROPERTY(BlueprintReadOnly, Category = "Building")
	FInteriorInfo FurnitureMonitor;

	UPROPERTY(BlueprintReadOnly, Category = "Building")
	UStaticMeshComponent* FurnitureMonitorComponent;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	
	void MoveForward(float Val);

	void MoveRight(float Val);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
		
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

