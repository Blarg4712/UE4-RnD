// Fill out your copyright notice in the Description page of Project Settings.

#include "RnD.h"
#include "InteractableChar.h"


AInteractableChar::AInteractableChar(){
	PrimaryActorTick.bCanEverTick = true;
	bCanInteract = true;
}

void AInteractableChar::BeginPlay(){
	Super::BeginPlay();

	for( UActorComponent* MeshComp : GetComponentsByClass(UMeshComponent::StaticClass()) ){
		UMeshComponent* thisMesh = Cast<UMeshComponent>(MeshComp);
		Meshes.Push(thisMesh);
	}

}

void AInteractableChar::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );

}

void AInteractableChar::OnInteract_Implementation(AActor* Caller){

}

void AInteractableChar::OnBeginFocus(){
	if(bCanInteract){
		for ( UMeshComponent* Mesh : Meshes ){
			Mesh->SetRenderCustomDepth(true);
			Mesh->SetCustomDepthStencilValue((uint8)StencilColor);
		}
	}
}

void AInteractableChar::OnEndFocus(){
	for ( UMeshComponent* Mesh : Meshes ){
		Mesh->SetRenderCustomDepth(false);
	}
}

void AInteractableChar::SetCanInteract(bool newCanInteract){
	bCanInteract = newCanInteract;
}

int32 AInteractableChar::GetMoneyReward() const{
	return MoneyReward;
}
