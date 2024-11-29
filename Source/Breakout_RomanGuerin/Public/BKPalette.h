// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BKPalette.generated.h"

UCLASS()
class BREAKOUT_ROMANGUERIN_API ABKPalette : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Ball")
	UStaticMeshComponent* Visu;

private:
	void MoveObject();

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
