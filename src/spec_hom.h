

#include <petscfe.h>
#include <petscksp.h>    
#include <petscdmplex.h>

class mesh;
class hexahedra;
class tetrahedra;

class mesh {
    
public:
    
    mesh(DM*);
    
private:
        
};


class hexahedra {
    
public:
    
    hexahedra(int, int, DM);
    
    /* functions */
    PetscErrorCode print_info(); 
    PetscErrorCode construct_mass_matrix();                         
    
private:
    
    /* dimension */
    int         dim;
    
    /* gll colocation points */
    int         n_gll;
    double     *gll_p;
    double      gll_p_4[5] = {-1, -0.6546536707, 0, 0.6546536707, 1};
    double      gll_p_5[6] = {-1, -0.7650553239, -0.2852315164, 0.2852315164, 
                              0.7650553239, 1};
    double      gll_p_6[7] = {-1, -0.8302238962, -0.4688487934, 0, 
                              0.4688487934, 0.8302238962, 1};
    double      gll_p_7[8] = {-1, -0.8717401485, -0.5917001814, -0.2092992179, 
                              0.2092992179, 0.5917001814, 0.8717401485, 1};
                              
    /* gll integration weights */
    double     *gll_w;
    double      gll_w_4[5] = {0.1, 0.5444444444, 0.7111111111, 0.5444444444, 
                              0.1};
    double      gll_w_5[6] = {0.0666666666, 0.3784749562, 0.5548583770, 
                              0.5548583770,0.3784749562, 0.0666666666};
    double      gll_w_6[7] = {0.0476190476, 0.2768260473, 0.4317453812, 
                              0.4876190476,0.4317453812, 0.2768260473, 
                              0.0476190476};
    double      gll_w_7[8] = {0.0357142857, 0.2107042271, 0.3411226924, 
                              0.4124587946, 0.4124587946, 0.3411226924, 
                              0.2107042271, 0.0357142857};
                                                                                              
};