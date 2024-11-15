// Fill out your copyright notice in the Description page of Project Settings.


#include "ABKBall.h"

// Sets default values
AABKBall::AABKBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AABKBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABKBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

