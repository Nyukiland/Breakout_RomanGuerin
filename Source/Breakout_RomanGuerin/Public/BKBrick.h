// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BKBrick.generated.h"

class ABKBall;

UCLASS()
class BREAKOUT_ROMANGUERIN_API ABKBrick : public AActor
{
	GENERATED_BODY()
	
protected: 
	UPROPERTY(EditAnywhere, Category = "Brick")
	int32 score;

public:	
	// Sets default values for this actor's properties
	ABKBrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractWithBall(ABKBall* Ball);

};
