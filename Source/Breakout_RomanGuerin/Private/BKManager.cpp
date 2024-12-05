#include "BKManager.h"
#include "BKBrick.h"
#include "BKBall.h"
#include "BKPalette.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

ABKManager* ABKManager::Instance = nullptr;

ABKManager* ABKManager::Get()
{
	if (Instance != nullptr)
	{
		return Instance;
	}

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(GWorld);
	if (World)
	{
		Instance = Cast<ABKManager>(UGameplayStatics::GetActorOfClass(World, ABKManager::StaticClass()));
	}

	if (Instance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ABKManager::Get() - No ABKManager found in the current world!"));
	}

	return Instance;
}

void ABKManager::BeginPlay()
{
	Super::BeginPlay();

	Instance = this;

	MainUI = CreateWidget<UUserWidget>(GetWorld(), MainUIClass);
	if (MainUI) MainUI->AddToViewport();

	PrepTile();
}

void ABKManager::PrepTile()
{
	FVector Position = GetActorLocation() - (FVector(0, 105 * (BrickPerLine)/2, 0));
	GenerateTile(YellowBrick, Position);

	Position += FVector(OffsetLine + BrickOffset.X, 0, 0);
	GenerateTile(GreenBrick, Position);
	
	Position += FVector(OffsetLine + BrickOffset.X, 0, 0);
	GenerateTile(OrangeBrick, Position);
	
	Position += FVector(OffsetLine + BrickOffset.X, 0, 0);
	GenerateTile(RedBrick, Position);
}

void ABKManager::GenerateTile(TSubclassOf<ABKBrick> Brick, FVector Position)
{

	for (int i = 0; i < BrickPerLine; i++)
	{
		Spawn(Brick, Position + FVector(0, BrickOffset.Y * i, 0));
	}

	Position += FVector(BrickOffset.X, 0, 0);

	for (int i = 0; i < BrickPerLine; i++)
	{
		Spawn(Brick, Position + FVector(0, BrickOffset.Y * i, 0));
	}
}

void ABKManager::Spawn(TSubclassOf<ABKBrick> Brick, FVector Position)
{
	AActor* ActorSpawned = GetWorld()->SpawnActor<ABKBrick>(Brick, Position, FRotator(0, 0, 0));
	RegisterInObjectCollision(ActorSpawned);
}

void ABKManager::EndGame()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
}

void ABKManager::ResetBallPosition()
{
	return; //Temporary to prevent a crash
	/*if (CurrentBall) CurrentBall->ResetPos();
	if (CurrentPaddle) CurrentPaddle->ResetPos();*/
}

void ABKManager::RegisterBall(ABKBall* Ball)
{
	CurrentBall = Ball;
}

void ABKManager::RegisterPaddle(ABKPalette* Paddle)
{
	CurrentPaddle = Paddle;
}

void ABKManager::RemoveFromObjectCollision(ABKBrick* Brick)
{
	if (!ObjectCollision.Contains(Brick)) return;

	ObjectCollision.Remove(Brick);
	CheckForBrickLeft();
}

void ABKManager::RegisterInObjectCollision(AActor* Actor)
{
	ObjectCollision.Add(Actor);
}

int32 ABKManager::GetScore()
{
	return Score;
}

int32 ABKManager::GetLife()
{
	return Life;
}

void ABKManager::DeathZoneHit()
{
	if (Life <= 0)
	{
		EndGame();
		return;
	}

	Life--;
	ResetBallPosition();
}

void ABKManager::CheckForBrickLeft()
{
	for (AActor* Actor : ObjectCollision)
	{
		if (Actor && Actor->IsA<ABKBrick>()) 
		{
			return;
		}
	}
	
	if (!Phase2)
	{
		ResetBallPosition();
		PrepTile();
		Phase2 = true;
	}
	else
	{
		EndGame();
	}
}