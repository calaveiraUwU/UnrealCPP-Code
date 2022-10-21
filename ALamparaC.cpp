// Fill out your copyright notice in the Description page of Project Settings.


#include "ALamparaC.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AALamparaC::AALamparaC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshcpp"));
	Mesh->SetupAttachment(RootComponent);// SetRootComponent(MainMesh);
	

	SecondMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondMeshUnderMesh"));
	SecondMesh->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AALamparaC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AALamparaC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector((speed * DeltaTime)*-1.f, 0.f, 0.f));

}

void AALamparaC::IncreaseSpeed()
{
	speed++;
}
