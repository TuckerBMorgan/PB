// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class APBCharacter;

/**
 * 
 */
class PB_API MovementState
{
protected:
    APBCharacter* character;
public:
    MovementState(APBCharacter* _character);
    virtual ~MovementState() = 0;
    virtual void EnterState(MovementState* previous) = 0;
    virtual void Tick(float delta) = 0;
    virtual void ExitState(MovementState* next) = 0;
};
