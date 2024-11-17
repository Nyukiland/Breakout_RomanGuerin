// Fill out your copyright notice in the Description page of Project Settings.


#include "BKBrick.h"
#include "BKBall.h"
#include "BKManager.h"


ABKBrick::ABKBrick()
{
	BrickVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallComponent"));
	RootComponent = BrickVisual;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeAsset.Succeeded())
	{
		BrickVisual->SetStaticMesh(CubeAsset.Object);
		BrickVisual->SetWorldScale3D(FVector(0.5f, 1, 1));
	}
}

// Called when the game starts or when spawned
void ABKBrick::BeginPlay()
{
	Super::BeginPlay();

}

void ABKBrick::InteractWithBall(ABKBall* Ball)
{
	ABKManager::Get()->Score += Score;
	ABKManager::Get()->ObjectCollision.Remove(this);
	Destroy();
}