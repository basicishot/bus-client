// i hate keeden
// c# original version: https://github.com/jeydevv/MonkeModMenu
// do not skid this
// DO not skid this shit bro
#include <jni.h>
#include <android/log.h>
#include <thread>
#include <unistd.h>
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNMResolve.hpp" // bnm resolve contains all the major includes. latest: https://github.com/livku2/bnmresolve
#include <httplib.h>
#include <json.hpp>
#include <XRInput.hpp>
#include <GorillaLocomotion.hpp>
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNM/Method.hpp"
#include "BNM/MethodBase.hpp"
#include "BNM/Field.hpp"
#include "BNM/FieldBase.hpp"
#include "BNM/UnityStructures/Color.hpp"
#include "BNM/UnityStructures/Quaternion.hpp"
#include "BNM/UnityStructures/Raycasthit.hpp"
#include "BNM/UnityStructures/Vector2.hpp"
#include "BNM/UnityStructures/Vector3.hpp"
#include "BNM/UnityStructures.hpp"
#include "BNM/BasicMonoStructures.hpp"
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNMResolve.hpp"
#include <BNM/BasicMonoStructures.hpp>
#include <BNM/Class.hpp>
#include <BNM/ClassesManagement.hpp>
#include <BNM/ComplexMonoStructures.hpp>
#include <BNM/Coroutine.hpp>
#include <BNM/DebugMessages.hpp>
#include <BNM/Defaults.hpp>
#include <BNM/Delegates.hpp>
#include <BNM/Event.hpp>
#include <BNM/EventBase.hpp>
#include <BNM/EventBase.hpp>
#include <BNM/Exceptions.hpp>
#include <BNM/Field.hpp>
#include <BNM/FieldBase.hpp>
#include <BNM/Il2CppHeaders.hpp>
#include <BNM/Image.hpp>
#include <BNM/Loading.hpp>
#include <BNM/Method.hpp>
#include <BNM/MethodBase.hpp>
#include <BNM/Operators.hpp>
#include <BNM/Property.hpp>
#include <BNM/PropertyBase.hpp>
#include <BNM/UnityStructures.hpp>
#include <BNM/Utils.hpp>
#include <string>
#include <vector>
#include <XRInput.hpp>
#include <GorillaLocomotion.hpp>
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNM/Method.hpp"
#include "BNM/MethodBase.hpp"
#include "BNM/Field.hpp"
#include "BNM/FieldBase.hpp"
#include "BNM/UnityStructures/Color.hpp"
#include "BNM/UnityStructures/Quaternion.hpp"
#include "BNM/UnityStructures/Raycasthit.hpp"
#include "BNM/UnityStructures/Vector2.hpp"
#include "BNM/UnityStructures/Vector3.hpp"
#include "BNM/UnityStructures.hpp"
#include "BNM/BasicMonoStructures.hpp"
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNMResolve.hpp"
#include <BNM/BasicMonoStructures.hpp>
#include <BNM/Class.hpp>
#include <BNM/ClassesManagement.hpp>
#include <BNM/ComplexMonoStructures.hpp>
#include <BNM/Coroutine.hpp>
#include <BNM/DebugMessages.hpp>
#include <BNM/Defaults.hpp>
#include <BNM/Delegates.hpp>
#include <BNM/Event.hpp>
#include <BNM/EventBase.hpp>
#include <BNM/EventBase.hpp>
#include <BNM/Exceptions.hpp>
#include <BNM/Field.hpp>
#include <BNM/FieldBase.hpp>
#include <BNM/Il2CppHeaders.hpp>
#include <BNM/Image.hpp>
#include <BNM/Loading.hpp>
#include <BNM/Method.hpp>
#include <BNM/MethodBase.hpp>
#include <BNM/Operators.hpp>
#include <BNM/Property.hpp>
#include <BNM/PropertyBase.hpp>
#include <BNM/UnityStructures.hpp>
#include <BNM/Utils.hpp>
#include "Mods.hpp"
#include "Hooks.hpp"
#include "GUIManager.hpp"
#include "PhotonResolve.hpp"

#define O(str) BNM_OBFUSCATE(str)

VRRig vrrrig;
GUIManager* gui;

using namespace BNM;
using namespace BNM::IL2CPP;
using namespace BNM::Structures;
using namespace BNM::Structures::Unity;
using namespace BNM::UnityEngine;
using namespace std;
using namespace Hooks;
using namespace BNM::Defaults;

Visual* visuals;

Class GorillaGameManager;
Class PhotonNetwork;

static std::vector<std::string> unlockQueue;
static std::mutex unlockQueueMutex;
static bool unlockThreadDone = true;

Method<bool> InRoom; // not being used cuz commented out the check
static Method<string> ServerIp;
static int currentPage = 0;
static const int buttonsPerPage = 6;
static bool mastaClient = false;
static GameObject *menu = nullptr;
static GameObject *canvasObj = nullptr;
static GameObject *referance = nullptr;
static GameObject *pointer = nullptr;
static int framePressCooldown = 0;
static float fps;

struct ModButton {
    std::string name;
    bool isToggle;
    bool isCategory;
    std::function<void()> action;
};

struct SettingsButton {
    //this is just for settings that is up and comin
    std::string name;
    static vector<const string> i; // <<-- idk what to call this lmao
    std::function<void()> action;
};

vector<ModButton> homePage;

string currentCategory = O("home");
map<string, bool> toggleStates;
map<string, vector<ModButton>> categories;
map<string, std::function<void()>> toggleActions;

// discord.gg/busclient


static vector<const string> buttons = {
        O("Toggle Super Monke"),
        O("Toggle Tag Gun"), // crashes, search BREAKS in this file to see what line it is if you want to try to fix. i spent ages and i have no clue why.
        O("Toggle Speed Boost"),
        O("Tag All"),
        O("Turn Off Tag Freeze"),
        O("Toggle Beacon"),
        O("Lag All"),
        O("Set Master"),
        O("Chams"),
        O("Break Tag"),
        O("Platforms"),
        O("Long Arms"),
        O("Velo Fly"),
        O("Zero Grav"),
        O("Loud Handtaps"),
        O("No Handtaps"),
        O("No Tap Cooldown"),
        O("Name Test")//,
        // not really sure what would happen if you added more buttons, but prolly would just extend off the menu, or hate keeden that works too
        //this is no use anymore ll
};
static bool buttonsActive[] = {false, false, false, false, false, false};

// methods to be called later
static void Draw();
static void Toggle(Mono::String* relatedText);
//

vector<ModButton> EnabledMods() {
    vector<ModButton> mods;
    ModButton backButton;
    backButton.name = "Back";
    backButton.isToggle = false;
    backButton.isCategory = true;
    backButton.action = []() {
        currentCategory = "home";
        Draw();
    };
    mods.push_back(backButton);
    unordered_set<string> seen;

    for (const auto& [catName, buttons] : categories) {
        for (const auto& btn : buttons) {
            if (btn.isToggle && toggleStates[btn.name]) {
                if (seen.insert(btn.name).second) {
                    mods.push_back(btn);
                }
            }
        }
    }

    return mods;
}

struct CosmeticItem {
    Mono::String* itemName;
    int itemCategory;
    void* itemPicture;
    void* displayName;
    void* overrideDisplayName;
    int cost;
    Mono::Array<Mono::String*>* bundledItems;
    bool canTryOn;
    bool bothHandsHoldable;
    bool isNullItem;
};
// discord.gg/busclient
struct SendOptionss {
    int DeliveryMode;
    bool Encrypt;
    uint8_t Channel;
};

void Home() {
    homePage.clear();
    for (auto& [name, _] : categories) {
        homePage.push_back({ name, false, true, [name]() {
            currentCategory = name;
            Draw();
        }});
    }
}

