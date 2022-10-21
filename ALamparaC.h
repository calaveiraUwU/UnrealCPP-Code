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
	
	//Para poder ver las propiedades des de cualquier sitio pero de tipo lectura.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;//Declaramos el componente de la principal para luego en el editor asignarle un static mesh. (Class es para no incluir las clases en el .h)
	
	//Para poder ver las propiedades des de cualquier sitio pero de tipo lectura.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SecondMesh;//Declaramos el componente de la secundario para luego en el editor asignarle un static mesh.
	
	//Para poder ver las propiedades des de cualquier sitio y poderlas editar.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float speed = 100.f;//Declaramos y definimos la velocidad estandar de el objeto.
	
	//
	UFUNCTION(BlueprintCallable)
	void IncreaseSpeed(); //Creamos una función para poder ir incrementando la velocidad del objeto.
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
