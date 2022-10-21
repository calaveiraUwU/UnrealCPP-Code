// Fill out your copyright notice in the Description page of Project Settings.


#include "TorusAsteroidField.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATorusAsteroidField::ATorusAsteroidField()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	field = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(FName("MeshesField"));
	SetRootComponent(field);
	field->bMultiBodyOverlap = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AsteroidMesh(TEXT("/Game/StarterContent/Props/asteroid/AsteroidLOD0"));
	if (AsteroidMesh.Succeeded())
		field->SetStaticMesh(AsteroidMesh.Object);
}

void ATorusAsteroidField::OnConstruction(const FTransform& transform)
{
	int32 count_ast = 0;
	numerOfAsteroidPerCircle = FMath::Max(1, numerOfAsteroidPerCircle);
	if (field->GetInstanceCount() > 0)
		field->ClearInstances();
	float _2_PI = 2.f * UKismetMathLibrary::GetPI();
	for (int c = 0; c < numerOfCircles; c++)
	{
		float deltaAngle = _2_PI / numerOfAsteroidPerCircle;

		for (float ang = 0; ang < _2_PI; ang += deltaAngle)
		{
			float relativeCenterHeight = FMath::RandRange(-internalRadius, internalRadius);
			float maxOffsetRadius = FMath::Sqrt(internalRadius * internalRadius - relativeCenterHeight * relativeCenterHeight);
			float circleRadius = externalRadius + FMath::FRandRange(-maxOffsetRadius, maxOffsetRadius);
			FVector location = FVector(FMath::Cos(ang), FMath::Sin(ang), 0.f) * circleRadius + FVector(0.f, 0.f, relativeCenterHeight);
			FRotator rot = UKismetMathLibrary::RandomRotator();
			FVector scale = FVector(FMath::FRandRange(minScale, maxScale), FMath::FRandRange(minScale, maxScale), FMath::FRandRange(minScale, maxScale));
			FTransform transf(rot, location, scale);
			field->AddInstance(transf);
			count_ast++;
		}
	}


}

// Called when the game starts or when spawned
void ATorusAsteroidField::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATorusAsteroidField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	AddActorLocalRotation(FRotator(0.f, GetWorld()->DeltaTimeSeconds * fieldAngularSpeed, 0.f));
}



