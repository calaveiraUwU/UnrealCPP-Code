// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRingParams.h"
#include "AsteroidField.generated.h"

UCLASS()
class FIRSTCPPPROJECT_API AAsteroidField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	class UHierarchicalInstancedStaticMeshComponent* hismc;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRingParams asteroidRings;
	
	virtual void OnConstruction(const FTransform& transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
