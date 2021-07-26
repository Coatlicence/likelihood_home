// Fill out your copyright notice in the Description page of Project Settings.


#include "Interior.h"
#include "Engine/Engine.h"

// Sets default values
AInterior::AInterior()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshInterior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	MeshInterior->SetStaticMesh(InteriorInfo.Mesh);

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	bool setted = SetRootComponent(Root);

	if (setted)
		MeshInterior->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	
	if (InteriorInfo.Mesh) 	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 12.f, FColor::Cyan, TEXT("mesh"));
	else GEngine->AddOnScreenDebugMessage(INDEX_NONE, 12.f, FColor::Cyan, TEXT("no mesh"));


}

// Called when the game starts or when spawned
void AInterior::BeginPlay()
{
	Super::BeginPlay();
	
	MeshInterior->SetStaticMesh(InteriorInfo.Mesh);
}

// Called every frame
void AInterior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

