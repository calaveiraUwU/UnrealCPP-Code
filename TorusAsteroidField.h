// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorusAsteroidField.generated.h"

UCLASS()
class FIRSTCPPPROJECT_API ATorusAsteroidField : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATorusAsteroidField();

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
		class UHierarchicalInstancedStaticMeshComponent* field;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
		float internalRadius = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
		float externalRadius = 10000.f;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
		int32 numerOfCircles = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
		int32 numerOfAsteroidPerCircle = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
		float minScale = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
		float maxScale = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadonly)
		float fieldAngularSpeed = 0.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& transform) override;
};
