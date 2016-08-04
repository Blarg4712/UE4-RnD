// Fill out your copyright notice in the Description page of Project Settings.

#include "RnD.h"
#include "WaveShop.h"
#include "WaveGameState.h"

void AWaveShop::OnInteract_Implementation(AActor* Caller){
	AWaveGameState* WaveGS = GetWorld()->GetGameState<AWaveGameState>();
	if(WaveGS->IsWaveActive()){
		UE_LOG(LogTemp, Warning, TEXT("You cannot access the shop!"));
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Welcome to the shop!"));
	}
}
