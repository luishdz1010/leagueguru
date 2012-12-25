#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>
#include "guru/matchupinfo.pb.h"
#include "guru/participantrole.pb.h"

class Enums
{
    Q_GADGET
    Q_ENUMS(ServerRegion)
    Q_ENUMS(ChampionRole)
    Q_ENUMS(GuruKeys)
    Q_ENUMS(PickState)
public:

    enum ServerRegion{
        NorthAmerica = guru::NA,
        EuropeWest = guru::EUW,
        EuropeNordicEast = guru::EUNE,
        Brazil = guru::BR
    };

    enum ChampionRole{
        AnyRole = guru::ANY_ROLE,
        Top = guru::TOP,
        Mid = guru::MID,
        Support = guru::SUPPORT,
        Jungler = guru::JUNGLER,
        ADC = guru::ADC
    };

    enum GuruKeys{
        ControlShiftTabKey = Qt::Key_unknown + 1,
        ControlTabKey
    };

    enum PickState{
        NotPicking = 0,
        Picking,
        LockedIn
    };

private:
    Enums(){}

    void hi();
};

#endif // ENUMS_H
