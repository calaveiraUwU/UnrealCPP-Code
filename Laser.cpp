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
	
	//Establecemos el objeto y le establecemos que sea el componente padre.
	canionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CanionMesh"));
	SetRootComponent(canionMesh);
	
	//Buscamos el Material y lo guardamos en una variable.
	static ConstructorHelpers::FObjectFinder<UMaterial> LaserMat(TEXT("/Game/Materials/LaserMaterial"));
	
	//Buscamos el Objeto y lo guardamos en una variable.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LaserMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	
	//Comprobamos que el objeto existe y no esta vacio y se lo establecemos a el láser.
	if (LaserMesh.Succeeded())
		canionMesh->SetStaticMesh(LaserMesh.Object);
	
	//Comprobamos que el material existe y no esta vacio y se lo establecemos a el láser.
	if (LaserMat.Succeeded())
		canionMesh->SetMaterial(0, LaserMat.Object);
	
	//Le establecemos la escala para que se vea alargado y visible en el mapa.
	canionMesh->SetWorldScale3D(FVector(1.f, 0.04f, 0.04f));
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaser::SetLaserVariables(float speedVal)
{
	//Le establecemos la velocidad al objeto que le pasamos por valor al instanciarlo.
	speed = speedVal;
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Movemos el objeto cuando la velocidad sea mayor que 0.
	if(speed>0)
		AddActorLocalOffset(FVector(speed* DeltaTime, 0.f, 0.f));
}

