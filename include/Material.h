#ifndef MATERIAL_H
#define MATERIAL_H


class Material
{
    public:
        Material(double, double);
        Material();

        double get_density();
        double get_restitution();

        void set_density(double);
        void set_restitution(double);

    private:
        double density;
        double restitution;
};

#endif // MATERIAL_H