static void ssetMaster() {
    Property<void*> LocalPlayer = PhotonNetwork.GetProperty("LocalPlayer");
    Method<void*> SetMaster = PhotonNetwork.GetMethod("SetMasterClient");
    SetMaster.Call(LocalPlayer);
    mastaClient = true;
}

void InitCategories() {
    vector<ModButton> movementMods = {
            {"Back",         false, true,  []() {
                currentCategory = "home";
                Draw();
            }},
            {"Speedboost",   true, false, []() {
                GorillaLocomotion::Player::get_Instance()->SetMaxJumpSpeed(999.f);
                GorillaLocomotion::Player::get_Instance()->SetJumpMultiplier(2.25f);
            }},
            {"Long Arms",    false, false, []() {
                GameObject *arms = GameObject::Find("Player VR Controller");
                arms->GetTransform()->SetLocalScale(Vector3(1.4f, 1.4f, 1.4f));
            }},
            {"Fly",          true,  false, []() {
                static bool flying = false;
                bool primaryDown = XRInput::GetBoolFeature(BoolFeature::PrimaryButton,
                                                           Controller::Right);
                bool secondaryDown = XRInput::GetBoolFeature(BoolFeature::SecondaryButton,
                                                             Controller::Right);
                static bool gravityToggled = false;
                static bool flyingg = false;

                if (primaryDown) {
                    GorillaLocomotion::Player::get_Instance()->GetTransform()->SetPosition(
                            GorillaLocomotion::Player::get_Instance()->GetTransform()->GetPosition() +
                            GorillaLocomotion::Player::get_Instance()->GetHeadCollider()->GetTransform()->GetForward() *
                            Time::GetDeltaTime() * 12.f);
                    reinterpret_cast<Rigidbody *>(GorillaLocomotion::Player::get_Instance()->GetGameObject()->GetComponent(
                            Rigidbody::GetType()))->SetVelocity(Vector3::zero);
                    if (!flyingg) {
                        flyingg = true;
                    }
                } else if (flyingg) {
                    reinterpret_cast<Rigidbody *>(GorillaLocomotion::Player::get_Instance()->GetGameObject()->GetComponent(
                            Rigidbody::GetType()))->SetVelocity(
                            GorillaLocomotion::Player::get_Instance()->GetHeadCollider()->GetTransform()->GetForward() *
                            Time::GetDeltaTime() * 12.f);
                    flyingg = false;
                }

                if (secondaryDown) {
                    if (!gravityToggled &&
                        reinterpret_cast<Collider *>(GorillaLocomotion::Player::get_Instance()->GetBodyCollider())->GetAttachedRigidbody()->GetUseGravity()) {
                        reinterpret_cast<Collider *>(GorillaLocomotion::Player::get_Instance()->GetBodyCollider())->GetAttachedRigidbody()->SetUseGravity(
                                false);
                        gravityToggled = true;
                    } else if (!gravityToggled &&
                               !reinterpret_cast<Collider *>(GorillaLocomotion::Player::get_Instance()->GetBodyCollider())->GetAttachedRigidbody()->GetUseGravity()) {
                        reinterpret_cast<Collider *>(GorillaLocomotion::Player::get_Instance()->GetBodyCollider())->GetAttachedRigidbody()->SetUseGravity(
                                true);
                        gravityToggled = true;
                    }
                } else {
                    gravityToggled = false;
                }
            }},
            {"Velo Fly",     true,  false, []() {
                Rigidbody *rigidbody = (Rigidbody *) GameObject::Find(
                        "GorillaPlayer")->GetComponent(Rigidbody::GetType());
                if (XRInput::GetBoolFeature(BoolFeature::TriggerButton, Controller::Right)) {
                    Transform *maincam = GameObject::Find("Main Camera")->GetTransform();
                    Vector3 force = maincam->GetForward() * 1.0f;
                    rigidbody->AddForce(force, ForceMode::VelocityChange);
                }
            }},
            {"Platforms",    true,  false, []() {
                static GameObject *rightPlat = nullptr;
                if (XRInput::GetBoolFeature(BoolFeature::GripButton, Controller::Right)) {
                    if (rightPlat == nullptr) {
                        GameObject *controller = GameObject::Find("RightHand Controller");
                        rightPlat = GameObject::CreatePrimitive(PrimitiveType::Cube);
                        Vector3 controllerPos = controller->GetTransform()->GetPosition();
                        Vector3 platPos = Vector3(controllerPos.x, controllerPos.y - 0.1f,
                                                  controllerPos.z);
                        rightPlat->GetTransform()->SetPosition(platPos);
                        rightPlat->GetTransform()->SetLocalScale(
                                Vector3(0.289351, 0.03870832, 0.4166668));
                    }
                } else {
                    if (rightPlat != nullptr) {
                        GameObject::Destroy(rightPlat);
                        rightPlat = nullptr;
                    }
                }
                static GameObject *leftPlat = nullptr;
                if (XRInput::GetBoolFeature(BoolFeature::GripButton, Controller::Left)) {
                    if (leftPlat == nullptr) {
                        GameObject *controller = GameObject::Find("LeftHand Controller");
                        leftPlat = GameObject::CreatePrimitive(PrimitiveType::Cube);
                        Vector3 controllerPos = controller->GetTransform()->GetPosition();
                        Vector3 platPos = Vector3(controllerPos.x, controllerPos.y - 0.1f,
                                                  controllerPos.z);
                        leftPlat->GetTransform()->SetPosition(platPos);
                        leftPlat->GetTransform()->SetLocalScale(Vector3(0.4f, 0.05f, 0.4f));
                    }
                } else {
                    if (leftPlat != nullptr) {
                        GameObject::Destroy(leftPlat);
                        leftPlat = nullptr;
                    }
                }
            }},
            {"Noclip", true, false, []() {
                auto *leftHand = reinterpret_cast<Rigidbody *>(GameObject::Find("LeftHand Controller")->GetComponent(Rigidbody::GetType()));
                auto *rightHand = reinterpret_cast<Rigidbody *>(GameObject::Find("RightHand Controller")->GetComponent(Rigidbody::GetType()));
                auto *body = reinterpret_cast<Rigidbody *>(GameObject::Find("GorillaPlayer")->GetComponent(Rigidbody::GetType()));

                if (XRInput::GetBoolFeature(BoolFeature::SecondaryButton, Controller::Right)) {
                    leftHand->SetDetectCollisions(false);
                    body->SetDetectCollisions(false);
                    rightHand->SetDetectCollisions(false);
                }
                else {
                    leftHand->SetDetectCollisions(true);
                    body->SetDetectCollisions(true);
                    rightHand->SetDetectCollisions(true);
                }
            }},
            {"Zero Gravity", false, false, []() {
                Component* gP = GameObject::Find("GorillaPlayer")->GetComponent(Rigidbody::GetType());
                auto *rigidBody = reinterpret_cast<Rigidbody *>(gP);
                rigidBody->SetUseGravity(false);
            }},
            {"Fix Gravity",  false, false, []() {
                Component* gP = GameObject::Find("GorillaPlayer")->GetComponent(Rigidbody::GetType());
                auto* rigidBody = reinterpret_cast<Rigidbody*>(gP);
                rigidBody->SetUseGravity(true);
            }},
            {"No Tag Freeze", true, false, []() {
                GorillaLocomotion::Player::get_Instance()->SetDisableMovement(false);
            }},
            {"Force Tag Freeze", true, false, []() {
                GorillaLocomotion::Player::get_Instance()->SetDisableMovement(true);
            }},
            {"Slow PSA", true, false, []() {
                if (XRInput::GetBoolFeature(BoolFeature::PrimaryButton, Controller::Right)) {
                    Transform* collida = GorillaLocomotion::Player::get_Instance()->GetBodyCollider()->GetTransform();
                    Transform* gorillaplayer = GameObject::Find("GorillaPlayer")->GetTransform();

                    gorillaplayer->SetPosition(gorillaplayer->GetPosition() + collida->GetForward() * Time::GetDeltaTime() * 2.5f);
                }
            }},
            {"PSA", true, false, []() {
                if (XRInput::GetBoolFeature(BoolFeature::PrimaryButton, Controller::Right)) {
                    Transform* collida = GorillaLocomotion::Player::get_Instance()->GetBodyCollider()->GetTransform();
                    Transform* gorillaplayer = GameObject::Find("GorillaPlayer")->GetTransform();

                    gorillaplayer->SetPosition(gorillaplayer->GetPosition() + collida->GetForward() * Time::GetDeltaTime() * 5.5f);
                }
            }},
            {"Up And Down", true, false, []() {
                static auto inst = GorillaLocomotion::Player::get_Instance();
                static Rigidbody* rb = inst->GetPlayerRigidBody();

                if (XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Right) > .5f) {
                    Vector3 velo = rb->GetVelocity();
                    Vector3 additive = ((Vector3::up * Time::GetDeltaTime()) * 30.f);
                    rb->SetVelocity( velo + additive );
                }
                if (XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Left) > .5f) {
                    Vector3 velo = rb->GetVelocity();
                    Vector3 additive = ((Vector3::up * Time::GetDeltaTime()) * -30.f);
                    rb->SetVelocity( velo + additive );
                }
            }},
            {"Gorilla Car", true, false, []() {
                static auto inst = GorillaLocomotion::Player::get_Instance();
                static Rigidbody* rb = inst->GetPlayerRigidBody();

                if (XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Right) > .5f) {
                    Vector3 velo = rb->GetVelocity();
                    Vector3 additive = ((inst->GetBodyCollider()->GetTransform()->GetForward() * Time::GetDeltaTime()) * 30.f);
                    rb->SetVelocity( velo + additive );
                }
                if (XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Left) > .5f) {
                    Vector3 velo = rb->GetVelocity();
                    Vector3 additive = ((inst->GetBodyCollider()->GetTransform()->GetForward() * Time::GetDeltaTime()) * -30.f);
                    rb->SetVelocity( velo + additive );
                }
            }},
            {"Pull Mod", true, false, []() {
                bool lasttouchleft = false;
                bool lasttouchright = false;
                if (((!GorillaLocomotion::Player::get_Instance()->IsHandTouching(true) && lasttouchleft) || (!!GorillaLocomotion::Player::get_Instance()->IsHandTouching(false) && lasttouchright)) && XRInput::GetFloatFeature(FloatFeature::Grip, Controller::Right) > .5f)
                {
                    Vector3 vel = GorillaLocomotion::Player::get_Instance()->GetPlayerRigidBody()->GetVelocity();
                    Transform* tran = GorillaLocomotion::Player::get_Instance()->GetTransform();
                    tran->SetPosition(tran->GetPosition() + Vector3(vel.x * 1, 0.f, vel.z * 1));
                }
                lasttouchleft = GorillaLocomotion::Player::get_Instance()->IsHandTouching(true);
                lasttouchright = GorillaLocomotion::Player::get_Instance()->IsHandTouching(false);
            }},
            {"Frozone", true, false, []() {
                bool leftGrab = XRInput::GetFloatFeature(FloatFeature::Grip, Controller::Left) > .5f;
                bool rightGrab = XRInput::GetFloatFeature(FloatFeature::Grip, Controller::Right) > .5f;

                if (leftGrab)
                {
                    GameObject* slipperyPlatform = GameObject::CreatePrimitive(PrimitiveType::Cube);
                    slipperyPlatform->SetName(O("Frozone"));
                    reinterpret_cast<Renderer*>(slipperyPlatform->GetComponent(Renderer::GetType()))->GetMaterial()->SetColor(Color::cyan);
                    slipperyPlatform->GetTransform()->SetLocalScale(Vector3(0.025f, 0.3f, 0.4f));
                    slipperyPlatform->GetTransform()->SetPosition(GorillaLocomotion::Player::get_Instance()->GetLeftHandTransform()->GetPosition() + Vector3(0, -.1f, .0f));
                    slipperyPlatform->GetTransform()->SetRotation(GorillaLocomotion::Player::get_Instance()->GetLeftHandTransform()->GetRotation());

                    GameObject::Destroy(slipperyPlatform, 1);
                }

                if (rightGrab)
                {
                    GameObject* slipperyPlatform = GameObject::CreatePrimitive(PrimitiveType::Cube);
                    slipperyPlatform->SetName(O("Frozone"));
                    reinterpret_cast<Renderer*>(slipperyPlatform->GetComponent(Renderer::GetType()))->GetMaterial()->SetColor(Color::cyan);
                    slipperyPlatform->GetTransform()->SetLocalScale(Vector3(0.025f, 0.3f, 0.4f));
                    slipperyPlatform->GetTransform()->SetPosition(GorillaLocomotion::Player::get_Instance()->GetRightHandTransform()->GetPosition() + Vector3(0, -.1f, .0f));
                    slipperyPlatform->GetTransform()->SetRotation(GorillaLocomotion::Player::get_Instance()->GetRightHandTransform()->GetRotation());

                    GameObject::Destroy(slipperyPlatform, 1);
                }

                GorillaLocomotion::Player::get_Instance()->GetBodyCollider()->SetEnabled(!(leftGrab || rightGrab));
            }},
            {"Slide Control", true, false, []() {
                float oldSlideControl = -1.0f;
                static GorillaLocomotion::Player* instance = GorillaLocomotion::Player::get_Instance();
                if (oldSlideControl == -1.0f) {
                    oldSlideControl = instance->GetSlideControl();
                }
                instance->SetSlideControl(1.0f);
            }},
            {"TFly", true, false, []() {
                float flySpeed = 10.f;
                if (XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Right) > .5f) {
                    static auto inst = GorillaLocomotion::Player::get_Instance();
                    static Rigidbody* rb = inst->GetPlayerRigidBody();
                    inst->GetTransform()->SetPosition(inst->GetTransform()->GetPosition() + inst->GetHeadCollider()->GetTransform()->GetForward() * Time::GetDeltaTime() * flySpeed);
                    rb->SetVelocity(Vector3::zero);
                }
            }},
            {"ExcelFly", true, false, []() {
                static Transform* leftHandTransform = GorillaLocomotion::Player::get_Instance()->GetLeftHandTransform();
                static Transform* rightHandTransform = GorillaLocomotion::Player::get_Instance()->GetRightHandTransform();
                static Rigidbody* rb = GorillaLocomotion::Player::get_Instance()->GetPlayerRigidBody();

                if (XRInput::GetBoolFeature(BoolFeature::PrimaryButton, Controller::Right)) {
                    rb->SetVelocity(rb->GetVelocity() + (rightHandTransform->GetRight() / 2.0f));
                }

                if (XRInput::GetBoolFeature(BoolFeature::PrimaryButton, Controller::Left)) {
                    rb->SetVelocity(rb->GetVelocity() + (-leftHandTransform->GetRight() / 2.0f));
                }
            }},
            {"Joystick Fly", true, false, []() {
                float flySpeed = 10.f;
                static auto inst = GorillaLocomotion::Player::get_Instance();
                static auto rb = inst->GetPlayerRigidBody();

                Vector2 leftJoystick = XRInput::GetVector2Feature(Vector2Feature::Primary2DAxis, Controller::Left);
                Vector2 rightJoystick = XRInput::GetVector2Feature(Vector2Feature::Primary2DAxis, Controller::Right);

                Vector3 inputDirection = Vector3(leftJoystick.x, rightJoystick.y, leftJoystick.y);
                Vector3 playerForward = inst->GetBodyCollider()->GetTransform()->GetForward();
                playerForward.y = 0;
                Vector3 playerRight = inst->GetBodyCollider()->GetTransform()->GetRight();
                playerRight.y = 0;
// discord.gg/busclient
                Vector3 velocity = inputDirection.x * playerRight + rightJoystick.y * Vector3::up + inputDirection.z * playerForward;
                velocity *= inst->GetTransform()->GetLocalScale().x * flySpeed;
                rb->SetVelocity(Vector3::Lerp(rb->GetVelocity(), velocity, 0.12875f));
            }},
            {"Fast PSA", true, false, []() {
                if (XRInput::GetBoolFeature(BoolFeature::PrimaryButton, Controller::Right)) {
                    Transform* collida = GorillaLocomotion::Player::get_Instance()->GetBodyCollider()->GetTransform();
                    Transform* gorillaplayer = GameObject::Find("GorillaPlayer")->GetTransform();

                    gorillaplayer->SetPosition(gorillaplayer->GetPosition() + collida->GetForward() * Time::GetDeltaTime() * 7.5f);
                }
            }}
    };
    vector<ModButton> roomMods = {
            {"Back",                false, true,  []() {
                currentCategory = "home";
                Draw();
            }},
            {"Set Master",     false, false, []() {
                Property<void*> LocalPlayer = PhotonNetwork.GetProperty("LocalPlayer");
                Method<void*> SetMaster = PhotonNetwork.GetMethod("SetMasterClient");
                SetMaster.Call(LocalPlayer);
                mastaClient = true;
            }},
            {"Lag All [M!] [RT]", true, false, []() {
                if (XRInput::GetBoolFeature(BoolFeature::TriggerButton, Controller::Left)) {
                    if (!mastaClient) {
                        Property<void*> LocalPlayer = PhotonNetwork.GetProperty("LocalPlayer");
                        Method<void*> SetMaster = PhotonNetwork.GetMethod("SetMasterClient");
                        SetMaster.Call(LocalPlayer);
                        mastaClient = true;
                    }
                    Method<void*> lag = PhotonNetwork.GetMethod("DestroyAll");
                    lag.Call();
                }
            }},
            {"Break Room", false, false, []() {
                ssetMaster();
                auto currentRoom = PhotonNetwork::GetCurrentRoom();
                if (currentRoom) {
                    currentRoom->SetPlayerCount(200);
                    currentRoom->SetIsOpen(false);
                }
            }},
            {"Break Tag [LT]", true, false, []() {
                    if (XRInput::GetBoolFeature(BoolFeature::TriggerButton, Controller::Left)) {

                    Method<void *> setTag = GorillaGameManager.GetMethod("SetisCurrentlyTag", 1);
                    Method<void *> clearInfection = GorillaGameManager.GetMethod(
                            "ClearInfectionState", 0);
                    Method<void> changeCurrentIt = GorillaGameManager.GetMethod("ChangeCurrentIt",
                                                                                1);

                    Property<IL2CPP::Il2CppObject *> LocalPlayer = PhotonNetwork.GetProperty(
                            "LocalPlayer");
                    IL2CPP::Il2CppObject *ggmInstance = GameObject::FindObjectOfType(
                            GorillaGameManager);

                    setTag[ggmInstance].Call(true);
                    clearInfection[ggmInstance].Call();
                    changeCurrentIt[ggmInstance].Call(LocalPlayer);
                }
            }},
            {"Mat All", true, false, []() {
                Class GorillaTagManager = Class("", "GorillaTagManager");
                //Array<Object> array = GameObject::FindObjectsOfType(GorillaTagManager.GetMonoType());
                Method<void> clearInfectionState = GorillaTagManager.GetMethod("ClearInfectionState");
                Field<float> checkCooldown = GorillaTagManager.GetField("checkCooldown");
                Field<float> tagCoolDown = GorillaTagManager.GetField("tagCoolDown");

                for (auto i : GameObject::FindObjectsOfType(GorillaTagManager.GetMonoType())->ToVector())
                {
                    clearInfectionState[i]();
                    tagCoolDown[i] = .0f;
                    checkCooldown[i] = .0f;
                }
            }}
    };
    vector<ModButton> visualMods = {
            {"Back",    false, true,  []() {
                currentCategory = "home";
                Draw();
            }},
            {"ESP", true, false, []() {
                Class VRRig("", "VRRig");
                Array<Object *> *vrRigs = GameObject::FindObjectsOfType(VRRig.GetMonoType());
                Field<bool> isOfflineVRRig = VRRig.GetField("isOfflineVRRig");
                Field<bool> isMyPlayer = VRRig.GetField("isMyPlayer");
                Class PhotonView = Class("Photon.Pun", "PhotonView", Image("PhotonUnityNetworking.dll"));
                Property<bool> IsMine = PhotonView.GetProperty("IsMine");
                for (Object *rig: vrRigs->ToVector()) {
                    if (!isOfflineVRRig[rig]() && !isMyPlayer[rig]() && !IsMine[rig]()) {
                        GameObject *box = GameObject::CreatePrimitive(PrimitiveType::Cube);
                        GameObject::Destroy(box->GetComponent(BoxCollider::GetType()));
                        GameObject::Destroy(box->GetComponent(Rigidbody::GetType()));
                        GameObject::Destroy(box->GetComponent(Collider::GetType()));
                        box->GetTransform()->SetRotation(Quaternion::identity);
                        box->GetTransform()->SetLocalScale(Vector3(0.2f, 0.2f, 0.2f));
                        box->GetTransform()->SetPosition(
                                reinterpret_cast<Component *>(rig)->GetTransform()->GetPosition());
                        reinterpret_cast<Renderer *>(box->GetComponent(
                                MeshRenderer::GetType()))->GetMaterial()->SetColor(Color::green);
                        Shader* shader = Shader::Find("GUI/Text Shader");
                        reinterpret_cast<Renderer *>(box->GetComponent(
                                MeshRenderer::GetType()))->GetMaterial()->SetShader(shader);
                        //reinterpret_cast<Renderer*>(beacon->GetComponent(MeshRenderer::GetType()))->SetMaterial(reinterpret_cast<Renderer*>(reinterpret_cast<Component*>(rig)->GetComponent(Renderer::GetType()))->GetMaterial());
                        // ^^^ attempt to do the actual player skin mat but skinned mesh renderer isnt in BNM resolve.
                        GameObject::Destroy(box, Time::GetDeltaTime());
                    }
                }
            }},
            {"Cham Beacons", true,  false, []() {
                Class VRRig("", "VRRig");
                Array<Object *> *vrRigs = GameObject::FindObjectsOfType(VRRig.GetMonoType());
                Field<bool> isOfflineVRRig = VRRig.GetField("isOfflineVRRig");
                Field<bool> isMyPlayer = VRRig.GetField("isMyPlayer");
                Class PhotonView = Class("Photon.Pun", "PhotonView",
                                         Image("PhotonUnityNetworking.dll"));
                Property<bool> IsMine = PhotonView.GetProperty("IsMine");
                for (Object *rig: vrRigs->ToVector()) {
                    if (!isOfflineVRRig[rig]() && !isMyPlayer[rig]() && !IsMine[rig]()) {
                        GameObject *beacon = GameObject::CreatePrimitive(PrimitiveType::Cylinder);
                        GameObject::Destroy(beacon->GetComponent(BoxCollider::GetType()));
                        GameObject::Destroy(beacon->GetComponent(Rigidbody::GetType()));
                        GameObject::Destroy(beacon->GetComponent(Collider::GetType()));
                        beacon->GetTransform()->SetRotation(Quaternion::identity);
                        beacon->GetTransform()->SetLocalScale(Vector3(0.04f, 200.f, 0.04f));
                        beacon->GetTransform()->SetPosition(
                                reinterpret_cast<Component *>(rig)->GetTransform()->GetPosition());
                        reinterpret_cast<Renderer *>(beacon->GetComponent(
                                MeshRenderer::GetType()))->GetMaterial()->SetColor(Color::white);
                        Shader* shader = Shader::Find("GUI/Text Shader");
                        reinterpret_cast<Renderer *>(beacon->GetComponent(
                                MeshRenderer::GetType()))->GetMaterial()->SetShader(shader);
                        //reinterpret_cast<Renderer*>(beacon->GetComponent(MeshRenderer::GetType()))->SetMaterial(reinterpret_cast<Renderer*>(reinterpret_cast<Component*>(rig)->GetComponent(Renderer::GetType()))->GetMaterial());
                        // ^^^ attempt to do the actual player skin mat but skinned mesh renderer isnt in BNM resolve.
                        GameObject::Destroy(beacon, Time::GetDeltaTime());
                    }
                }
            }},
            {"Beacons", true,  false, []() {
                Class VRRig("", "VRRig");
                Array<Object *> *vrRigs = GameObject::FindObjectsOfType(VRRig.GetMonoType());
                Field<bool> isOfflineVRRig = VRRig.GetField("isOfflineVRRig");
                Field<bool> isMyPlayer = VRRig.GetField("isMyPlayer");
                Class PhotonView = Class("Photon.Pun", "PhotonView",
                                         Image("PhotonUnityNetworking.dll"));
                Property<bool> IsMine = PhotonView.GetProperty("IsMine");
                for (Object *rig: vrRigs->ToVector()) {
                    if (!isOfflineVRRig[rig]() && !isMyPlayer[rig]() && !IsMine[rig]()) {
                        GameObject *beacon = GameObject::CreatePrimitive(PrimitiveType::Cylinder);
                        GameObject::Destroy(beacon->GetComponent(BoxCollider::GetType()));
                        GameObject::Destroy(beacon->GetComponent(Rigidbody::GetType()));
                        GameObject::Destroy(beacon->GetComponent(Collider::GetType()));
                        beacon->GetTransform()->SetRotation(Quaternion::identity);
                        beacon->GetTransform()->SetLocalScale(Vector3(0.04f, 200.f, 0.04f));
                        beacon->GetTransform()->SetPosition(
                                reinterpret_cast<Component *>(rig)->GetTransform()->GetPosition());
                        reinterpret_cast<Renderer *>(beacon->GetComponent(
                                MeshRenderer::GetType()))->GetMaterial()->SetColor(Color::white);
                        //reinterpret_cast<Renderer*>(beacon->GetComponent(MeshRenderer::GetType()))->SetMaterial(reinterpret_cast<Renderer*>(reinterpret_cast<Component*>(rig)->GetComponent(Renderer::GetType()))->GetMaterial());
                        // ^^^ attempt to do the actual player skin mat but skinned mesh renderer isnt in BNM resolve.
                        GameObject::Destroy(beacon, Time::GetDeltaTime());
                    }
                }
            }},
            { "See Network Triggers [W?]", false, false, []() {
                visuals->SeeNetworkTriggers();
            }}
    };
