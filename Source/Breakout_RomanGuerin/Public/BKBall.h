// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BKBall.generated.h"


UCLASS()
class BREAKOUT_ROMANGUERIN_API ABKBall : public AActor
{
	GENERATED_BODY()
	
private:

	float CurrentSpeed;
	FVector Direction;
	UPROPERTY(EditAnywhere, Category = "Ball")
	float Radius;
	UPROPERTY(VisibleAnywhere, Category = "Ball")
	UStaticMeshComponent* BallComponent;

public:	
	// Sets default values for this actor's properties
	ABKBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddSpeed(int32 Speed);

private:
	void MoveBall();
	void CollisionDetection(float DeltaTime);

};
