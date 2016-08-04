// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "RnD.generated.h"

UENUM(BlueprintType)
enum class EStencilColor : uint8
{
	SC_None=0		UMETA(DisplayName="Disabled"),
	SC_Green=250 	UMETA(DisplayName="Green"),
	SC_Blue=251		UMETA(DisplayName="Blue"),
	SC_Red=252		UMETA(DisplayName="Red"),
	SC_White=253	UMETA(DisplayName="White")
};

USTRUCT(BlueprintType)
struct FSpawnInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawning)
	TSubclassOf<class AWaveEnemy> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawning)
	int32 MaxAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawning)
	float Probability;
};

USTRUCT(BlueprintType)
struct FWaveInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawning)
	int32 TotalNumberOfEnemies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawning)
	TArray<FSpawnInfo> SpawnInfo;
};
