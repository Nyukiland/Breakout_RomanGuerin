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
	FVector NormalCollision = FVector::ZeroVector;
	TArray<AActor*> Collided;

	// Starting and ending positions of the ball
	FVector StartPosition = BallComponent->GetComponentLocation();
	FVector EndPosition = StartPosition + (Direction * CurrentSpeed * DeltaTime);

	// Number of steps for interpolating along the movement path
	const int32 NumSteps = 10; // Higher = more precision
	const float StepSize = 1.0f / NumSteps;

	// Iterate through interpolated positions along the movement path
	for (int32 Step = 0; Step <= NumSteps; Step++)
	{
		// Calculate the current position based on interpolation
		FVector CurrentPosition = FMath::Lerp(StartPosition, EndPosition, Step * StepSize);

		// Recalculate the ball's bounding box for this position
		FBox BallBounds = FBox(CurrentPosition - FVector(Radius), CurrentPosition + FVector(Radius));

		// Check for collisions with each actor
		for (AActor* Actor : ABKManager::Get()->ObjectCollision)
		{
			if (!Actor) continue;

			// Get the actor's bounding box
			FBox ActorBounds = Actor->GetComponentsBoundingBox();

			// Check if the ball's bounding box intersects with the actor's bounding box
			if (ActorBounds.Intersect(BallBounds))
			{
				// Collision detected: calculate the collision normal
				FVector ClosestPoint = ActorBounds.GetClosestPointTo(CurrentPosition);
				FVector ColDir = (CurrentPosition - ClosestPoint).GetSafeNormal();
				NormalCollision += ColDir;

				Collided.Add(Actor);
			}
		}

		if (NormalCollision != FVector(0, 0, 0)) break;
	}

	// Reflect the direction based on accumulated collision normal
	if (NormalCollision.SizeSquared() > 0)
	{
		NormalCollision.Normalize();
		Direction = Direction.MirrorByVector(NormalCollision);
	}

	// Handle brick-specific behavior
	for (AActor* Actor : Collided)
	{
		if (ABKBrick* Brick = Cast<ABKBrick>(Actor))
		{
			Brick->InteractWithBall(this);
		}
	}
}