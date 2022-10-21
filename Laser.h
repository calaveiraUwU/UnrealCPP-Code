// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class FIRSTCPPPROJECT_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* canionMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float speed;

	void SetLaserVariables(float speedVal);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