// discord.gg/busclient
    vector<ModButton> rigMods = {
            {"Back",    false, true,  []() {
                currentCategory = "home";
                Draw();
            }},
            {"Rig Spam [RT] [W?]", true, false, []() {
                if (XRInput::GetBoolFeature(BoolFeature::TriggerButton, Controller::Right)) {
                    PhotonNetwork::Instantiate("gorillaprefabs/Gorilla Player Networked", Vector3(GameObject::Find("GorillaPlayer")->GetTransform()->GetPosition()), Quaternion(GameObject::Find("GorillaPlayer")->GetTransform()->GetRotation()));
                }
            }}
    };
// discord.gg/busclient
    vector<ModButton> funMods = {
            { "Back",    false, true,  []() {
                currentCategory = "home";
                Draw();
            }},
    };
// discord.gg/busclient
    vector<ModButton> soundMods = {
            {"Back",    false, true,  []() {
                currentCategory = "home";
                Draw();
            }},
            {"Metal Spam", true, false, []() {
                vrrrig.PlayHandTap(18, true, 999999.f);
            }},
            {"Crystal Spam", true, false, []() {
                vrrrig.PlayHandTap(43, true, 999999.f);
            }},
            {"Wood Spam", true, false, []() {
                vrrrig.PlayHandTap(8, true, 999999.f);
            }},
            {"Concrete Spam", true, false, []() {
                vrrrig.PlayHandTap(1, true, 999999.f);
            }},
            {"Cloth Spam", true, false, []() {
                vrrrig.PlayHandTap(3, true, 999999.f);
            }},
            {"Snow Spam", true, false, []() {
                vrrrig.PlayHandTap(31, true, 999999.f);
            }}
    };
