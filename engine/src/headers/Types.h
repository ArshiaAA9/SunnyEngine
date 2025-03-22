#pragma once
#include <memory>

#include "Objects.h"

using ObjectPtr = std::shared_ptr<Object>;
using ObjectWeakPtr = std::weak_ptr<Object>;

using RectObjectPtr = std::shared_ptr<RectObject>;
using RectObjectWeakPtr = std::weak_ptr<RectObject>;

using CircleObjectPtr = std::shared_ptr<CircleObject>;
using CircleObjectWeakPtr = std::weak_ptr<CircleObject>;
