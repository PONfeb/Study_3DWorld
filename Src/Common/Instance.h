
#pragma once

#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"

namespace Ins
{
   // InputManager ‚Ì’ZkQÆ
   inline InputManager& input() { return InputManager::GetInstance(); }

   // SceneManager ‚Ì’ZkQÆ
   inline SceneManager& scene() { return SceneManager::GetInstance(); }
}

// g‚¢•û
// #include "Instance.h"
// Ins::’ZkQÆ–¼.ƒƒ\ƒbƒh–¼();
// —ájIns::input().IsNew(KEY_INPUT_SPACE);