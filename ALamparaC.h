// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ALamparaC.generated.h"

UCLASS()
class FIRSTCPPPROJECT_API AALamparaC : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AALamparaC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SecondMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float speed = 100.f;
	UFUNCTION(BlueprintCallable)
	void IncreaseSpeed();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
