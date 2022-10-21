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
	
	//El componente de la Nave.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* StaticMeshC;

	//El componente de el cañon.	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Canion;

	//Componente padre.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* rootComponentC;

	//Componente del brazo de la cámara.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* CameraBoom;

	//Componente de la cámara.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* FollowCamera;

	//Componente de el punto de referencia para instanciar el láser por el cañon 1.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* spawnPoint1;

	//Componente de el punto de referencia para instanciar el láser por el cañon 2.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* spawnPoint2;

	//El temporizador entre láser y láser.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle TimerHandler;

	//La velociad a la que se rota el Eje X. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PitchSpeed = 90.f;

	//La velociad a la que se rota el Eje Y. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float YawSpeed = 90.f;

	//La velocidad máxima a la que puede ir la nave.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed = 1000.f;

	//La acceleración que tiene la nave.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ForwardAcceleration = 1000.f;
	
	//La velociad a la que se rota el Eje Z.	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RollSpeed = 90.f;


	//La rotación X máxima permitida para la cámara para evitar el clipping.
	float _minRotation = -70.f, _maxRotation = 70.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//La función que rota el Eje X.
	void Pitch(float value);
	
	//La función que rota el Eje Y.
	void Yaw(float value);

	//La función que hace que avance la nave.
	void Forward(float value);

	//La función que rota el Eje Z.
	void Roll(float value);

	//La función que rota la cámara en su Eje X.
	void RotateX(float value);
	
	//La función que rota la cámara y el cañon en su eje Y.
	void RotateY(float value);

	//La función que dispara.
	void ShootPressed();

	//La función que gestiona el timer de los disparos.
	void Shoot();
	
	//La función que borra el timer que hemos generado en el shoot.	
	void ShootUnpressed();

	//La función que cambia la intensidad de el máterial dínamico de el propulsor.
	UFUNCTION(BlueprintImplementableEvent)
    	void ChangePower(float PowerFactor);

	//La declaración de donde almacenaremos el timer.
	float timer;
	
	//Saber por que cañon disparar.	
	bool canionPoint;

private:

	//Función que almacena la velocidad acutal.
	float CurrentSpeed = 0.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//El componente que determina la caja de colisones de la nave.
	UPROPERTY(VisibleAnywhere, Category = "Trigger Box")
	class UBoxComponent* TriggerBox;

	//La función que detecta que entra en la caja de colisones que tiene la nave.
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//La función que detecta que sale de la caja de colisones que tiene la nave.
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
