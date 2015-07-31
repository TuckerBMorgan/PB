// Fill out your copyright notice in the Description page of Project Settings.

#include "PB.h"
#include "PBCharacter.h"
#include "MovementState.h"
MovementState::MovementState(APBCharacter* _character)
{
    this->character = _character;
}
MovementState::~MovementState()
{
    
}