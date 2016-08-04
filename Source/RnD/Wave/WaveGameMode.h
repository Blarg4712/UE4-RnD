// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "WaveGameMode.generated.h"

UCLASS()
class RND_API AWaveGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Wave")
	void SetWaveDelay(float Delay);
	UFUNCTION(BlueprintCallable, Category="Wave")
	void SetMaxWaves(int32 Max);
	UFUNCTION(BlueprintCallable, Category="Wave")
	void SetWaveInfo(const TArray<FWaveInfo>& newWaveInfo);

	void UpdateHUD();

	virtual void BeginPlay() override;
	virtual void Killed(AController* Killer, AController* Victim);

protected:
	void BeginWave();
	void EndWave();
	void BeginSpawning();
	void SpawnEnemy();
	virtual void StartMatch() override;
	virtual void EndMatch() override;
	virtual void InitGameState() override;

private:
	UPROPERTY(EditDefaultsOnly)
	FName SpawnTag;
	UPROPERTY(EditDefaultsOnly)
	float WaveDelay;
	UPROPERTY(EditDefaultsOnly)
	float SpawnDelay;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxWaves;
	UPROPERTY(EditDefaultsOnly)
	TArray<struct FWaveInfo> WaveInfo;

	TArray<int32> SpawnedOfType;
	int32 EnemyToSpawn;
	int32 EnemiesSpawned;

	FTimerHandle WaveTimerHandle;
	FTimerHandle SpawnTimerHandle;

	TArray<AActor*> AISpawnPoints;

	class AWaveGameState* WaveGS;
};
