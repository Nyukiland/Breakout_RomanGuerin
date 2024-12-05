// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "BKPalette.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class BREAKOUT_ROMANGUERIN_API ABKPalette : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Paddle")
	UStaticMeshComponent* Visu;

	UPROPERTY(EditAnywhere, Category = "Paddle")
	float Speed = 1;

	UPROPERTY(EditAnywhere, Category = "Paddle")
	float MaxPos = 1;
	UPROPERTY(EditAnywhere, Category = "Paddle")
	float MinPos = 1;


	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IAMove;

	FVector StartPos = FVector(0, 0, 0);

public:

	float MoveValue = 0;


private:
	void MoveInput(const FInputActionValue& Value);
	void Move(float DeltaTime);
	void StopInput(const FInputActionValue& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	ABKPalette();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ResetPos();
	FBox GetVisuBound();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
