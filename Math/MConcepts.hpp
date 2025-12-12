#pragma once

#include <concepts>

/**
 * @namespace gmath
 * @brief Пространство имён для математических операций
 * 
 * Содержит шаблонные классы: 
 * 
 * Vector2
 * 
 * Vector3
 * 
 * Vector4
 * 
 * Все классы поддерживают операции с типами float и double.
 */
namespace gmath {
    
    /**
     * @concept isFloatDouble
     * @brief Концепт для проверки типа на соответствие float или double
     * @tparam T Проверяемый тип
     */
    template<typename T> concept is_float_double = std::is_floating_point_v<T>;
}