// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidField.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"


// Sets default values
AAsteroidField::AAsteroidField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hismc = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM"));
	SetRootComponent(hismc);
}

// Called when the game starts or when spawned
void AAsteroidField::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAsteroidField::OnConstruction(const FTransform& transform)
{
	if (!hismc)
		return;

	hismc->bAutoRebuildTreeOnInstanceChanges = false;
	hismc->ClearInstances();

	for (int as = 0; as < asteroidRings.NumAsteroids; as++)
	{
		float r = FMath::FRandRange(asteroidRings.MajorRadius - asteroidRings.MinorRadius, 
			asteroidRings.MajorRadius + asteroidRings.MinorRadius);
		//FRotator rot = FRotator(0.f, FMath::FRandRange(0.f, 360.f), 0.f);

		float z = FMath::FRandRange(-asteroidRings.MinorRadius, asteroidRings.MinorRadius);
		float ang = FMath::FRandRange(0.f, 360.f);
		float x = r * FMath::Cos(ang * 3.14169f / 180.f);
		float y = r * FMath::Sin(ang * 3.14169f / 180.f);
		//FVector v(1.0f, 0.0f, 0.0f);
		//v = rot.RotateVector(v)*r;



		FTransform transf;
		transf.SetLocation(FVector(x, y, z));
		/*transf.SetRotation(FQuat(FRotator(FMath::FRandRange(0.f, 360.f),
			FMath::FRandRange(0.f, 360.f),
			FMath::FRandRange(0.f, 360.f))));*/
		transf.SetScale3D(FVector(1.f, 1.f, 1.f));
		hismc->AddInstance(transf);
	}
	hismc->BuildTreeIfOutdated(true, true);
}

// Called every frame
void AAsteroidField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