// discord.gg/busclient
// discord.gg/busclient
    categories["Enabled"] = EnabledMods();
    categories["Movement"] = movementMods;
    categories["Room"] = roomMods;
    categories["Sound"] = soundMods;
    categories["Rig"] = rigMods;
    categories["Visual"] = visualMods;

    homePage.clear();
    vector<string> catergories = {
            "Enabled",
            "Movement",
            "Room",
            "Rig",
            "Sound",
            "Visual"
    };
// discord.gg/busclient
    for (const string& name : catergories) {
        homePage.push_back({ name, false, true, [name]() {
            currentCategory = name;
            currentPage = 0;
            Draw();
        }});
    }
}
// discord.gg/busclient
void UpdateToggleStuff() {
    for (auto& [name, action] : toggleActions) {
        action();
    }
}
// discord.gg/busclient

void UpdateFPS() {
    fps = 1.0f / Time::GetUnscaledDeltaTime();
}

// discord.gg/busclient
void MotdAndCOC() {
    Color pink = Color(1.0f, 0.4f, 0.8f, 1.0f);
    Color white = Color(1.0f, 1.0f, 1.0f, 1.0f);
// discord.gg/busclient
    static float fadeTimer = 0.0f;
    const float duration = 2.5f;
// discord.gg/busclient
    fadeTimer += Time::GetDeltaTime();
    if (fadeTimer > duration) fadeTimer = 0.0f;
// discord.gg/busclient
    float normalized = fabs((fadeTimer / duration) * 2.0f - 1.0f);
    Color current = Color::Lerp(pink, white, normalized);
    auto p = PhotonNetwork::GetPhotonServerSettings()->GetAppSettings();
// discord.gg/busclient
    auto motdtextGO = GameObject::Find("COC Text");
    auto motd = GameObject::Find("motd");
    auto CodeOfConduct = GameObject::Find("CodeOfConduct");
    if (motdtextGO) {
        auto textComp1 = (Text*)motdtextGO->GetComponent(Text::GetType());
        if (textComp1) {
            textComp1->SetColor(current);
            textComp1->SetText("<color=red>Realtime ID: "+p->GetAppIdRealtime()+"\nVoice ID: "+p->GetAppIdVoice()+"\nApp Version: "+p->GetAppVersion()+"</color>");
        }
    }
    if (motd) {
        auto motdtext = (Text*)motd->GetComponent(Text::GetType());
        if (motdtext) {
            motdtext->SetColor(current);
            motdtext->SetText("<color=#6600FF>B</color><color=#5B00F5>U</color><color=#5100EB>S</color> <color=#3D00D8>C</color><color=#3200CE>L</color><color=#2800C4>I</color><color=#1E00BB>E</color><color=#1400B1>N</color><color=#0A00A7>T</color>");
        }
    }
    if (CodeOfConduct) {
        auto CodeOfConducttext = (Text*)CodeOfConduct->GetComponent(Text::GetType());
        if (CodeOfConducttext) {
            CodeOfConducttext->SetColor(current);
            CodeOfConducttext->SetText("<color=#6600FF>B</color><color=#5B00F5>U</color><color=#5100EB>S</color> <color=#3D00D8>C</color><color=#3200CE>L</color><color=#2800C4>I</color><color=#1E00BB>E</color><color=#1400B1>N</color><color=#0A00A7>T</color>");
        }
    }
}

