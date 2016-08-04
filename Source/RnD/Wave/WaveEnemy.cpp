// Fill out your copyright notice in the Description page of Project Settings.

#include "RnD.h"
#include "WaveEnemy.h"
#include "WaveGameMode.h"
#include "WavePlayer.h"

void AWaveEnemy::OnInteract_Implementation(AActor* Caller){
	AWaveGameMode* WaveGM = GetWorld()->GetAuthGameMode<AWaveGameMode>();
	if(WaveGM){
		AWavePlayer* Killer = Cast<AWavePlayer>(Caller);
		WaveGM->Killed(Killer->GetController(), GetController());
	}
	Destroy();
}
