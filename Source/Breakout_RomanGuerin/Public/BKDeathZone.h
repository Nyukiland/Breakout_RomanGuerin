// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BKBrick.h"
#include "BKDeathZone.generated.h"

/**
 * 
 */
UCLASS()
class BREAKOUT_ROMANGUERIN_API ABKDeathZone : public ABKBrick
{
	GENERATED_BODY()
	
public:
	virtual void InteractWithBall(ABKBall* Ball) override;
};
