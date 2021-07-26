// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/Texture2D.h"
#include "Interior.generated.h"

USTRUCT(BlueprintType)
struct FInteriorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
	UStaticMesh* Mesh;
};

UCLASS()
class THEHOMEOFMYDREAM_API AInterior : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterior();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshInterior;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Root")
	USceneComponent* Root;

	UPROPERTY(BlueprintReadOnly, Category = "Main", meta = (ExposeOnSpawn = "true"))
	FInteriorInfo InteriorInfo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

