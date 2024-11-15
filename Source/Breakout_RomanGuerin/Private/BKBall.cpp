// Fill out your copyright notice in the Description page of Project Settings.


#include "BKBall.h"

// Sets default values
ABKBall::ABKBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Direction = FVector(1, 0, 0);
	CurrentSpeed = 10;
	Radius = 1;

	BallComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallComponent"));
	RootComponent = BallComponent;

	// Load a sphere mesh from the engine's default assets
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereAsset.Succeeded())
	{
		BallComponent->SetStaticMesh(SphereAsset.Object);
	}

	// Optionally, set the material
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("/Game/StarterContent/Materials/M_Brick_Clay.M_Brick_Clay"));
	if (SphereMaterial.Succeeded())
	{
		BallComponent->SetMaterial(0, SphereMaterial.Object);
	}

	BallComponent->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ABKBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABKBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveBall();
	CollisionDetection(DeltaTime);
}

void ABKBall::AddSpeed(int32 Speed)
{
	CurrentSpeed += Speed;
}

void ABKBall::MoveBall()
{
	if (!BallComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("BallComponent is null in ABKBall::MoveBall!"));
		return;  
	}
	BallComponent->SetPhysicsLinearVelocity(Direction * CurrentSpeed);
}

void ABKBall::CollisionDetection(float DeltaTime)
{
	FVector Start = GetActorLocation();
	FVector End = Start + Direction * CurrentSpeed * DeltaTime;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(Radius), QueryParams);
}

