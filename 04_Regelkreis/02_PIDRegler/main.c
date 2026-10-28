#include <stdio.h>
#include <stdbool.h>

// Anfangstemperatur Innen
const double t0 = 21;
// Zeitintervall in Sekunden
const double dt = 60;
// Wärmeverlustkoeffizient
const double H = 30;
// Maximale Heizleistung
const double P = 2000;
// Wärmekapazität
const double C = 4000000;
// Außentemperatur
const double ta = 12;
// Solltemperatur
const double tw = 21;

// PID-Konstanten
const double Kp = 20.0;
const double Ki = 0.001;
const double Kd = 100.0;

// PID-Zustand
double integral = 0;
double lastDiff = 0;

// Aktuelle Innentemperatur
double t = 21;

// Heizleistung zwischen 0 und 1
double ein = 0;

double pid(void)
{
    double diff = tw - t;

    double p = Kp * diff;

    integral += diff * dt;
    double i = Ki * integral;

    double d = Kd * (diff - lastDiff) / dt;

    lastDiff = diff;

    double output = p + i + d;

    output /= 100.0;

    if (output > 1.0)
        output = 1.0;

    if (output < 0.0)
        output = 0.0;

    return output;
}

int main(void)
{
    lastDiff = tw - t;

    printf("Zeit [min];Temperatur [°C];Heizung [%%]\n");

    for (int n = 0; n < 24 * 60; n++)
    {
        ein = pid();

        t += ((P * ein - H * (t - ta)) * dt) / C;

        printf("%d;%.4f;%.2f\n", n, t, ein * 100);
    }

    return 0;
}