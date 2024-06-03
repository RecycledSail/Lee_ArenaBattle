// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Lee_ArenaBattle.h"
#include "GameFramework/Pawn.h"
#include "ABPawn.generated.h"

UCLASS()
class LEE_ARENABATTLE_API AABPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AABPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController *NewController) override;
	
	
};
