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
	float Speed;

	float MoveValue;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

private:
	void MoveInput(const FInputActionValue& Value);
	void Move(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	ABKPalette();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
