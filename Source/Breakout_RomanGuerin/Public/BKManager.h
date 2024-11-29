// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BKManager.generated.h"

class ABKBrick;

UCLASS()
class BREAKOUT_ROMANGUERIN_API ABKManager : public AActor
{
	GENERATED_BODY()

public:
	static ABKManager* Get();

	int32 Score;

	UPROPERTY(EditAnywhere, Category = "Control")
	TArray<AActor*> ObjectCollision;


private:
	static ABKManager* Instance;

	UPROPERTY(EditAnywhere, Category = "Control")
	int32 BrickPerLine = 5;

	UPROPERTY(EditAnywhere, Category = "Control")
	FVector SpawnPos = FVector(0,0,0);

	UPROPERTY(EditAnywhere, Category = "Control")
	TSubclassOf<ABKBrick> YellowBrick;

	bool Phase2 = false;

public:
	void RemoveFromObjectCollision(ABKBrick* Brick);

private:
	virtual void BeginPlay() override;
	void PrepTile();
	void GenerateTile(TSubclassOf<ABKBrick> Brick);
	void Spawn(TSubclassOf<ABKBrick> Brick, FVector Position);
	void CheckForBrickLeft();
	void EndGame();

};