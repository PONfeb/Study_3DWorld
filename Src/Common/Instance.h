
#pragma once

#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"

namespace Ins
{
   // InputManager �̒Z�k�Q��
   inline InputManager& input() { return InputManager::GetInstance(); }

   // SceneManager �̒Z�k�Q��
   inline SceneManager& scene() { return SceneManager::GetInstance(); }
}

// �g����
// #include "Instance.h"
// Ins::�Z�k�Q�Ɩ�.���\�b�h��();
// ��jIns::input().IsNew(KEY_INPUT_SPACE);