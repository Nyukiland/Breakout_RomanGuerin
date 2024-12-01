// Fill out your copyright notice in the Description page of Project Settings.


#include "BKController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ABKController::BeginPlay()
{
	Super::BeginPlay();

	// Ensure Enhanced Input is initialized
	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add the input mapping context
			if (PlayerMappingContext)
			{
				Subsystem->AddMappingContext(PlayerMappingContext, 0);
			}
		}
	}
}