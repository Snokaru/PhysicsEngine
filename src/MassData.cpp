#include "MassData.h"

MassData::MassData(double mass)
{
    this->set_mass(mass);
}

MassData::MassData() {
    this->set_mass(0);
}

void MassData::set_mass(double mass) {
    this->mass = mass;
    if (this->mass == 0)
        this->inverse_mass = 0;
    else
        this->inverse_mass = 1/mass;
}

double MassData::get_mass() {
    return mass;
}

double MassData::get_inverse_mass() {
    return inverse_mass;
}
