// Fill out your copyright notice in the Description page of Project Settings.


#include "BKBall.h"
#include "BKManager.h"
#include "BKBrick.h"

// Sets default values
ABKBall::ABKBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Direction = FVector(1, 0, 0);
	CurrentSpeed = BaseSpeed;
	Radius = 1;

	BallComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallComponent"));
	RootComponent = BallComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereAsset.Succeeded())
	{
		BallComponent->SetStaticMesh(SphereAsset.Object);
	}

	//remove all physics system
	BallComponent->SetSimulatePhysics(false);
	BallComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABKBall::BeginPlay()
{
	Super::BeginPlay();
	
	Direction = FVector(1, 0, 0);
	CurrentSpeed = BaseSpeed;
}

// Called every frame
void ABKBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollisionDetection(DeltaTime);
	MoveBall(DeltaTime);
}

void ABKBall::AddSpeed(int32 Speed)
{
	CurrentSpeed += Speed;
}

void ABKBall::MoveBall(float DeltaTime)
{
	FVector Movement = Direction * CurrentSpeed * DeltaTime;
	BallComponent->SetWorldLocation(BallComponent->GetComponentLocation() + Movement);
}

void ABKBall::CollisionDetection(float DeltaTime)
{
	FVector NormalCollision = FVector(0, 0, 0);
	TArray<ABKBrick*> BricksCollided;

	FVector Location = BallComponent->GetComponentLocation() + (Direction * CurrentSpeed * DeltaTime);

	for (AActor* Actor : ABKManager::Get()->ObjectCollision)
	{
		if (!Actor) continue;

		FBox ActorBounds = Actor->GetComponentsBoundingBox();
		if (ActorBounds.IsInside(Location))
		{
			FVector ColDir = (Location - Actor->GetActorLocation()).GetSafeNormal();
			//if (ColDir.X > ColDir.Y) ColDir.Y = 0;
			//else ColDir.X = 0;
			NormalCollision += ColDir;

			if (ABKBrick* Brick = Cast<ABKBrick>(Actor)) BricksCollided.Add(Brick);
		}
	}

	for (int32 i = BricksCollided.Num() - 1; i >= 0; i--)
	{
		if (BricksCollided[i])
		{
			BricksCollided[i]->InteractWithBall(this);
		}
	}

	if (NormalCollision.SizeSquared() > 0)
	{
		NormalCollision.Normalize();
		Direction = Direction.MirrorByVector(NormalCollision);
	}
}

