/*
 Fix the gun system please anyone - baggZ

#include "BNMIncludes.h"
#include "GorillaLocomotion.hpp"
struct RaycastResult {
    RaycastHit Ray;
    uintptr_t GunPointer;
};

RaycastResult RenderGun(int overrideLayerMask = 0xFFFFFFFF) {
    GameObject* GunPointer;

    RaycastResult result = {};

    Vector3 GunPosition = GorillaTagger::get_Instance()->GetTransform()->GetPosition() + GorillaTagger::get_Instance()->GetRightHandTransform()->GetPosition();
    Vector3 Direction = GunPosition + Vector3::forward;

    Physics::Raycast(GunPosition * GorillaTagger::get_Instance()->GetTransform()->GetLocalScale(), Direction, result.Ray);

    Vector3 EndPosition = result.Ray.point;
    if (EndPosition == Vector3{0,0,0})
        EndPosition = GunPosition + Direction * 512.f;

    if (GunPointer == nullptr)
        GunPointer = GameObject::CreatePrimitive(PrimitiveType::Sphere);

    GunPointer->GetTransform()->SetPosition(Vector3{0.2f,0.2f,0.2f} * GorillaTagger::get_Instance()->GetTransform()->GetLocalScale());

    LineRenderer* GunLine;
    if (GunLine == nullptr)
        GunLine = LineRenderer;

    return result;
} */