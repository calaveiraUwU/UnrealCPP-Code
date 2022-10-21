// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	canionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CanionMesh"));
	SetRootComponent(canionMesh);
	static ConstructorHelpers::FObjectFinder<UMaterial> LaserMat(TEXT("/Game/Materials/LaserMaterial"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LaserMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (LaserMesh.Succeeded())
		canionMesh->SetStaticMesh(LaserMesh.Object);
	if (LaserMat.Succeeded())
		canionMesh->SetMaterial(0, LaserMat.Object);
	canionMesh->SetWorldScale3D(FVector(1.f, 0.04f, 0.04f));
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaser::SetLaserVariables(float speedVal)
{
	speed = speedVal;
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(speed* DeltaTime, 0.f, 0.f));
}

