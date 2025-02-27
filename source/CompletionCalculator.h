#pragma once

class CompletionCalculator
{
public:
    /// \brief Calcule le pourcentage de complétion en se basant sur SavefileIO
    /// \return Le pourcentage (valeur entre 0.0 et 100.0).
    static float CalculateCompletionPercentage(bool max_mode);
};
