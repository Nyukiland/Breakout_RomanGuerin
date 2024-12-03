// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "BKManager.generated.h"

class ABKBrick;
class ABKBall;
class ABKPalette;

UCLASS()
class BREAKOUT_ROMANGUERIN_API ABKManager : public AActor
{
	GENERATED_BODY()

public:
	static ABKManager* Get();

	UPROPERTY(EditAnywhere, Category = "Control")
	TArray<AActor*> ObjectCollision;

	int32 Score;
	int32 Life = 3;

private:

	UPROPERTY(EditAnywhere, Category = "Control")
	FVector BrickOffset = FVector(110, 60, 0);

	UPROPERTY(EditAnywhere, Category = "Control")
	float OffsetLine = 5;

	UPROPERTY(EditAnywhere, Category = "Control")
	int32 BrickPerLine = 5;

	UPROPERTY(EditAnywhere, Category = "Control")
	TSubclassOf<ABKBrick> YellowBrick;

	UPROPERTY(EditAnywhere, Category = "Control")
	TSubclassOf<ABKBrick> GreenBrick;

	UPROPERTY(EditAnywhere, Category = "Control")
	TSubclassOf<ABKBrick> OrangeBrick;

	UPROPERTY(EditAnywhere, Category = "Control")
	TSubclassOf<ABKBrick> RedBrick;

	UPROPERTY(EditAnywhere, Category = "Control")
	TSubclassOf<UUserWidget> MainUIClass;

	bool Phase2 = false;
	static ABKManager* Instance;
	UUserWidget* MainUI;
	ABKBall* CurrentBall;
	ABKPalette* CurrentPaddle;

public:
	void RegisterBall(ABKBall* Ball);
	void RegisterPaddle(ABKPalette* Paddle);
	void RemoveFromObjectCollision(ABKBrick* Brick);
	void DeathZoneHit();
	void RegisterInObjectCollision(AActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "Control")
	int32 GetScore();
	UFUNCTION(BlueprintCallable, Category = "Control")
	int32 GetLife();

private:
	virtual void BeginPlay() override;
	void PrepTile();
	void GenerateTile(TSubclassOf<ABKBrick> Brick, FVector Position);
	void Spawn(TSubclassOf<ABKBrick> Brick, FVector Position);
	void CheckForBrickLeft();
	void EndGame();
	void ResetBallPosition();

};