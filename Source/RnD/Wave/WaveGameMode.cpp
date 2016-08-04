// Fill out your copyright notice in the Description page of Project Settings.

#include "RnD.h"
#include "WaveGameMode.h"
#include "WaveEnemy.h"
#include "WaveGameState.h"
#include "WavePlayerState.h"
#include "Base/InteractableChar.h"
#include "WavePlayer.h"

void AWaveGameMode::InitGameState(){
	Super::InitGameState();

	WaveGS = Cast<AWaveGameState>(GameState);
	if(WaveGS){
		WaveGS->SetMaxWaves(MaxWaves);
		WaveGS->SetWaveDelay(WaveDelay);
	}
}

void AWaveGameMode::BeginPlay(){
	Super::BeginPlay();

	TArray<AActor*> Spawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Spawns);
	for(AActor* Spawn : Spawns){
		if(Spawn->ActorHasTag(SpawnTag)){
			AISpawnPoints.Add(Spawn);
		}
	}
}

void AWaveGameMode::UpdateHUD(){
	TArray<AActor*> Players;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWavePlayer::StaticClass(), Players);
	for(AActor* Player : Players){
		AWavePlayer* CastedPlayer = Cast<AWavePlayer>(Player);
		if(CastedPlayer && CastedPlayer->IsPlayerControlled()){
			CastedPlayer->UpdateHUD();
		}
	}
}

void AWaveGameMode::Killed(AController* Killer, AController* Victim){

	AInteractableChar* VictimPawn = Cast<AInteractableChar>(Victim->GetPawn());
	if(VictimPawn && !VictimPawn->IsPlayerControlled()){
		WaveGS->AddEnemiesRemaining(-1);
		UpdateHUD();
	}

	AWavePlayerState* WavePS = Cast<AWavePlayerState>(Killer->PlayerState);
	if(WavePS){
		WavePS->AddMoney( VictimPawn->GetMoneyReward() );
		UpdateHUD();
	}
	if(WaveGS->GetEnemiesRemaining() <= 0){
		EndWave();
	}
}

void AWaveGameMode::BeginWave(){
	GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);
	WaveTimerHandle.Invalidate();

	WaveGS->SetIsWaveActive(true);
	WaveGS->SetCurrentWave(WaveGS->GetCurrentWave() + 1);
	UpdateHUD();
	BeginSpawning();
}

void AWaveGameMode::EndWave(){
	WaveGS->SetIsWaveActive(false);
	UpdateHUD();
	if(WaveGS->GetCurrentWave() >= MaxWaves){
		EndMatch();
	}
	else{
		GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &AWaveGameMode::BeginWave, WaveDelay, false);
	}
}

void AWaveGameMode::BeginSpawning(){
	SpawnedOfType.Empty();
	int32 CurrentWave = WaveGS->GetCurrentWave();
	for(int i = 0; i < WaveInfo[CurrentWave-1].SpawnInfo.Num(); i++){
		SpawnedOfType.Add(0);
	}
	EnemyToSpawn = 0;
	EnemiesSpawned = 0;
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AWaveGameMode::SpawnEnemy, SpawnDelay, true);
}

void AWaveGameMode::SpawnEnemy(){
	if(AISpawnPoints.Num() < 1 || WaveInfo.Num() < 1){
		UE_LOG(LogTemp, Error, TEXT("Something went wrong!"));
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		SpawnTimerHandle.Invalidate();
	}

	int32 CurrentWave = WaveGS->GetCurrentWave();
	if(EnemiesSpawned < WaveInfo[CurrentWave-1].TotalNumberOfEnemies){
		FSpawnInfo SpawnInfo = WaveInfo[CurrentWave-1].SpawnInfo[EnemyToSpawn];

		if(SpawnedOfType[EnemyToSpawn] < SpawnInfo.MaxAmount){
			float Prob = FMath::RandRange(0.f, 1.f);
			if(Prob <= SpawnInfo.Probability){
				int32 SpawnIndex = FMath::RandRange(0, AISpawnPoints.Num()-1);
				FVector SpawnLoc = AISpawnPoints[SpawnIndex]->GetActorLocation();
				FRotator SpawnRot = AISpawnPoints[SpawnIndex]->GetActorRotation();

				GetWorld()->SpawnActor<AActor>(SpawnInfo.EnemyClass, SpawnLoc, SpawnRot);
				EnemiesSpawned++;
				SpawnedOfType[EnemyToSpawn]++;
				WaveGS->AddEnemiesRemaining(1);
				UpdateHUD();
			}
		}

		if(EnemyToSpawn >= WaveInfo[CurrentWave-1].SpawnInfo.Num()-1){
			EnemyToSpawn = 0;
		}
		else{
			EnemyToSpawn++;
		}
	}
	else{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		SpawnTimerHandle.Invalidate();
	}
}

void AWaveGameMode::StartMatch(){
	if(!HasMatchStarted()){
		EndWave();
	}
	Super::StartMatch();
	UpdateHUD();
}

void AWaveGameMode::EndMatch(){
	Super::EndMatch();
	UE_LOG(LogTemp, Warning, TEXT("You've won the match!"));
	UpdateHUD();
}

void AWaveGameMode::SetWaveDelay(float Delay){
	WaveDelay = Delay;
}

void AWaveGameMode::SetMaxWaves(int32 Max){
	MaxWaves = Max;
}

void AWaveGameMode::SetWaveInfo(const TArray<FWaveInfo>& newWaveInfo){
	WaveInfo = newWaveInfo;
}