// discord.gg/busclient
void (*Update)(void*);
void new_Update(void* instance) {
    MotdAndCOC();
    Update(instance);
    UpdateFPS();
    UpdateToggleStuff();
    static bool gripDown;
    static bool gravityToggled = false;
    static bool flying = false;
    static int btnCooldown = 0;
    static float maxJumpSpeed = 0;
//if (InRoom.Call()) { // useless check but u can keep it iyw
    if (maxJumpSpeed == 0) {
        maxJumpSpeed = GorillaLocomotion::Player::get_Instance()->GetMaxJumpSpeed();
    }
// discord.gg/busclient
    float grip = XRInput::GetBoolFeature(BoolFeature::SecondaryButton, Controller::Left);
    if (grip) {
        gripDown = true;
    }
    else {
        gripDown = false;
    }

    if (gripDown && menu == nullptr) {
        InitCategories();
        Draw();
        if (referance == nullptr) {
            referance = GameObject::CreatePrimitive(PrimitiveType::Sphere);
            //GameObject::Destroy(referance->GetComponent(MeshRenderer::GetType())); // comment this out to make the referance visible.
            // ^^^ Referance is on the left side of ur right hand for some reason (on the github gifs, its on the finger i have no clue why)
            referance->GetTransform()->SetParent(GameObject::Find("RightHand Controller")->GetTransform());
            reinterpret_cast<Renderer*>(referance->GetComponent(Renderer::GetType()))->GetMaterial()->SetColor(Color(0.4f, 0.0f, 0.6f));
            referance->GetTransform()->SetLocalPosition(Vector3(0.f, -0.1f, 0.f));
            referance->GetTransform()->SetLocalScale(Vector3(0.01f, 0.01f, 0.01f));
        }
    } else if (!gripDown && menu != nullptr) {
        GameObject::Destroy(menu);
        menu = nullptr;
        GameObject::Destroy(referance);
        referance = nullptr;
    }

    if (gripDown && menu != nullptr) {
        menu->GetTransform()->SetPosition(GameObject::Find("LeftHand Controller")->GetTransform()->GetPosition());
        menu->GetTransform()->SetRotation(GameObject::Find("LeftHand Controller")->GetTransform()->GetRotation());
    }

    if (btnCooldown > 0) {
        if (Time::GetFrameCount() > btnCooldown) {
            btnCooldown = 0;
            buttonsActive[3] = false;
            GameObject::Destroy(menu);
            menu = nullptr;
            Draw();
        }
    }
}
//}
struct BtnCollider : BNM::UnityEngine::MonoBehaviour
{
    BNM_CustomClass(BtnCollider,
                    BNM::CompileTimeClassBuilder(BNM_OBFUSCATE_TMP(O("")), BNM_OBFUSCATE_TMP(O("BtnCollider"))).Build(),
                    BNM::CompileTimeClassBuilder(BNM_OBFUSCATE_TMP(O("UnityEngine")), BNM_OBFUSCATE_TMP(O("MonoBehaviour")), BNM_OBFUSCATE_TMP(O("UnityEngine.CoreModule"))).Build(),
                    {},
    ); // custom monobehavior yappington, cool part is this acts as a real class and i can do like Class BtnCollider = Class(O(""), O("BtnCollider")); and actually load it, i do that later in the code.

