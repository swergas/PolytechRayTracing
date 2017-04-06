#ifndef MATERIAL_H_
#define MATERIAL_H_

class Material {
public:
	Material(double k_a = 0, double k_d = 0, double k_s = 0, double n_s = 0, double k_reflex =0);
	virtual ~Material();

	//k_a: ambiant
	//k_d: diffuse
	//k_s: specular
	//n_s: cosine power
	//k_reflex: reflexion (0: matt, 1: mirror)
	double k_a, k_d, k_s, n_s, k_reflex;
};

#endif /* MATERIAL_H_ */
