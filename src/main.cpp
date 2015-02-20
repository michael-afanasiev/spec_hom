static char help[] = "A 1D spectral element wave propagator.\n\n";

#include <iostream>

#include <petscksp.h>    
#include <petscdmplex.h>
#include <petscdmda.h>

#include "spec_hom.h"

/* Functions that modify DM */
extern PetscErrorCode CreateMesh(DM *dm);
extern PetscErrorCode SetupField(DM *dm);
extern PetscErrorCode ConstructMassMatrix(DM *dm);

/* Functions that return something */
extern PetscErrorCode CalculateJacobian(DM *dm, PetscReal);

int main(int argc, char **args) {
    
    /* Setup (will be moved to parameters) */
    int dim=2, order=4;
    
    /* Book keeping */
    PetscErrorCode  ier;        /* Holds error codes */
    PetscMPIInt     comm_size;  /* Size of MPI communicator */
    
    /* Mesh components */
    DM              dm;         /* DMDA distributed mesh object */
	
	/* Jacobian (currently scalar) */
	PetscReal		J=1; 		/* Scalar value of the jacobian */
    
    /* Initialize Petsc and MPI environment */
    PetscInitialize(&argc, &args, (char*)0, help);
    ier = MPI_Comm_size(PETSC_COMM_WORLD, &comm_size); CHKERRQ(ier);
    
    /* Create mesh file and place in DM object */
    ier = CreateMesh(&dm); CHKERRQ(ier);
    
	/* Precalculate Jacobian */
	ier = CalculateJacobian(&dm, J); CHKERRQ(ier);
	
    // VecView(c_loc, PETSC_VIEWER_STDOUT_WORLD);
    
    ier = ConstructMassMatrix(&dm);
    
    /* Set up element type */
    hexahedra hex(order, dim, dm);
    
    PetscFinalize();
    
}

#undef __FUNCT__
#define __FUNCT__ "SetupField"
PetscErrorCode SetupField(DM *dm) {
	
	PetscFunctionBegin;
	
	/* Return a field variable copied from the DM in FIELD */ 
	
    /* Set vector values */
    // VecSet(glob, 1.0);
    // DMGlobalToLocalBegin(dm, glob, INSERT_VALUES, loc);
    // DMGlobalToLocalEnd(dm, glob, INSERT_VALUES, loc);
		
	PetscFunctionReturn(0);
	
}	

#undef __FUNCT__
#define __FUNCT__ "CalculateJacobian"
PetscErrorCode CalculateJacobian(DM *dm, PetscReal jacobian) {
	
	PetscFunctionBegin;
	
	
	PetscFunctionReturn(0);
	
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
    PetscInt            n_elem=4;	/* Number of elements */
    PetscInt            s_width=1;  /* Width of stencil */
	
	PetscReal			xmin=-1.0;	/* Minimum x coordiante */
	PetscReal			ymin=-1.0;  /* Minimum y coordiante */
	PetscReal			zmin=-1.0;	/* Minimum z coordiante */
	PetscReal			xmax=1.0;   /* Maximum x coordiante */
	PetscReal			ymax=1.0;   /* Maximum y coordiante */
	PetscReal			zmax=1.0;	/* Minimum z coordiante */
    
    /* Create 2d mesh */
    DMDACreate2d(PETSC_COMM_WORLD, DM_BOUNDARY_NONE, DM_BOUNDARY_NONE,
                 DMDA_STENCIL_BOX, n_elem, n_elem, PETSC_DECIDE, PETSC_DECIDE, 
                 d_free, s_width, NULL, NULL, dm);
				 
    /* Set uniform co-ordinates */
	DMDASetUniformCoordinates(*dm, xmin, xmax, ymin, ymax, zmin, zmax);

    // DMView(*dm, PETSC_VIEWER_STDOUT_WORLD);
    
    PetscFunctionReturn(0);
    
}
