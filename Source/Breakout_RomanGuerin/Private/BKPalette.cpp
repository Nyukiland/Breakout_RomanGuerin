// Fill out your copyright notice in the Description page of Project Settings.


#include "BKPalette.h"

// Sets default values
ABKPalette::ABKPalette()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ABKPalette::MoveObject()
{
}

// Called when the game starts or when spawned
void ABKPalette::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABKPalette::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABKPalette::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

