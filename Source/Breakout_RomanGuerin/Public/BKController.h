// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h" // Include for Enhanced Input
#include "EnhancedInputComponent.h" // Include for Enhanced Input Component
#include "InputMappingContext.h"    // Include for Input Mapping Context
#include "InputAction.h"            // Include for Input Actions
#include "BKController.generated.h"


/**
 * 
 */
UCLASS()
class BREAKOUT_ROMANGUERIN_API ABKController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

private:
	virtual void BeginPlay() override;
};
