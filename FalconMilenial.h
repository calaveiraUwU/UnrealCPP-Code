// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Laser.h"
#include "FalconMilenial.generated.h"

UCLASS()
class FIRSTCPPPROJECT_API AFalconMilenial : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFalconMilenial();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* StaticMeshC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Canion;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* rootComponentC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* spawnPoint1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* spawnPoint2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle TimerHandler;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PitchSpeed = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float YawSpeed = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ForwardAcceleration = 1000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RollSpeed = 90.f;



	float _minRotation = -70.f, _maxRotation = 70.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void Pitch(float value);
	
	void Yaw(float value);

	void Forward(float value);

	void Roll(float value);

	void RotateX(float value);
	
	void RotateY(float value);

	void ShootPressed();

	void Shoot();
	
	void ShootUnpressed();

	UFUNCTION(BlueprintImplementableEvent)
    void ChangePower(float PowerFactor);

	float timer;
	
	bool canionPoint;

private:

	float CurrentSpeed = 0.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Trigger Box")
	class UBoxComponent* TriggerBox;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
