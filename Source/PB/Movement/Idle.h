// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MovementState.h"

/**
 * 
 */
class PB_API Idle : public MovementState
{
public:
	Idle(APBCharacter* _character);
	~Idle();
    virtual void EnterState(MovementState* prev);
    virtual void ExitState(MovementState* next);
    virtual void Tick(float delta);
};
