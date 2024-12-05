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
	StartPos = FVector(0, 0, 0);

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

	StartPos = BallComponent->GetComponentLocation();

	ABKManager::Get()->RegisterBall(this);
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

void ABKBall::ResetPos()
{
	BallComponent->SetWorldLocation(StartPos);
	Direction = FVector(1, 0, 0);
}

void ABKBall::MoveBall(float DeltaTime)
{
	FVector Movement = Direction * CurrentSpeed * DeltaTime;
	BallComponent->SetWorldLocation(BallComponent->GetComponentLocation() + Movement);
}

void ABKBall::CollisionDetection(float DeltaTime)
{
	FVector NormalCollision = FVector::ZeroVector;
	TArray<AActor*> Collided;

	FVector StartPosition = BallComponent->GetComponentLocation();
	FVector EndPosition = StartPosition + (Direction * CurrentSpeed * DeltaTime);

	
	const int32 NumSteps = 10; 
	const float StepSize = 1.0f / NumSteps;

	for (int32 Step = 0; Step <= NumSteps; Step++)
	{
		FVector CurrentPosition = FMath::Lerp(StartPosition, EndPosition, Step * StepSize);

		FBox BallBounds = FBox(CurrentPosition - FVector(Radius), CurrentPosition + FVector(Radius));

		for (AActor* Actor : ABKManager::Get()->ObjectCollision)
		{
			if (!Actor) continue;

			FBox ActorBounds = Actor->GetComponentsBoundingBox();

			if (ActorBounds.Intersect(BallBounds))
			{
				UE_LOG(LogTemp, Warning, TEXT("Debug Message: Current Collision is %s"), *Actor->GetName());

				FVector ClosestPoint = ActorBounds.GetClosestPointTo(CurrentPosition);
				FVector ColDir = (CurrentPosition - ClosestPoint).GetSafeNormal();
				NormalCollision += ColDir;

				Collided.Add(Actor);
			}
		}

		if (NormalCollision != FVector(0, 0, 0)) break;
	}

	if (NormalCollision.SizeSquared() > 0)
	{
		NormalCollision.Normalize();
		Direction = Direction.MirrorByVector(NormalCollision);
	}

	for (int i = Collided.Num()-1; i >= 0; i--)
	{
		if (ABKBrick* Brick = Cast<ABKBrick>(Collided[i]))
		{
			Brick->InteractWithBall(this);
		}
	}
}