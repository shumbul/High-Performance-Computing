#include<stdio.h>
#include<omp.h>
/*
 *  Compute forces and accumulate the virial and the potential
 */
  

  void main(){
    double epot,vir;
    int   i, j;
    vir    = 0.0;
    epot   = 0.0;
    int npart = 20;
    
    double x[100],  f[100], side = 1/100000,  rcoff = 1/1727448;
    for(i=0;i<60;i++)
    {
      x[i] = i/103947;
      f[i] = i/43567;
    }
    double start; 
    double end; 
    start = omp_get_wtime(); 
#pragma​ ​ omp​ ​ for shared ( f, x) \
private ( i, j, fxi,fyi,fzi)
    for (i=0; i<npart*3; i+=3) {


      // zero force components on particle i 

      double fxi = 0.0;
      double fyi = 0.0;
      double fzi = 0.0;

      // loop over all particles with index > i 
 
      for (j=i+3; j<npart*3; j+=3) {

	// compute distance between particles i and j allowing for wraparound 

        double xx = x[i]-x[j];
        double yy = x[i+1]-x[j+1];
        double zz = x[i+2]-x[j+2];

        if (xx< (-0.5*side) ) xx += side;
        if (xx> (0.5*side) )  xx -= side;
        if (yy< (-0.5*side) ) yy += side;
        if (yy> (0.5*side) )  yy -= side;
        if (zz< (-0.5*side) ) zz += side;
        if (zz> (0.5*side) )  zz -= side;

        double rd = xx*xx+yy*yy+zz*zz;

	// if distance is inside cutoff radius compute forces
	// and contributions to pot. energy and virial 

        if (rd<=rcoff*rcoff) {

          double rrd      = 1.0/rd;
          double rrd3     = rrd*rrd*rrd;
          double rrd4     = rrd3*rrd;
          double r148     = rrd4*(rrd3 - 0.5);


          epot    += rrd3*(rrd3-1.0); 
          vir     -= rd*r148;

          fxi     += xx*r148;
          fyi     += yy*r148;
          fzi     += zz*r148;

          f[j]    -= xx*r148;
          f[j+1]  -= yy*r148;
          f[j+2]  -= zz*r148;

        }

      }

      // update forces on particle i 
	f[i]     += fxi;
	f[i+1]   += fyi;
	f[i+2]   += fzi;
    }
end = omp_get_wtime(); 
printf("Work took %f seconds\n", end - start);
  }

