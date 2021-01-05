#include "Material.h"

Material::Material(double density, double restitution)
{
    this->set_density(density);
    this->set_restitution(restitution);
}

Material::Material() {
    this->set_density(0);
    this->set_restitution(0);
}

double Material::get_density() {
    return density;
}

double Material::get_restitution() {
    return restitution;
}

void Material::set_density(double density) {
    this->density = density;
}

void Material::set_restitution(double restitution) {
    this->restitution = restitution;
}
