// Fill out your copyright notice in the Description page of Project Settings.


#include "FalconMilenial.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Laser.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFalconMilenial::AFalconMilenial()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Generamos el objeto padre, le ponemos un nombre para el editor y lo asignamos como tal.
	rootComponentC = CreateDefaultSubobject<USceneComponent>(TEXT("rootComponentC"));
	SetRootComponent(rootComponentC);
	
	//Generamos el objeto nave, le ponemos un nombre para el editor y lo asignamos debajo de el objeto padre.
	StaticMeshC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship"));
	StaticMeshC->SetupAttachment(rootComponentC);
	
	//Generamos el objeto cañon, le ponemos un nombre para el editor y lo asignamos debajo de la nave.
	Canion = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Canion"));
	Canion->SetupAttachment(StaticMeshC);

	//Generamos el objeto que sujeta la cámara y le da un movimiento, le ponemos un nombre para el editor y lo asignamos debajo del componente padre.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraBoom->SetupAttachment(rootComponentC);
	CameraBoom->TargetArmLength = 700.0f;//Longitud del brazo
	CameraBoom->SetRelativeRotation(FRotator(-15, 0, 0));//Rotación del brazo.
	CameraBoom->bEnableCameraLag = true;//Valor verdadero para que tenga movimiento el brazo.
	CameraBoom->bEnableCameraRotationLag = true;//Valor verdadero para que tenga rotación el brazo.
	CameraBoom->CameraLagSpeed = 10.f;//Cuanto movimiento va a tener.

	//Generamos el objeto que sirve de referencia al laser, le ponemos un nombre para el editor y lo asignamos debajo del componente cañon.
	spawnPoint1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SP1"));
	spawnPoint1->SetupAttachment(Canion);

	//Generamos el objeto que sirve de referencia al laser, le ponemos un nombre para el editor y lo asignamos debajo del componente cañon.
	spawnPoint2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SP2"));
	spawnPoint2->SetupAttachment(Canion);

	//Generamos el objeto que hace de cámara, le ponemos un nombre para el editor y lo asignamos debajo del componente brazo.
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom);

	//Generamos el objeto que hace de caja de colisones, le ponemos un nombre para el editor y lo asignamos debajo del componente padre.
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	TriggerBox->SetBoxExtent(StaticMeshC->GetRelativeScale3D(), true);//Lo escalamos segun los valores de la nave.
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));//Le ponemos un nombre al sistema de colisiones.
	TriggerBox->SetupAttachment(rootComponentC);

	//Generamos dos eventos dínamicos en relación de la caja de colisones para saber cuando se han activado o desactivado respectivamente.
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFalconMilenial::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFalconMilenial::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AFalconMilenial::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFalconMilenial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
}

void AFalconMilenial::Pitch(float value)
{
	//Le añadimos a la rotación X local una rotación que dependerá del input que le demos.
	AddActorLocalRotation(FRotator(value * PitchSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f));
}

void AFalconMilenial::Yaw(float value)
{
	//Le añadimos a la rotación Y local una rotación que dependerá del input que le demos.
	AddActorLocalRotation(FRotator(0.f, value * PitchSpeed * GetWorld()->DeltaTimeSeconds, 0.f));
}

void AFalconMilenial::Roll(float value)
{
	//Le añadimos a la rotación Z local una rotación que dependerá del input que le demos.
	AddActorLocalRotation(FRotator(0.f, 0.f, value * RollSpeed * GetWorld()->DeltaTimeSeconds));
}

void AFalconMilenial::Forward(float value)
{
	//Le asignamos un valor al float que almacena la velocidad del objeto.
	CurrentSpeed = FMath::FInterpConstantTo(CurrentSpeed, Speed * value, GetWorld()->DeltaTimeSeconds, ForwardAcceleration);
	//Le añadimos este valor a la posición X de el objeto.
	AddActorLocalOffset(FVector(CurrentSpeed* GetWorld()->DeltaTimeSeconds, 0.f, 0.f));

	//Modificamos la intensidad del material dínamico de la nave con el valor axis de la función.
	ChangePower(value);
}

void AFalconMilenial::RotateX(float value)
{
	CameraBoom->AddRelativeRotation(FRotator(0.f, value * RollSpeed * GetWorld()->DeltaTimeSeconds, 0.f));
	//Canion->AddRelativeRotation(FRotator(0.f, value * RollSpeed * GetWorld()->DeltaTimeSeconds, 0.f));
	Canion->SetRelativeRotation(FRotator(0.f,CameraBoom->GetRelativeRotation().Yaw, 0.f));
}