    void Constructor() {
        BNM::UnityEngine::MonoBehaviour tmp = *this;
        *this = BtnCollider();
        *((BNM::UnityEngine::MonoBehaviour *)this) = tmp;
    }

    void Start() {
    }
    Mono::String* relatedText;
    void OnTriggerEnter(Collider* collider)
    {
        if (Time::GetFrameCount() >= framePressCooldown + 30)
        {
            vrrrig.PlayHandTap(8, true, 999999.f);
            Toggle(relatedText);
            framePressCooldown = Time::GetFrameCount();
        }
    }
    BNM_CustomField(relatedText, BNM::Defaults::Get<Mono::String*>(), "relatedText");
    BNM_CustomMethod(OnTriggerEnter, false, BNM::Defaults::Get<void>(), "OnTriggerEnter");
    BNM_CustomMethod(Start, false, BNM::Defaults::Get<void>(), "Start");
    BNM_CustomMethod(Constructor, false, BNM::Defaults::Get<void>(), ".ctor");
};
void AddButton(float offset, const std::string& text, bool toggled = false)
{
    GameObject* newBtn = GameObject::CreatePrimitive(PrimitiveType::Cube);
    GameObject::Destroy(newBtn->GetComponent(Rigidbody::GetType()));
    reinterpret_cast<Collider*>(newBtn->GetComponent(BoxCollider::GetType()))->SetIsTrigger(true);
    Rigidbody* rb = (Rigidbody*)newBtn->AddComponent(Rigidbody::GetType());
    rb->SetIsKinematic(true);
    newBtn->GetTransform()->SetParent(menu->GetTransform());
    newBtn->GetTransform()->SetRotation(Quaternion::identity);
    newBtn->GetTransform()->SetLocalScale(Vector3(0.09f, 0.8f, 0.08f));
    newBtn->GetTransform()->SetLocalPosition(Vector3(0.56f, 0.f, 0.28f - offset));
    Class BtnCollider = Class(O(""), O("BtnCollider"));
    newBtn->AddComponent(BtnCollider.GetMonoType());
    Field<Mono::String*> relatedText = BtnCollider.GetField(O("relatedText"));
    Il2CppObject* btnInst = reinterpret_cast<Behaviour*>(newBtn->GetComponent(BtnCollider.GetMonoType()));
    relatedText.SetInstance(btnInst);
    relatedText.Set(CreateMonoString(text));

    int index = -1;
    for (int i = 0; i < buttons.size(); i++)
    {
        if (text == buttons[i])
        {
            index = i;
            break;
        }
    }


    Renderer* renderer = reinterpret_cast<Renderer*>(newBtn->GetComponent(Renderer::GetType()));
    renderer->GetMaterial()->SetColor(toggled ? Color(0.4f, 0.05f, 0.05f, 1.f) : Color(0.1f, 0.1f, 0.1f, 1.0f));

    GameObject* outlineObj = GameObject::CreatePrimitive(PrimitiveType::Cube);
    GameObject::Destroy(outlineObj->GetComponent(Rigidbody::GetType()));
    GameObject::Destroy(outlineObj->GetComponent(BoxCollider::GetType()));
    GameObject::Destroy(outlineObj->GetComponent(MeshCollider::GetType()));
    Renderer* outlineRenderer = reinterpret_cast<Renderer*>(outlineObj->GetComponent(Renderer::GetType()));
    outlineRenderer->GetMaterial()->SetColor(Color(0.4f, 0.0f, 0.6f));
    outlineObj->GetTransform()->SetParent(newBtn->GetTransform());
    outlineObj->GetTransform()->SetLocalPosition(Vector3(0.f, 0.f, 0.01f));
    outlineObj->GetTransform()->SetLocalRotation(Quaternion::identity);
    outlineObj->GetTransform()->SetLocalScale(Vector3(0.9f, 1.01f, 1.05f));

    GameObject* titleObj = (GameObject*)GameObject::GetClass().CreateNewObjectParameters();
    titleObj->GetTransform()->SetParent(canvasObj->GetTransform());
    Text* title = (Text*)(titleObj->AddComponent(Text::GetType()));
    title->SetFont((Font*)(Resources::GetBuiltinResource(Font::GetType(), O("Arial.ttf")))); // same font as original but feel free to change
    title->SetText(text);
    title->SetFontSize(1);
    title->SetAlignment(TextAnchor::MiddleCenter);
    title->SetTextResizeForBestFit(true);
    title->SetResizeTextMinSize(0);
    RectTransform* titleTransform = title->GetRectTransform();
    titleTransform->SetLocalPosition(Vector3::zero);
    titleTransform->SetSizeDelta(Vector2(0.2f, 0.03f));
    titleTransform->SetLocalPosition(Vector3(0.064f, 0.f, 0.111f - (offset / 2.55f)));
    titleTransform->SetRotation(Quaternion::FromEuler(Vector3(180.f, 90.f, 90.f)));
}
void AddDisconnectButton(float offset)
{
    //another dupe of AddButton for disconnect
    GameObject* newBtn = GameObject::CreatePrimitive(PrimitiveType::Cube);
    GameObject::Destroy(newBtn->GetComponent(Rigidbody::GetType()));
    reinterpret_cast<Collider*>(newBtn->GetComponent(BoxCollider::GetType()))->SetIsTrigger(true);
    Rigidbody* rb = (Rigidbody*)newBtn->AddComponent(Rigidbody::GetType());
    rb->SetIsKinematic(true);
    newBtn->GetTransform()->SetParent(menu->GetTransform());
    newBtn->GetTransform()->SetRotation(Quaternion::identity);
    newBtn->GetTransform()->SetLocalScale(Vector3(0.09f, 0.8f, 0.08f));
    newBtn->GetTransform()->SetLocalPosition(Vector3(0.56f, 0.f, 0.28f - offset));
    Class BtnCollider = Class(O(""), O("BtnCollider"));
    newBtn->AddComponent(BtnCollider.GetMonoType());
    Field<Mono::String*> relatedText = BtnCollider.GetField(O("relatedText"));
    Il2CppObject* btnInst = reinterpret_cast<Behaviour*>(newBtn->GetComponent(BtnCollider.GetMonoType()));
    relatedText.SetInstance(btnInst);
    relatedText.Set(CreateMonoString("Disconnect"));

    Renderer* renderer = reinterpret_cast<Renderer*>(newBtn->GetComponent(Renderer::GetType()));
    renderer->GetMaterial()->SetColor(Color(0.4f, 0.0f, 0.6f));

    GameObject* outlineObj = GameObject::CreatePrimitive(PrimitiveType::Cube);
    GameObject::Destroy(outlineObj->GetComponent(Rigidbody::GetType()));
    GameObject::Destroy(outlineObj->GetComponent(BoxCollider::GetType()));
    GameObject::Destroy(outlineObj->GetComponent(MeshCollider::GetType()));
    Renderer* outlineRenderer = reinterpret_cast<Renderer*>(outlineObj->GetComponent(Renderer::GetType()));
    outlineRenderer->GetMaterial()->SetColor(Color::black);
    outlineObj->GetTransform()->SetParent(newBtn->GetTransform());
    outlineObj->GetTransform()->SetLocalPosition(Vector3(0.f, 0.f, 0.01f));
    outlineObj->GetTransform()->SetLocalRotation(Quaternion::identity);
    outlineObj->GetTransform()->SetLocalScale(Vector3(0.9f, 1.01f, 1.05f));
    GameObject* titleObj = (GameObject*)GameObject::GetClass().CreateNewObjectParameters();
    titleObj->GetTransform()->SetParent(canvasObj->GetTransform());
    Text* title = (Text*)(titleObj->AddComponent(Text::GetType()));
    title->SetFont((Font*)(Resources::GetBuiltinResource(Font::GetType(), O("Arial.ttf"))));
    title->SetText("Disconnect");
    title->SetFontSize(1);
    title->SetAlignment(TextAnchor::MiddleCenter);
    title->SetTextResizeForBestFit(true);
    title->SetResizeTextMinSize(0);

    RectTransform* titleTransform = title->GetRectTransform();
    titleTransform->SetLocalPosition(Vector3::zero);
    titleTransform->SetSizeDelta(Vector2(0.2f, 0.03f));
    titleTransform->SetLocalPosition(Vector3(0.064f, 0.f, 0.111f - (offset / 2.55f)));
    titleTransform->SetRotation(Quaternion::FromEuler(Vector3(180.f, 90.f, 90.f)));
}
void AddSidePageButton(bool left, const std::string& text)
{
    //drawing
    GameObject* newBtn = GameObject::CreatePrimitive(PrimitiveType::Cube);
    GameObject::Destroy(newBtn->GetComponent(Rigidbody::GetType()));
    reinterpret_cast<Collider*>(newBtn->GetComponent(BoxCollider::GetType()))->SetIsTrigger(true);
    Rigidbody* rb = (Rigidbody*)newBtn->AddComponent(Rigidbody::GetType());
    rb->SetIsKinematic(true);
// discord.gg/busclient
    newBtn->GetTransform()->SetParent(menu->GetTransform());
    newBtn->GetTransform()->SetRotation(Quaternion::FromEuler(Vector3(90.0f, 0.f, 0.f)));
    newBtn->GetTransform()->SetLocalScale(Vector3(0.04f, 0.6f, 0.12f));
    float xPos = left ? 0.5f : 0.5f;
    float yPos = left ? 0.6f : -0.6f;
    newBtn->GetTransform()->SetLocalPosition(Vector3(xPos, yPos, 0.f));
// discord.gg/busclient
    Class BtnCollider = Class(O(""), O("BtnCollider"));
    newBtn->AddComponent(BtnCollider.GetMonoType());
    Field<Mono::String*> relatedText = BtnCollider.GetField(O("relatedText"));
    Il2CppObject* btnInst = reinterpret_cast<Behaviour*>(newBtn->GetComponent(BtnCollider.GetMonoType()));
    relatedText.SetInstance(btnInst);
    relatedText.Set(CreateMonoString(text));
    Renderer* renderer = reinterpret_cast<Renderer*>(newBtn->GetComponent(Renderer::GetType()));
    renderer->GetMaterial()->SetColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
// discord.gg/busclient
    //actual outline object coming into play
    GameObject* outlineObj = GameObject::CreatePrimitive(PrimitiveType::Cube);
    GameObject::Destroy(outlineObj->GetComponent(Rigidbody::GetType()));
    GameObject::Destroy(outlineObj->GetComponent(BoxCollider::GetType()));
    GameObject::Destroy(outlineObj->GetComponent(MeshCollider::GetType()));

    Renderer* outlineRenderer = reinterpret_cast<Renderer*>(outlineObj->GetComponent(Renderer::GetType()));
    outlineRenderer->GetMaterial()->SetColor(Color(0.4f, 0.0f, 0.6f));
    outlineObj->GetTransform()->SetParent(newBtn->GetTransform());
    outlineObj->GetTransform()->SetLocalPosition(Vector3(0.f, 0.f, -0.05f)); // Very slightly behind
    outlineObj->GetTransform()->SetLocalRotation(Quaternion::identity);
    outlineObj->GetTransform()->SetLocalScale(Vector3(0.95f, 1.01f, 1.05f));
// discord.gg/busclient
    //text stuff
    GameObject* titleObj = (GameObject*)GameObject::GetClass().CreateNewObjectParameters();
    titleObj->GetTransform()->SetParent(canvasObj->GetTransform());
    Text* title = (Text*)(titleObj->AddComponent(Text::GetType()));
    title->SetFont((Font*)(Resources::GetBuiltinResource(Font::GetType(), O("Arial.ttf")))); // same font as original but feel free to change
    title->SetText(text);
    title->SetFontSize(1);
    title->SetAlignment(TextAnchor::MiddleCenter);
    title->SetTextResizeForBestFit(true);
    title->SetResizeTextMinSize(0);
    RectTransform* titleTransform = title->GetRectTransform();
    titleTransform->SetLocalPosition(Vector3::zero);
    titleTransform->SetSizeDelta(Vector2(0.2f, 0.03f));
    titleTransform->SetLocalPosition(Vector3(0.064f, 0.f, 0.111f - (2.55f)));
    titleTransform->SetRotation(Quaternion::FromEuler(Vector3(180.f, 90.f, 90.f)));
}
static void Draw()
{
    Home(); //this is just the home page, its what draws it.
    vector<ModButton>* catButtons = (currentCategory == O("home")) ? &homePage : &categories[currentCategory]; //makes it so the hom page has the category buttons and some other stuff. pretty useful.
    GameObject::Destroy(menu); //incase the menu wasnt nullptr or just non-existant, it destroys the old one to prevent overlapping and stuff.
    //menu stuff and stuff :)
    menu = GameObject::CreatePrimitive(PrimitiveType::Cube);
    GameObject::Destroy(menu->GetComponent(Rigidbody::GetType()));
    GameObject::Destroy(menu->GetComponent(BoxCollider::GetType()));
    GameObject::Destroy(menu->GetComponent(Renderer::GetType()));
    menu->GetTransform()->SetLocalScale(Vector3(0.1f, 0.3f, 0.4f));
    //actual background/object for the menu
    GameObject* background = GameObject::CreatePrimitive(PrimitiveType::Cube);
    GameObject::Destroy(background->GetComponent(Rigidbody::GetType()));
    GameObject::Destroy(background->GetComponent(BoxCollider::GetType()));
    background->GetTransform()->SetParent(menu->GetTransform());
    background->GetTransform()->SetRotation(Quaternion::identity);
    background->GetTransform()->SetLocalScale(Vector3(0.1f, 1.f, 1.f));
    reinterpret_cast<Renderer*>(background->GetComponent(Renderer::GetType()))->GetMaterial()->SetColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
    background->GetTransform()->SetPosition(Vector3(0.05f, 0.f, 0.f));
    //canvas stuff for the menu
    canvasObj = (GameObject*)GameObject::GetClass().CreateNewObjectParameters();
    canvasObj->GetTransform()->SetParent(menu->GetTransform());
    Canvas* canvas = (Canvas*)canvasObj->AddComponent(Canvas::GetType());
    CanvasScaler* canvasScale = (CanvasScaler*)canvasObj->AddComponent(CanvasScaler::GetType());
    canvasObj->AddComponent(GraphicRaycaster::GetType());
    canvas->SetRenderMode(RenderMode::WorldSpace);
    canvasScale->SetDynamicPixelsPerUnit(1000);

    //outline stuff
    GameObject* outlineObj = GameObject::CreatePrimitive(PrimitiveType::Cube);
    GameObject::Destroy(outlineObj->GetComponent(Rigidbody::GetType()));
    GameObject::Destroy(outlineObj->GetComponent(BoxCollider::GetType()));
    outlineObj->GetTransform()->SetParent(menu->GetTransform());
    outlineObj->GetTransform()->SetRotation(Quaternion::identity);
    outlineObj->GetTransform()->SetLocalScale(Vector3(0.090f, 1.01f, 1.01f));
    outlineObj->GetTransform()->SetPosition(Vector3(0.05f, 0.f, 0.f));
    Renderer* outlineRenderer = reinterpret_cast<Renderer*>(outlineObj->GetComponent(Renderer::GetType()));
    outlineRenderer->GetMaterial()->SetColor(Color(0.4f, 0.0f, 0.6f));

    //title shit
    GameObject* titleObj = (GameObject*)GameObject::GetClass().CreateNewObjectParameters();
    titleObj->GetTransform()->SetParent(canvasObj->GetTransform());
    Text* title = (Text*)titleObj->AddComponent(Text::GetType());
    title->SetFont((Font*)(Resources::GetBuiltinResource(Font::GetType(), O("Arial.ttf"))));
    title->SetText((O("<color=#660099>Bus</color><color=grey> Client</color>\n<i><color=grey>[") + currentCategory + "]</color></i>").c_str()); // here is the menu title, change this iyw
    title->SetFontSize(1);
    title->SetAlignment(TextAnchor::MiddleCenter);
    title->SetTextResizeForBestFit(true);
    title->SetResizeTextMinSize(0);
    RectTransform* titleTransform = title->GetRectTransform();
    titleTransform->SetLocalPosition(Vector3::zero);
    titleTransform->SetSizeDelta(Vector2(0.28f, 0.05f));
    titleTransform->SetPosition(Vector3(0.06f, 0.f, 0.175f));
    titleTransform->SetRotation(Quaternion::FromEuler(Vector3(180.f, 90.f, 90.f)));
    //this is for pages + limiting the buttons to 4 per page.
    int startIndex = currentPage * buttonsPerPage;
    int endIndex = min((int)catButtons->size(), startIndex + buttonsPerPage);
    float offset = 0;
    //this is where limiting buttons for each page comes into play.
    for (int i = startIndex; i < endIndex; i++) {
        const auto& btn = catButtons->at(i);
        bool toggled = btn.isToggle && toggleStates[btn.name];
        AddButton(offset, btn.name, toggled);
        offset += 0.13f;
    }
    //page buttons that get added
    AddDisconnectButton(-0.30f);
    AddSidePageButton(true, O("<"));
    AddSidePageButton(false, O(">"));
}
static void Toggle(Mono::String* relatedText) //handles pages + other stuff related to toggling and stuff. works pretty nice
{
    string text = relatedText->str();
    vector<ModButton>* currentList = (currentCategory == O("home")) ? &homePage : &categories[currentCategory];
    int total = (currentCategory == O("home")) ? homePage.size() : categories[currentCategory].size();
    int totalPages = (total + buttonsPerPage - 1) / buttonsPerPage;
    vrrrig.PlayHandTap(8, true, 999999.f);
    if (text == "Disconnect") {
        Method<void*> dc = PhotonNetwork.GetMethod("Disconnect");
        dc.Call();
    }
    if (totalPages > 0) {
        if (text == O(">")) {
            currentPage = (currentPage + 1) % totalPages;
        } else if (text == O("<")) {
            currentPage = (currentPage == 0) ? (totalPages - 1) : (currentPage - 1);
        }
    }
    for (auto& btn : *currentList) {
        if (btn.name == text) {
            if (btn.isToggle) {
                toggleStates[btn.name] = !toggleStates[btn.name];
                if (toggleStates[btn.name]) {
                    toggleActions[btn.name] = btn.action;  //if isToggle then it will nicely be
                } else {
                    toggleActions.erase(btn.name); //just turns it off/removes it from executing after toggled off
                }
            } else {
                btn.action(); //just calls once when the isToggle is false (a button)
            }
            break;
        }
    }

    GameObject::Destroy(menu);
    menu = nullptr;
    Draw();
}

static float crashAllDelay = 0.0f;



void OnLoaded() {
    PhotonNetwork = Class(O("Photon.Pun"), O("PhotonNetwork"), Image(O("PhotonUnityNetworking")));
    GorillaGameManager = Class("", "GorillaTagManager");
    InRoom = PhotonNetwork.GetMethod(O("get_InRoom"));
    ServerIp = PhotonNetwork.GetMethod("get_ServerAddress");  //not useless this guy is lying!!!  // again, useless check but if you want it to work just like the original, you can uncomment the check in new_Update and the menu will only work if ur in a room.
    InvokeHook(Class("GorillaNetworking", "CosmeticsController").GetMethod("Update"), new_Update, Update);
    //InvokeHook(Class("Photon.VR", "PhotonVRManager").GetProperty("IsCorrect"), new_IsCorrect, IsCorrect);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, [[maybe_unused]] void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    BNM::Loading::AddOnLoadedEvent(OnLoaded);
    BNM::Loading::TryLoadByJNI(env);
    return JNI_VERSION_1_6;
}
