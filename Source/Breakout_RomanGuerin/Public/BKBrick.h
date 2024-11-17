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
	UPROPERTY(VisibleAnywhere, Category = "Brick")
	UStaticMeshComponent* BrickVisual;
	UPROPERTY(EditAnywhere, Category = "Brick")
	int32 Score = 0;
	UPROPERTY(EditAnywhere, Category = "Brick")
	bool SpawnOthers = false;

public:	
	virtual void InteractWithBall(ABKBall* Ball);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	ABKBrick();

};