void AFalconMilenial::RotateY(float value)
{
	UE_LOG(LogTemp, Warning, TEXT("Num=%f"), CameraBoom->GetRelativeRotation().Pitch);
	
	//Comprobamos que el valor no supere los límites establecidos y rotamos el brazo de la cámara en su eje X.
	if (CameraBoom->GetRelativeRotation().Pitch + (value * RollSpeed * GetWorld()->DeltaTimeSeconds) >= _minRotation && CameraBoom->GetRelativeRotation().Pitch + (value * RollSpeed * GetWorld()->DeltaTimeSeconds) <= _maxRotation)
		CameraBoom->AddRelativeRotation(FRotator(value * RollSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f));
}

void AFalconMilenial::ShootPressed()
{

	UWorld* World = GetWorld();
		//Si el valor del cañon es verdadero dispara por el primero si no dispara por el segundo.
		if (canionPoint)
		{
			//Obtenemos la posición del punto de referencia.
			const FTransform SpawnLocAndRotation = spawnPoint1->GetComponentTransform();
			//Generamos una instancia de tipo retrasada para poder pasarle valores y cuando lo tenga todo poder acabar la instancia pasandole la clase.
			ALaser* Laser = World->SpawnActorDeferred<ALaser>(ALaser::StaticClass(), SpawnLocAndRotation);
			//Le pasamos la velocidad que queremos más la velocidad actual de la nave para que siempre salga a una velocidad moderada y que no se quede atrás.
			Laser->SetLaserVariables(10000.f + CurrentSpeed);
			//Finalmente instanciamos el objeto dínamico.
			Laser->FinishSpawning(SpawnLocAndRotation);
		}
		else
		{
			const FTransform SpawnLocAndRotation = spawnPoint2->GetComponentTransform();
			ALaser* Laser = World->SpawnActorDeferred<ALaser>(ALaser::StaticClass(), SpawnLocAndRotation);
			Laser->SetLaserVariables(10000.f + CurrentSpeed);
			Laser->FinishSpawning(SpawnLocAndRotation);
		}
	
		//Invertimos el valor actual del punto de disparo para que sea el contrario.
		canionPoint = !canionPoint;
}

void AFalconMilenial::Shoot()
{
	//Mientrás se presiona el botón iniciamos el reloj y llamamos a la función que dispara cuando se cumpla el delay.
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AFalconMilenial::ShootPressed, 0.4f, true, 0.f);
}

void AFalconMilenial::ShootUnpressed()
{
	//Limpiamos el reloj.
	GetWorldTimerManager().ClearTimer(TimerHandler);
}

/*void AFalconMilenial::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (OtherActor && (OtherActor != this) && OtherComp)
	//{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("hit item "+ SweepResult.Item));
	//}
}*/

void AFalconMilenial::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Cuando sea otro objeto que no sea la nave nos muestra el número de asteroide que representa del HISM.
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		FString IntAsString = FString::FromInt(SweepResult.Item);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit on " + IntAsString));
	}
}

void AFalconMilenial::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Cuando salimos de otro objeto que no sea la nave nos muestra que hemos salido de la colisión.
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
	}
}

// Called to bind functionality to input
void AFalconMilenial::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Gestionamos los imputs y las llamadas de funciones correspondientes.
	PlayerInputComponent->BindAxis("UpDown", this, &AFalconMilenial::Pitch);
	PlayerInputComponent->BindAxis("RigthLeft", this, &AFalconMilenial::Yaw);
	PlayerInputComponent->BindAxis("Forward", this, &AFalconMilenial::Forward);
	PlayerInputComponent->BindAxis("Roll", this, &AFalconMilenial::Roll);
	PlayerInputComponent->BindAxis("RotateX", this, &AFalconMilenial::RotateX);
	PlayerInputComponent->BindAxis("RotateY", this, &AFalconMilenial::RotateY);
	PlayerInputComponent->BindAction("FalconShoot", IE_Pressed, this, &AFalconMilenial::Shoot);
	PlayerInputComponent->BindAction("FalconShoot", IE_Released, this, &AFalconMilenial::ShootUnpressed);
}
