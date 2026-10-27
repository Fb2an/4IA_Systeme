//
// Created by fabian on 10/27/26.
//

#include <math.h>
#include <stdio.h>
#include <stdbool.h>

int main ()
{
    // Anfangstemperatur Innen
    const double t0 = 21;
    // Zeitintervall in Sekunden
    const double dt = 60;
    // Wärmeverlustkoeffizient des Gebäudes
    const double H = 30;
    // Heizleistung
    const double P = 2000;
    // Wirksame Wärmekapazität des Raumes/Gebäudes
    const double C = 4000000;
    // Außenlufttemperatur
    const double ta = 12;
    // Wunschwert der Innentemperatur
    const double tw = 21;
    // Epsilon
    const double epsilon = 0.5;

    bool ein = false;

    // Aktuelle Innentemperatur
    double t = t0;

    for (int i = 0; i < 24 * 60; i++)
    {
        if (t <= tw - epsilon)
            ein = true;
        else if (t >= tw + epsilon)
            ein = false;

        t = ein
            ? t + ((P - H * (t - ta)) * dt) / C
            : t - (H * (t - ta) * dt) / C;

        printf("%d;%.4f;%d\n", i, t, ein ? 1 : 0);
    }


}
