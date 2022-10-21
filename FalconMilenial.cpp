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

	rootComponentC = CreateDefaultSubobject<USceneComponent>(TEXT("rootComponentC"));
	SetRootComponent(rootComponentC);
	StaticMeshC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship"));
	StaticMeshC->SetupAttachment(rootComponentC);
	//StaticMeshC->SetCollisionResponseToChannel()
	Canion = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Canion"));
	Canion->SetupAttachment(StaticMeshC);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraBoom->SetupAttachment(rootComponentC);
	CameraBoom->TargetArmLength = 700.0f;
	CameraBoom->SetRelativeRotation(FRotator(-15, 0, 0));
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraLagSpeed = 10.f;


	spawnPoint1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SP1"));
	spawnPoint1->SetupAttachment(Canion);

	spawnPoint2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SP2"));
	spawnPoint2->SetupAttachment(Canion);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	TriggerBox->SetBoxExtent(StaticMeshC->GetRelativeScale3D(), true);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetupAttachment(rootComponentC);
	//FVector(13.02f, 9.50f, 1.85f)

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
	AddActorLocalRotation(FRotator(value * PitchSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f));
}

void AFalconMilenial::Yaw(float value)
{
	AddActorLocalRotation(FRotator(0.f, value * PitchSpeed * GetWorld()->DeltaTimeSeconds, 0.f));
}

void AFalconMilenial::Roll(float value)
{
	AddActorLocalRotation(FRotator(0.f, 0.f, value * RollSpeed * GetWorld()->DeltaTimeSeconds));
}

void AFalconMilenial::Forward(float value)
{
	CurrentSpeed = FMath::FInterpConstantTo(CurrentSpeed, Speed * value, GetWorld()->DeltaTimeSeconds, ForwardAcceleration);
	AddActorLocalOffset(FVector(CurrentSpeed* GetWorld()->DeltaTimeSeconds, 0.f, 0.f));

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
	if (CameraBoom->GetRelativeRotation().Pitch + (value * RollSpeed * GetWorld()->DeltaTimeSeconds) >= _minRotation && CameraBoom->GetRelativeRotation().Pitch + (value * RollSpeed * GetWorld()->DeltaTimeSeconds) <= _maxRotation)
		CameraBoom->AddRelativeRotation(FRotator(value * RollSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f));
}

void AFalconMilenial::ShootPressed()
{

	UWorld* World = GetWorld();
		if (canionPoint)
		{
			const FTransform SpawnLocAndRotation = spawnPoint1->GetComponentTransform();
			ALaser* Laser = World->SpawnActorDeferred<ALaser>(ALaser::StaticClass(), SpawnLocAndRotation);
			Laser->SetLaserVariables(10000.f + CurrentSpeed);
			Laser->FinishSpawning(SpawnLocAndRotation);
		}
		else
		{
			const FTransform SpawnLocAndRotation = spawnPoint2->GetComponentTransform();
			ALaser* Laser = World->SpawnActorDeferred<ALaser>(ALaser::StaticClass(), SpawnLocAndRotation);
			Laser->SetLaserVariables(10000.f + CurrentSpeed);
			Laser->FinishSpawning(SpawnLocAndRotation);
		}
		canionPoint = !canionPoint;
}

void AFalconMilenial::Shoot()
{
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AFalconMilenial::ShootPressed, 0.4f, true, 0.f);
}

void AFalconMilenial::ShootUnpressed()
{
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
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		FString IntAsString = FString::FromInt(SweepResult.Item);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit on " + IntAsString));
	}
}

void AFalconMilenial::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
	}
}

// Called to bind functionality to input
void AFalconMilenial::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("UpDown", this, &AFalconMilenial::Pitch);
	PlayerInputComponent->BindAxis("RigthLeft", this, &AFalconMilenial::Yaw);
	PlayerInputComponent->BindAxis("Forward", this, &AFalconMilenial::Forward);
	PlayerInputComponent->BindAxis("Roll", this, &AFalconMilenial::Roll);
	PlayerInputComponent->BindAxis("RotateX", this, &AFalconMilenial::RotateX);
	PlayerInputComponent->BindAxis("RotateY", this, &AFalconMilenial::RotateY);
	PlayerInputComponent->BindAction("FalconShoot", IE_Pressed, this, &AFalconMilenial::Shoot);
	PlayerInputComponent->BindAction("FalconShoot", IE_Released, this, &AFalconMilenial::ShootUnpressed);
}