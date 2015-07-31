// Fill out your copyright notice in the Description page of Project Settings.
#include "PB.h"
#include "PBCharacter.h"
#include "Idle.h"
#include "MovementState.h"

Idle::Idle(APBCharacter* _character)
    :MovementState(_character)
{
    
}

Idle::~Idle()
{
}
void Idle::EnterState(MovementState *prev)
{

}
void Idle::ExitState(MovementState *next)
{
    
}
void Idle::Tick(float delta)
{
    
}
