#ifndef MASSDATA_H
#define MASSDATA_H


class MassData
{
    public:
        MassData(double);
        MassData();

        double  get_mass();
        double  get_inverse_mass();

        void    set_mass(double);

    private:
        double mass;
        double inverse_mass;
};

#endif // MASSDATA_H
