// Fill out your copyright notice in the Description page of Project Settings.

#include "PB.h"
#include "PBCharacter.h"
#include "Walking.h"
#include "MovementState.h"

Walking::Walking(APBCharacter* _character)
    : MovementState(_character)
{
    direction = 0;
}

Walking::~Walking()
{
}
void Walking::Tick(float delta)
{
    character->AddMovementInput(FVector(0.f,-1.f,0.f),direction);
}
void Walking::EnterState(MovementState *previous)
{
    
}
void Walking::ExitState(MovementState *next)
{
    
}
void Walking::SetDirection(float value)
{
    direction = value;
}
