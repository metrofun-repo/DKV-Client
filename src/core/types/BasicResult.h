#pragma once

#include "BasicError.h"
#include "Expected.h"

template <typename T>
using BasicResult = Expected<T, BasicError>;