#include "CompletionCalculator.h"

#include "SavefileIO.h" // Pour accéder à SavefileIO::foundKoroks, foundShrines, etc.
#include "Data.h"       // Pour accéder à Data::KoroksCount, Data::ShrineCount, etc.

float CompletionCalculator::CalculateCompletionPercentage(bool max_mode)
{
    // S’il n’y a pas de sauvegarde chargée, on peut renvoyer 0
    if (!SavefileIO::LoadedSavefile)
        return 0.0f;

    // ============================================
    // 1) RÉCUPÉRER CE QUI EST DÉJÀ DANS SavefileIO
    // ============================================

    // Nombre d’éléments trouvés / vaincus (taille des vecteurs correspondants)
    int foundKoroks = static_cast<int>(SavefileIO::foundKoroks.size());
    int foundShrines = static_cast<int>(SavefileIO::foundShrines.size());
    int foundDLCShrines = static_cast<int>(SavefileIO::foundDLCShrines.size());
    int defeatedHinoxes = static_cast<int>(SavefileIO::defeatedHinoxes.size());
    int defeatedTaluses = static_cast<int>(SavefileIO::defeatedTaluses.size());
    int defeatedMoldugas = static_cast<int>(SavefileIO::defeatedMoldugas.size());
    int visitedLocations = static_cast<int>(SavefileIO::visitedLocations.size());

    // ============================================
    // 2) DÉTERMINER LE TOTAL D’OBJECTIFS POSSIBLES
    // ============================================

    // Le code Data::XCount vous donne le nombre total d’éléments existants
    int totalKoroks = Data::KoroksCount;
    int totalShrines = Data::ShrineCount;
    int totalDLCShrines = Data::DLCShrineCount;
    int totalHinoxes = Data::HinoxesCount;
    int totalTaluses = Data::TalusesCount;
    int totalMoldugas = Data::MoldugasCount;
    int totalLocations = Data::LocationsCount;

    // ============================================
    // 3) SI VOUS TENEZ À RECRÉER LA FORMULE OFFICIELLE
    //    (4 bêtes divines, 120 sanctuaires, 900 Koroks, 185 lieux)
    //    => 1209 total
    //    VOIR L’EXEMPLE PLUS LOIN
    // ============================================

    // Dans votre code, vous pouvez vouloir TOUT inclure (Koroks, Sanctuaires, DLC, Boss, Lieux).
    // Ici, par exemple, on additionne tout :
    int totalFound_official = foundKoroks + foundShrines + visitedLocations;
    int totalPossible_official = totalKoroks + totalShrines + totalLocations;

    int totalFound_max = foundKoroks + foundShrines + foundDLCShrines + defeatedHinoxes + defeatedTaluses + defeatedMoldugas + visitedLocations;
    int totalPossible_max = totalKoroks + totalShrines + totalDLCShrines + totalHinoxes + totalTaluses + totalMoldugas + totalLocations;

    // ============================================
    // 4) CALCUL DU POURCENTAGE
    // ============================================
    float completion_official = 0.0f;
    if (totalFound_official > 0)
    {
        completion_official = (static_cast<float>(totalFound_official) / static_cast<float>(totalPossible_official)) * 100.0f;
    }

    float completion_max = 0.0f;
    if (totalFound_max > 0)
    {
        completion_max = (static_cast<float>(totalFound_max) / static_cast<float>(totalPossible_max)) * 100.0f;
    }

    // On peut arrondir avant de renvoyer, ou non
    return max_mode ? completion_max : completion_official;
}