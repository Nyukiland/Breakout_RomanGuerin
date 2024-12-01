// Fill out your copyright notice in the Description page of Project Settings.


#include "BKDeathZone.h"
#include "BKManager.h"

void ABKDeathZone::InteractWithBall(ABKBall* Ball)
{
	ABKManager::Get()->DeathZoneHit();
}