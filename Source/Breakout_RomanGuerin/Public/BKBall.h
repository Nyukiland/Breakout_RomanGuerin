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

	UPROPERTY(EditAnywhere, Category = "Ball")
	float BaseSpeed = 50;
	float CurrentSpeed;	
	UPROPERTY(EditAnywhere, Category = "Ball")
	FVector Direction = FVector(1,0,0);
	UPROPERTY(EditAnywhere, Category = "Ball")
	float Radius;
	UPROPERTY(VisibleAnywhere, Category = "Ball")
	UStaticMeshComponent* BallComponent;

public:	
	void AddSpeed(int32 Speed);

private:
	ABKBall();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void MoveBall(float DeltaTime);
	void CollisionDetection(float DeltaTime);

};
