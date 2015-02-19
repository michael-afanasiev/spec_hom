

#include <iostream>

#include <petscksp.h>    

#include "spec_hom.h"

hexahedra::hexahedra(int ni, int di, DM dm) {
    
    n_gll = ni + 1;
    dim   = di;
    
    if (n_gll == 4) {        
        gll_p = gll_p_4;    
        gll_w = gll_w_4;
    } else if (n_gll == 5) {
        gll_p = gll_p_5;
        gll_w = gll_w_5;
    } else if (n_gll == 6) {
        gll_p = gll_p_6;
        gll_w = gll_w_6;
    } else if (n_gll == 7) {
        gll_p = gll_p_7;
        gll_w = gll_w_7;
    }
        
}

PetscErrorCode hexahedra::print_info() {
    
    
    PetscFunctionBegin;
    
    PetscErrorCode      ier;
    PetscMPIInt         rank;
    
    ier = MPI_Comm_rank(PETSC_COMM_WORLD, &rank); CHKERRQ(ier);
    if (rank == 0)
    std::cout << "Hexahedral element.\nUsing legendre polynomails of degree "
              << n_gll-1 << "." << std::endl;
    
    PetscFunctionReturn(0);
    
}

PetscErrorCode hexahedra::construct_mass_matrix() {
    
    PetscFunctionBegin;
    
    PetscFunctionReturn(0);
    
}