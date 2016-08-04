// Fill out your copyright notice in the Description page of Project Settings.

#include "RnD.h"
#include "InteractableActor.h"
#include "RnDPlayerChar.h"

AInteractableActor::AInteractableActor(){
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;
	bCanInteract = true;
}

void AInteractableActor::BeginPlay(){
	Super::BeginPlay();

	for( UActorComponent* MeshComp : GetComponentsByClass(UMeshComponent::StaticClass()) ){
		UMeshComponent* thisMesh = Cast<UMeshComponent>(MeshComp);
		Meshes.Push(thisMesh);
	}

	if(bTouchInteracts){
		OnActorBeginOverlap.AddDynamic(this, &AInteractableActor::OnOverlapBegin);
	}

}

void AInteractableActor::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );

}

void AInteractableActor::OnInteract_Implementation(AActor* Caller){
	if(bCanInteract){
		Destroy();
	}
}

void AInteractableActor::OnOverlapBegin(AActor* OtherActor, AActor* thisActor){
	ARnDPlayerChar* Player = Cast<ARnDPlayerChar>(OtherActor);
	if(Player){
		OnInteract(OtherActor);
	}
}

void AInteractableActor::OnBeginFocus(){
	if(bCanInteract){
		for ( UMeshComponent* Mesh : Meshes ){
			Mesh->SetRenderCustomDepth(true);
			Mesh->SetCustomDepthStencilValue((uint8)StencilColor);
		}
	}
}

void AInteractableActor::OnEndFocus(){
	for ( UMeshComponent* Mesh : Meshes ){
		Mesh->SetRenderCustomDepth(false);
	}
}

void AInteractableActor::SetCanInteract(bool newCanInteract){
	bCanInteract = newCanInteract;
}
