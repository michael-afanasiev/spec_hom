static char help[] = "A 1D spectral element wave propagator.\n\n";

#include <iostream>

#include <exodusII.h>
#include <petscksp.h>    
#include <petscdmplex.h>
#include <petscdmda.h>

#include "spec_hom.h"

extern PetscErrorCode CreateMesh(DM *dm);
extern PetscErrorCode ConstructMassMatrix(DM *dm);

int main(int argc, char **args) {
    
    /* Setup (will be moved to parameters) */
    int dim=2, order=4;
    
    /* Book keeping */
    PetscErrorCode  ier;        /* Holds error codes */
    PetscMPIInt     comm_size;  /* Size of MPI communicator */
    
    /* Mesh components */
    DM              dm;         /* DMDA distributed mesh object */
    Vec             glob;
    Vec             loc;
    
    /* Initialize Petsc and MPI environment */
    PetscInitialize(&argc, &args, (char*)0, help);
    ier = MPI_Comm_size(PETSC_COMM_WORLD, &comm_size); CHKERRQ(ier);
    
    /* Open exodus mesh file and place in DM object */
    ier = CreateMesh(&dm); CHKERRQ(ier);
    
    /* Create global vector, and processor specific local vector */
    ier = DMCreateGlobalVector(dm, &glob); CHKERRQ(ier);
    ier = DMCreateLocalVector(dm, &loc); CHKERRQ(ier);
    
    /* Set vector values */
    VecSet(glob, -3.0);
    DMGlobalToLocalBegin(dm, glob, INSERT_VALUES, loc);
    DMGlobalToLocalEnd(dm, glob, INSERT_VALUES, loc);
    VecView(loc, PETSC_VIEWER_STDOUT_WORLD);
    
    ier = ConstructMassMatrix(&dm);
    
    /* Set up element type */
    hexahedra hex(order, dim, dm);
    
    PetscFinalize();
    
}

#undef __FUNCT__
#define __FUNCT__ "ConstructMassMatrix"
PetscErrorCode ConstructMassMatrix(DM *dm) {
    
    PetscFunctionBegin;
    
    // PetscErrorCode  ier;
    // Vec             *c;
    
    // ier = VecView(*c, PETSC_VIEWER_STDOUT_WORLD); CHKERRQ(ier);
    
    PetscFunctionReturn(0);
    
}

#undef __FUNCT__
#define __FUNCT__ "CreateMesh"
PetscErrorCode CreateMesh(DM *dm) {
    
    PetscFunctionBegin;
    
    PetscInt            d_free=4;   /* Degrees of freedom per element */
    PetscInt            n_elem=10; /* Number of elements */
    PetscInt            s_width=1;  /* Width of stencil */
    
    
    DMDACreate2d(PETSC_COMM_WORLD, DM_BOUNDARY_NONE, DM_BOUNDARY_NONE,
                 DMDA_STENCIL_BOX, n_elem, n_elem, PETSC_DECIDE, PETSC_DECIDE, 
                 d_free, s_width, NULL, NULL, dm);   
    DMView(*dm, PETSC_VIEWER_STDOUT_WORLD);
    
    PetscFunctionReturn(0);
    
}