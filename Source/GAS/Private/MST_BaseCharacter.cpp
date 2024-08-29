// Fill out your copyright notice in the Description page of Project Settings.


#include "MST_BaseCharacter.h"

// Sets default values
AMST_BaseCharacter::AMST_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMST_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMST_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMST_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

