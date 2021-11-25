#ifndef CRPROPA_PARTICLE_MASS_H
#define CRPROPA_PARTICLE_MASS_H

namespace crpropa {
/**
 * \addtogroup PhysicsDefinitions
 * @{
 */

/** Get the nucleus mass by lookup from a table.
 The masses are the atomic masses from the NIST database: 
   http://www.nist.gov/pml/data/comp.cfm
 minus electron masses, neglecting electron binding energies.
 Unmeasured atomic masses are taken to be A * amu minus electron masses.
 The data table is generated by data-tools/NuclearMass/createNuclearMassTable.
 @param id		id of the particle following the PDG numbering scheme
 @returns The mass of a the nucleus
 */
double nuclearMass(int id);
/** Get the nucleus mass by lookup from a table.
 The masses are the atomic masses from the NIST database: 
   http://www.nist.gov/pml/data/comp.cfm
 minus electron masses, neglecting electron binding energies.
 Unmeasured atomic masses are taken to be A * amu minus electron masses.
 The data table is generated by data-tools/NuclearMass/createNuclearMassTable.
 @param A		atomic mass number of the nucleus
 @param Z		atomic number of the nucleus
 @returns The mass of a the nucleus
 */
double nuclearMass(int A, int Z);

/** @}*/
} // namespace crpropa

#endif // CRPROPA_PARTICLE_MASS_H