#include "BKManager.h"
#include "BKBrick.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/WorldSettings.h"
#include "Blueprint/UserWidget.h"

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

	Position += FVector(BrickOffset.X * 3, 0, 0);
	GenerateTile(GreenBrick, Position);
	
	Position += FVector(BrickOffset.X * 3, 0, 0);
	GenerateTile(OrangeBrick, Position);
	
	Position += FVector(BrickOffset.X * 3, 0, 0);
	GenerateTile(RedBrick, Position);
}

void ABKManager::GenerateTile(TSubclassOf<ABKBrick> Brick, FVector Position)
{

	for (int i = 0; i <= BrickPerLine; i++)
	{
		if (i == 0) continue;

		Spawn(Brick, Position + FVector(0, BrickOffset.Y * i, 0));
	}

	Position += FVector(BrickOffset.X, 0, 0);

	for (int i = 0; i <= BrickPerLine; i++)
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
		GenerateTile(YellowBrick);
		Phase2 = true;
	}
	else
	{
		EndGame();
	}
}