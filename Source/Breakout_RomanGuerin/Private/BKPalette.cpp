// Fill out your copyright notice in the Description page of Project Settings.


#include "BKPalette.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "BKManager.h"

// Sets default values
ABKPalette::ABKPalette()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StartPos = FVector(0, 0, 0);
	MoveValue = 0;
	Speed = 1;

	Visu = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallComponent"));
	RootComponent = Visu;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeAsset.Succeeded())
	{
		Visu->SetStaticMesh(CubeAsset.Object);
		Visu->SetWorldScale3D(FVector(0.5f, 2, 1));
	}

	Visu->SetSimulatePhysics(false);
	Visu->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABKPalette::BeginPlay()
{
	Super::BeginPlay();
	ABKManager::Get()->RegisterInObjectCollision(this);

	StartPos = Visu->GetComponentLocation();

	ABKManager::Get()->RegisterPaddle(this);
}

// Called every frame
void ABKPalette::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void ABKPalette::ResetPos()
{
	Visu->SetWorldLocation(StartPos);
}

FBox ABKPalette::GetVisuBound()
{
	FBoxSphereBounds LocalBounds = Visu->GetStaticMesh()->GetBounds();

	FTransform ComponentTransform = Visu->GetComponentTransform();
	FBox WorldBounds = LocalBounds.GetBox().TransformBy(ComponentTransform);

	return WorldBounds;
}

// Called to bind functionality to input
void ABKPalette::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IAMove)
		{
			EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &ABKPalette::MoveInput);
			EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Completed, this, &ABKPalette::StopInput);
		}
	}
}

void ABKPalette::MoveInput(const FInputActionValue& Value)
{
	MoveValue = Value.Get<float>();
}

void ABKPalette::StopInput(const FInputActionValue& Value)
{
	MoveValue = 0;
}

void ABKPalette::Move(float DeltaTime)
{
	FVector Movement = MoveValue * Speed * DeltaTime * FVector(0, 1, 0);
	FVector ClampedPos = Visu->GetComponentLocation() + Movement;
	ClampedPos = FVector(ClampedPos.X, FMath::Clamp(ClampedPos.Y, MinPos, MaxPos), ClampedPos.Z);
	Visu->SetWorldLocation(ClampedPos);
}